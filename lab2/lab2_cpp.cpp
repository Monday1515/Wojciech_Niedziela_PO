#include<iostream>
using namespace std;

class Samochód
{
    private:
        string marka;
        string model;
        int rokProdukcji;

    public: 
    Samochód(string marka, string model, int rokProdukcji)
    {
        this->marka = marka;
        this->model = model;
        this->rokProdukcji = rokProdukcji;
    }   
    Samochód()
    {
        this->marka = "nieznana marka";
        this->model = "nieznany, nieznany model";
        this->rokProdukcji = 0;
    }
    ~Samochód()
    {
        cout << "Destruktor wywolany dla " << marka <<" "<< model << endl; // informacja o likwidacji obiektu?
    }
};


class Tablica {
private:
    int* arr;       // wskaźnik na dynamiczną tablicę
    int size;       // rozmiar tablicy

public:
    // Konstruktor domyślny - alokuje tablicę o wielkości 10 elementów
    Tablica() {
        this->size = 10;
        this->arr = new int[size];  // dynamiczna alokacja pamięci
        cout << "Konstruktor domyslny: alokuje tablice o rozmiarze 10." << endl;
    }

    // Konstruktor z parametrem - alokuje tablicę o podanej wielkości
    Tablica(int s) {
        this->size = s;
        this->arr = new int[size];  // dynamiczna alokacja pamięci
        cout << "Konstruktor z parametrem: alokuje tablice o rozmiarze " << size << "." << endl;
    }

    // Destruktor - zwalnia dynamicznie alokowaną pamięć
    ~Tablica() {
        delete[] arr;  // zwalnianie pamięci
        cout << "Destruktor: zwalniam tablice o rozmiarze " << size << "." << endl;
    }

};


int main() // // Prosze tworzyc obiekty takze w pamieci dyamicznej
{
    Samochód();
    Samochód("Audi", "A4", 2010);
    Tablica();
    Tablica(5);
}
