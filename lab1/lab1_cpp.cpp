#include <iostream>
#include <string>

using namespace std;

class Car {
    // Atrybuty klasy Car
    private:
        string make; // marka
        string model; // model
        int year; // rok produkcji
        int currentYear;

    public:
        // Konstruktor klasy Car
        Car(string carMake, string carModel, int carYear, int currYear) {
            make = carMake;
            model = carModel;
            year = carYear;
            currentYear = currYear;
        }

        // Metoda do wyświetlania informacji o samochodzie
        void displayInfo() {
            cout << "Make: " << make << endl;
            cout << "Model: " << model << endl;
            cout << "Year: " << year << endl;
        }

        // Metoda do obliczania wieku samochodu
        int getCarAge() {
            return currentYear - year;
        }

        // Metoda do porównywania dwóch samochodów
        bool isSameCar(Car otherCar) {
            return (make == otherCar.make && model == otherCar.model && year == otherCar.year);
        }
};

int main() {
    // Tworzenie obiektów klasy Car
    Car car1("Toyota", "Corolla", 2020, 2024);
    Car car2("Toyota", "Corolla", 2020, 2024);
    Car car3("Honda", "Civic", 2020, 2024);

    cout << "Car 1:" << endl;
    car1.displayInfo();
    cout << "This car is " << car1.getCarAge() << " years old" << endl;

    
    cout << "Car 2:" << endl;
    car2.displayInfo();
    cout << "This car is " << car2.getCarAge() << " years old" << endl;

    cout << "Car 3:" << endl;
    car3.displayInfo();
    cout << "This car is " << car3.getCarAge() << " years old" << endl;

    if (car1.isSameCar(car2)) {
        cout << "Car 1 and Car 2 are the same." << endl;
    } else {
        cout << "Car 1 and Car 2 are different." << endl;
    }

    if (car1.isSameCar(car3)) {
        cout << "Car 1 and Car 3 are the same." << endl;
    } else {
        cout << "Car 1 and Car 3 are different." << endl;
    }

    return 0;
}
