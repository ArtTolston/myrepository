#include <vector>
#include <iostream>
#include <memory>
#include <sstream>
#include <iterator>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdint>
#include <iomanip>
using namespace std;
const double PI = 3.14;

class Figure {
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure {
public:
    Triangle(const double& a, const double& b, const double& c) : _a(a), _b(b), _c(c) {}
    string Name() const override{
        return "TRIANGLE";
    }
    double Perimeter() const override{
        return _a + _b + _c;
    }
    double Area() const override{
        double poluperimeter = Perimeter() / 2;
        return sqrt(poluperimeter * (poluperimeter - _a) * (poluperimeter - _b) * (poluperimeter - _c));
    }
private:
    double _a;
    double _b;
    double _c;
};

class Rect : public Figure{
public:
    Rect(const double& width, const double& height) {
        _width = width;
        _height = height;
    }
    string Name() const override{
        return "RECT";
    }
    double Perimeter() const override{
        return 2 * _width + 2 * _height;
    }
    double Area() const override{
        return _width * _height;
    }
private:
    double _width;
    double _height;
};

class Circle : public Figure {
public:
    Circle(const double& r) {
        _radius = r;
    }
    string Name() const override{
        return "CIRCLE";
    }
    double Perimeter() const override{
        return 2 * PI * _radius;
    }
    double Area() const override{
        return PI * _radius * _radius;
    }
private:
    double _radius;
};

shared_ptr<Figure> CreateFigure(istringstream& ss) {
    string s;
    ss >> s;
    if(s == "TRIANGLE") {
        double a = 0,b = 0,c = 0;
        ss >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else if(s == "RECT") {
        double a = 0, b = 0;
        ss >> a >> b;
        return make_shared<Rect>(a ,b);
    } else if(s == "CIRCLE") {
        double r = 0;
        ss >> r;
        return make_shared<Circle>(r);
    }
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
