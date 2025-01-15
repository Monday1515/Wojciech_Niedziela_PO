#include <iostream>
#include <string>

using namespace std;

class Vehicle {
public:
    virtual void create() = 0;
};

class Car : public Vehicle {
public:
    void create() override { // ta metoda powinna być zdefiniowana w klasie VehicleFactory i pochodnych 
        cout << "Samochod stworzony" << endl;
    }
};

class Bike : public Vehicle {
public:
    void create() override {
        cout << "Rower stworzony" << endl;
    }
};

class VehicleFactory {   
public:
    Vehicle* createVehicle(const string& type) {
        if (type == "car") { // przydałyby się klasy pochodne w miejsce tej instrukcji warunkowej (zasda open/closed)
            return new Car();
        } else if (type == "bike") {
            return new Bike();
        }
        return nullptr;
    }
};

int main() {
    VehicleFactory factory;
    Vehicle* vehicle1 = factory.createVehicle("car");
    Vehicle* vehicle2 = factory.createVehicle("bike");
    vehicle1->create();
    vehicle2->create();
    delete vehicle1;
    delete vehicle2;
    return 0;
}
