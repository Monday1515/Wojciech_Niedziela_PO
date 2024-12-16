#include <iostream>
using namespace std;

// Interfejs dla kształtów
class Shape {
public:
    virtual double getArea() const = 0;  // Czyni metodę wirtualną
    virtual ~Shape() = default;  // Wirtualny destruktor
};

// Prostokąt
class Rectangle : public Shape {
protected:
    double width;
    double height;

public:
    Rectangle(double width, double height) : width(width), height(height) {}

    void setWidth(double w) {
        width = w;
    }

    void setHeight(double h) {
        height = h;
    }

    double getArea() const override {
        return width * height;
    }
};

// Kwadrat
class Square : public Shape {
private:
    double side;

public:
    Square(double side) : side(side) {}

    void setSide(double s) {
        side = s;
    }

    double getArea() const override {
        return side * side;
    }
};

int main() {
    Rectangle rect(5, 3);
    Square sq(4);

    Shape* shape1 = &rect;
    Shape* shape2 = &sq;

    cout << "Area of Rectangle: " << shape1->getArea() << endl;
    cout << "Area of Square: " << shape2->getArea() << endl;

    return 0;
}
