#include<iostream>
#include<string>
using namespace std;

class Pracownik
{
    protected:
        string stanowisko;
        float wynagrodzenie;

    public:
        Pracownik(string stanowisko, float wynagrodzenie)
        {
            this->stanowisko = stanowisko;
            this->wynagrodzenie = wynagrodzenie;
        };

        virtual void GetDane() const {
            cout << "Stanowisko: " << stanowisko << endl;
            cout << "Wynagrodzenie: " << wynagrodzenie << endl;
        }

    virtual ~Pracownik() {}


};

class Nauczyciel : public Pracownik
{
    private:
        string przedmiot;

    public:
        Nauczyciel(string stanowisko, float wynagrodzenie, string przedmiot) : Pracownik(stanowisko, wynagrodzenie)
        {
            this->przedmiot = przedmiot;
        };

        void GetDane() const override   // ta metoda powinna zostać zdefiniowana jako (ew. czysto) wirtualna w klasie Pracownik
        {
            cout << "Stanowisko: " << stanowisko << endl;
            cout << "Wynagrodzenie: " << wynagrodzenie << endl;
            cout << "Przedmiot: " << przedmiot << endl;
        };
};

class Administracja : public Pracownik
{
    private:
        string obowiazki;

    public:
        Administracja(string stanowisko, float wynagrodzenie, string obowiazki) : Pracownik(stanowisko, wynagrodzenie)
        {
            this->obowiazki = obowiazki;
        };

        void GetDane() const override
        {
            cout << "Stanowisko: " << stanowisko << endl;
            cout << "Wynagrodzenie: " << wynagrodzenie << endl;
            cout << "Obowiazki: " << obowiazki << endl;
        };
};

class Osoba
{
    private:
        string imie;
        string nazwisko;
        int wiek;
        string email;
        string telefon;

    public:
        Osoba(string imie, string nazwisko, int wiek, string email, string telefon)
        {
            this->imie = imie;
            this->nazwisko = nazwisko;
            this->wiek = wiek;
            SetEmail(email);
            SetTelefon(telefon);
        };
        
        void GetImie()
        {
            cout << "Imie: " << imie << endl;
        };

        void GetNazwisko()
        {
            cout << "Nazwisko: " << nazwisko << endl;
        };

        void GetWiek()
        {
            cout << "Wiek: " << wiek << endl;
        };

        void GetEmail()
        {
            cout << "Email: " << email << endl;
        };

        void GetTelefon()
        {
            cout << "Telefon: " << telefon << endl;
        };

        void SetImie(string imie)
        {
            this->imie = imie;
        };

        void SetNazwisko(string nazwisko)
        {
            this->nazwisko = nazwisko;
        };

        void SetWiek(int wiek)
        {
            this->wiek = wiek;
        };

        void SetEmail(string email)
        {
            if (email.find("@") == string::npos)
            {
                cout << "Niepoprawny email" << endl;
                return;
            };
            this->email = email;
        };

        void SetTelefon(string telefon)
        {
            if (telefon.length() != 9)
            {
                cout << "Niepoprawny numer telefonu" << endl;
                return;
            };
            this->telefon = telefon;
        };


};


int main()
{    
    // Tworzenie obiektów dynamicznie
    Osoba* osoba1 = new Osoba("Jan", "Kowalski", 30, "test@gmail.com", "123456789");
    osoba1->GetImie();
    osoba1->GetNazwisko();
    osoba1->GetWiek();
    osoba1->GetEmail();
    osoba1->GetTelefon();

    osoba1->SetImie("Adam");
    osoba1->SetNazwisko("Nowak");
    osoba1->SetWiek(40);
    osoba1->SetEmail("wwwATgmail.com");
    osoba1->SetTelefon("9876543210");

    // Tworzenie obiektów nauczyciela i administracji
    Pracownik* nauczyciel1 = new Nauczyciel("Nauczyciel", 3000, "Matematyka");
    nauczyciel1->GetDane();

    Pracownik* administracja1 = new Administracja("Administracja", 2000, "Sprzątanie");
    administracja1->GetDane();

    // Usuwanie obiektów dynamicznych
    delete osoba1;
    delete nauczyciel1;
    delete administracja1;

    return 0;
}
