#include<iostream>

using namespace std;


class Silnikowy {
    public:

        string marka;
        string model;

        Silnikowy(string marka, string model) : marka(marka), model(model) {}

        void przyspiesz() {
            cout << "Przyspieszam, silnikiem spalinowym!" << endl;
        }
};

class Elektryczny {
    public:

        string marka;
        string model;

        Elektryczny(string marka, string model) : marka(marka), model(model) {}

        void przyspiesz() {
            cout << "Przyspieszam, silnikiem elektrycznym!" << endl;
        }
};

class Hybryda : public Silnikowy, public Elektryczny {
    public:

        string marka;
        string model;
        
        Hybryda(string marka, string model) : Silnikowy(marka, model), Elektryczny(marka, model) {}

        void przyspiesz() {
            cout << "Przyspieszam, silnikiem hybrydowym!" << endl;
        }

        void pokazFunkcje() {
            Silnikowy::przyspiesz();
            Elektryczny::przyspiesz();
            przyspiesz();
        }
};


int main()
{
    Hybryda samochod("Toyota", "Prius");
    
    samochod.pokazFunkcje();

    return 0;
}