#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& name, const string& prof) : Name(name), Profession(prof) {}

    virtual void Walk(const string& destination) const {
        log() << " walks to: " << destination << endl;
    }

    ostream& log(void) const {
        cout << Profession << ": " << Name;
        return cout;
    }

    string getProf() const {return Profession;}
    string getName() const {return Name;}
protected:
    const string Name;
    const string Profession;
};


class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong) : Person(name, "Student") ,FavouriteSong(favouriteSong) {}

    void Learn() const {
        log() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        log() << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const {
        log() << " sings a song: " << FavouriteSong << endl;
    }
private:
    string FavouriteSong;
};


class Teacher : public Person{
public:
    Teacher(const string& name, const string& subject) : Person(name, "Teacher"), Subject(subject) {}

    void Teach() const {
       log() << " teaches: " << Subject << endl;
    }
private:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name, "Policeman") {}

    void Check(const Person& pers) const {
        log() << " checks " << pers.getProf() << ". " <<  pers.getProf() << "'s name is: " << pers.getName() << endl;
    }
};


void VisitPlaces(const Person& pers, const vector<string>& places) {
    for (const auto& p : places) {
        pers.Walk(p);
    }
}



int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}

