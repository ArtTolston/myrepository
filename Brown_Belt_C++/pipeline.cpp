#include "test_runner.h"
#include <iostream>
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
	void PassOn(unique_ptr<Email> email) const {
		if(next_worker)
			next_worker->Process(move(email));
  }
  

public:
	void SetNext(unique_ptr<Worker> next) {
		next_worker = move(next);
  }
private:
	unique_ptr<Worker> next_worker;  //будет ли работать??
};


class Reader : public Worker {
public:
	Reader(istream& in) : input(in) {}

	void Run() override {
		while(!input.eof()) {
			unique_ptr<Email> email = make_unique<Email>();
			getline(input,email->from, '\n');
			if (input.eof())
				return;
			getline(input, email->to, '\n');
			if (input.eof())
				return;
			getline(input, email->body, '\n');
			cerr << email->from << "_\n" << email->to << "_\n" << email->body << "_\n"<< endl;
			Process(move(email));
		}
    }
	void Process(unique_ptr<Email> email) override {
		PassOn(move(email));
	}
private:
	istream& input;
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;

public:
	Filter(Function func) : f(func) {}  // можно ли так делать?

	void Process(unique_ptr<Email> email) override {
		if (f(*email))
			PassOn(move(email));
	}
private:
	Function f;
};


class Copier : public Worker {
public:
	Copier(const string& rec) : receiver(rec) {}

	void Process(unique_ptr<Email> email) override {
		if (email->to != receiver) {
			unique_ptr<Email> copy = make_unique<Email>();
			copy->from = email->from;
			copy->to = receiver;
			copy->body = email->body;
			PassOn(move(email));
			PassOn(move(copy));
		}
		else {
			PassOn(move(email));
		}
	}
private:
	string receiver;
};


class Sender : public Worker {
public:
	Sender(ostream& ostr) :  output(ostr) {}

	void Process(unique_ptr<Email> email) override {
		output << email->from << "\n" << email->to << "\n" << email->body << "\n";
		PassOn(move(email));
	}
private:
	ostream& output;
};


// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
	explicit PipelineBuilder(istream& in) {
		unique_ptr<Worker> w = make_unique<Reader>(in);
		workers.push_back(move(w));
    }

  // добавляет новый обработчик Filter
	PipelineBuilder& FilterBy(Filter::Function filter) {
		unique_ptr<Worker> w = make_unique<Filter>(filter);
		workers.push_back(move(w));
		return *this;
    }

  // добавляет новый обработчик Copier
	PipelineBuilder& CopyTo(string recipient) {
		unique_ptr<Worker> w = make_unique<Copier>(recipient);
		workers.push_back(move(w));
		return *this;
    }

  // добавляет новый обработчик Sender
	PipelineBuilder& Send(ostream& out) {
		unique_ptr<Worker> w = make_unique<Sender>(out);
		workers.push_back(move(w));
		return *this;
    }

  // возвращает готовую цепочку обработчиков
	unique_ptr<Worker> Build() {
		for (int i = workers.size() - 1; i >= 1; --i) {
			workers[i - 1]->SetNext(move(workers[i]));
		}
		return move(workers[0]);
    }
private:
	vector<unique_ptr<Worker>> workers;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
