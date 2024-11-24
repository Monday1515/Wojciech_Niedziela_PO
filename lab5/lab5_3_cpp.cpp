#include<iostream>

using namespace std;


class Pojazd
{
    public:

        Pojazd()
        {
            cout << "Konstruktor klasy Pojazd" << endl;
        }

        virtual void przyspiesz()
        {
            cout << "Przyspiesz!" << endl;
        }

        
        void zatrzymaj()
        {
            cout << "Pojazd zatrzymuje się" << endl;
        }
    
    

};

class Samochod : public Pojazd
{
    public:

        Samochod()
        {
            cout << "Konstruktor klasy Samochod" << endl;
        }

        void przyspiesz() override
        {
            cout << "Samochod przyspiesza" << endl;
        }
    
};

class Rower : public Pojazd
{
    public:
        
        Rower()
        {
            cout << "Konstruktor klasy Rower" << endl;
        }

        void przyspiesz() override
        {
            cout << "Rower przyspiesza" << endl;
        }
    
};


int main()
{
    Pojazd* pojazd = new Pojazd();
    pojazd->przyspiesz();

    Pojazd* samochod = new Samochod();
    samochod->przyspiesz();

    Pojazd* rower = new Rower();
    rower->przyspiesz();

    // delete pojazd;
    // delete samochod;
    // delete rower;

    return 0;
}