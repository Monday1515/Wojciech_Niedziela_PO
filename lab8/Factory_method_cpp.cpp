#include <iostream>
#include <string>

using namespace std;

class Vehicle {
public:
    virtual void create() = 0;
};

class Car : public Vehicle {
public:
    void create() override {
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
        if (type == "car") {
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
