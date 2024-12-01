#include<iostream>

using namespace std;


class Pojazd
{
    protected:

        string marka;
        string model;


    public:

        Pojazd(string marka, string model)
        {
            this->marka = marka;
            this->model = model;
            cout << "Konstruktor klasy Pojazd" << endl;
        }

        void pokazInfo()
        {
            cout << "Marka: " << marka << ", Model: " << model << endl;
        }
    
    

};

class Samochod : protected Pojazd
{
    public:

        Samochod(string marka, string model) : Pojazd(marka, model)
        {
            cout << "Konstruktor klasy Samochod" << endl;
        }

        void pokazDaneSamochodu() 
        {
            // Dostęp do chronionych elementów klasy bazowej
            cout << "Dane samochodu -> Marka: " << marka << ", Model: " << model << endl;
        }
    
};


int main()
{
    // Tworzenie obiektu klasy Samochod
    Samochod mojSamochod("Toyota", "Corolla");

    // Próba dostępu do metod klasy bazowej
    //mojSamochod.pokazInformacje(); // Błąd: metoda jest chroniona przez dziedziczenie chronione // pokazInfo()

    // Wywołanie metody klasy Samochod, która korzysta z chronionych elementów
    mojSamochod.pokazDaneSamochodu();


    return 0;
}
