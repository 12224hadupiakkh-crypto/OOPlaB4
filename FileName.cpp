#include <iostream>
#include <fstream>
using namespace std;

class Figure {
public:
    virtual double area() = 0;  // чисто віртуальна функція
    virtual void info() = 0;
};

class Square : virtual public Figure {
protected:
    double side;
public:
    Square(double s) : side(s) {}
    double area() override { return side * side; }
    double perimeter() { return 4 * side; }
    void info() override {
        cout << "Square: side = " << side
            << ", area = " << area()
            << ", perimeter = " << perimeter() << endl;
    }
};

class Circle : virtual public Figure {
protected:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() override {
        const double PI = 3.14159265358979323846;
        return PI * radius * radius;
    }
    double circumference() {
        const double PI = 3.14159265358979323846;
        return 2 * PI * radius;
    }
    void info() override {
        cout << "Circle: radius = " << radius
            << ", area = " << area()
            << ", circumference = " << circumference() << endl;
    }
};

class CircleInSquare : public Circle, public Square {
public:
    CircleInSquare(double sideLength)
        : Square(sideLength), Circle(sideLength / 2) {
    }

    // Явне перевизначення area() для уникнення неоднозначності
    double area() override {
        return Square::area(); // або Circle::area(), залежно від того, що треба
    }

    void info() override {
        Square::info();
        Circle::info();
    }
};

int main() {
    double side;
    cout << "Enter side of the square: ";
    cin >> side;

    CircleInSquare cis(side);
    cis.info();

    ofstream file("figures.txt");
    if (file.is_open()) {
        file << "Square: side = " << side
            << ", area = " << cis.area()
            << ", perimeter = " << cis.perimeter() << "\n";

        const double PI = 3.14159265358979323846;
        double radius = side / 2;
        file << "Circle: radius = " << radius
            << ", area = " << PI * radius * radius
            << ", circumference = " << 2 * PI * radius << "\n";

        file.close();
        cout << "Information saved to figures.txt" << endl;
    }
    else {
        cout << "Unable to open file." << endl;
    }

    return 0;
}
