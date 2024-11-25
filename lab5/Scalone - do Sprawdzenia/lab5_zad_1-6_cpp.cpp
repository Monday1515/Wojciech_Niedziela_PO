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

class Samochod : private Pojazd // w przeciwienstwie do protected, private nie pozwala na dostep
// do chronionych elementow klasy bazowej
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

        void pokazInformacjeSamochodu()
        {
            pokazInfo();   
        }
    
};


int main()
{
    Samochod mojSamochod("Ford", "Focus");

    // Próba dostępu do metod klasy bazowej
    // mojSamochod.pokazInformacje(); // Błąd: metoda jest prywatna w klasie Samochod
    mojSamochod.pokazDaneSamochodu(); // Dostęp poprzez metodę klasy Samochod
    mojSamochod.pokazInformacjeSamochodu(); // Dostęp poprzez "wrapper" metody w klasie Samochod


    return 0;
}