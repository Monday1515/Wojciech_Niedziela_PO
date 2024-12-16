#include <iostream>
#include <string>

using namespace std;

// Interfejs rabatu
class Discount {
public:
    virtual double calculateDiscount(double price) const = 0;  // Wirtualna funkcja obliczająca rabat
    virtual ~Discount() = default;  // Wirtualny destruktor
};

// Regularny rabat (10%)
class RegularDiscount : public Discount {
public:
    double calculateDiscount(double price) const override {
        return price * 0.10;  // 10% rabatu
    }
};

// Sezonowy rabat (20%)
class SeasonalDiscount : public Discount {
public:
    double calculateDiscount(double price) const override {
        return price * 0.20;  // 20% rabatu
    }
};

// Klasa reprezentująca produkt
class Product {
private:
    double price;
    string name;

public:
    Product(double price, const string& name)
        : price(price), name(name) {}

    double getPrice() const {
        return price;
    }

    string getName() const {
        return name;
    }

    void applyDiscount(const Discount& discount) {
        double discountAmount = discount.calculateDiscount(price);
        cout << "Product: " << name << ", Original Price: " << price << endl;
        cout << "Discount Applied: " << discountAmount << endl;
        cout << "Final Price: " << (price - discountAmount) << endl;
    }
};

int main() {
    Product product(100.0, "Phone");

    // Tworzymy obiekty rabatów
    RegularDiscount regularDiscount;
    SeasonalDiscount seasonalDiscount;

    // Zastosowanie rabatów
    cout << "\nApplying Regular Discount:" << endl;
    product.applyDiscount(regularDiscount);

    cout << "\nApplying Seasonal Discount:" << endl;
    product.applyDiscount(seasonalDiscount);

    return 0;
}
