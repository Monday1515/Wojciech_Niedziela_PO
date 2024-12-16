#include <iostream>
using namespace std;

// Interfejs dla drukarki
class Printer {
public:
    virtual void print() const = 0;
    virtual ~Printer() = default;
};

// Interfejs dla skanera
class Scanner {
public:
    virtual void scan() const = 0;
    virtual ~Scanner() = default;
};

// Wielofunkcyjna maszyna
class MultiFunctionMachine : public Printer, public Scanner {
public:
    void print() const override {
        cout << "Printing document..." << endl;
    }

    void scan() const override {
        cout << "Scanning document..." << endl;
    }
};

int main() {
    MultiFunctionMachine mfm;
    mfm.print();
    mfm.scan();
    return 0;
}
