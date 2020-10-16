#include <iostream>

using namespace std;

class Animal {
public:
    Animal(const string& par) : Name(par) {};

    void make_sound() {
        cout << Name << " barks: woof!" << " " << age << endl;
    }
    const string getName() {
        return Name;
    }
private:
    const string Name;
protected:
    int age;
};


class Dog : public Animal {
public:
    Dog(const string& par, const string& s, int ag) : Animal(par), secondname(s) {age = ag;};

private:
    const string secondname;
};

class Bird : public Animal {
public:
    Bird(const string& par, const string& s, int ag) : Animal(par), secondname(s) {age = ag;};
    void check() {
        cout << age << getName();
    }
private:
    const string secondname;
};

int main() {
    Bird d("Bonya", "Asya", 8);
    d.check();
    return 0;
}
