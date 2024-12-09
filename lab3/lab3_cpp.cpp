#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Klasa bazowa: Osoba
class Osoba {
protected:
    string imie;
    string nazwisko;

public:
    Osoba(string imie, string nazwisko) : imie(imie), nazwisko(nazwisko) {}

    string getFullName() const {
        return imie + " " + nazwisko;
    }
};

// Dziedziczenie: Klasy Nauczyciel i Uczeń
class Nauczyciel : public Osoba {
public:
    Nauczyciel(string imie, string nazwisko) : Osoba(imie, nazwisko) {}
};

class Uczen : public Osoba {
public:
    Uczen(string imie, string nazwisko) : Osoba(imie, nazwisko) {}
};

// Agregacja: Klasa Sala lekcyjna
class SalaLekcyjna {
private:
    string numerSali;

public:
    SalaLekcyjna(string numer) : numerSali(numer) {}

    string getNumerSali() const {
        return numerSali;
    }
};

// Kompozycja: Klasa Materiał
class Material {
private:
    string nazwaMaterialu;

public:
    Material(string nazwa) : nazwaMaterialu(nazwa) {}

    string getNazwaMaterialu() const {
        return nazwaMaterialu;
    }
};

// Klasa Kurs - centralny element systemu
class Kurs {
private:
    string nazwaKursu;
    Nauczyciel* nauczyciel;
    SalaLekcyjna* salaLekcyjna;
    vector<Uczen*> uczniowie;
    vector<Material> materialy;

public:
    Kurs(string nazwa) : nazwaKursu(nazwa), nauczyciel(nullptr), salaLekcyjna(nullptr) {}

    void assignTeacher(Nauczyciel* n) {
        nauczyciel = n;
    }

    void assignClassroom(SalaLekcyjna* sala) {
        salaLekcyjna = sala;
    }

    void addStudent(Uczen* uczen) {
        uczniowie.push_back(uczen);
    }

    void addMaterial(const Material& material) {
        materialy.push_back(material);
    }

    void displayDetails() const {
        cout << "Kurs: " << nazwaKursu << endl;
        if (nauczyciel) {
            cout << "Prowadzony przez: " << nauczyciel->getFullName() << endl;
        }
        if (salaLekcyjna) {
            cout << "Sala lekcyjna: " << salaLekcyjna->getNumerSali() << endl;
        }
        cout << "Lista uczniow: ";
        for (const auto& uczen : uczniowie) {
            cout << uczen->getFullName() << " ";
        }
        cout << endl;

        cout << "Materialy kursu: ";
        for (const auto& material : materialy) {
            cout << material.getNazwaMaterialu() << " ";
        }
        cout << endl;
    }
};

int main() {
    // Tworzenie obiektów
    Nauczyciel nauczyciel("Jan", "Kowalski");
    Uczen uczen1("Anna", "Nowak");
    Uczen uczen2("Adam", "Malysz");
    SalaLekcyjna sala("1");
    Material material1("PO - Lab 3");
    Material material2("PO - Lab 4");

    // Tworzenie kursu i dodawanie relacji
    Kurs kurs("PO");
    kurs.assignTeacher(&nauczyciel);
    kurs.assignClassroom(&sala);
    kurs.addStudent(&uczen1);
    kurs.addStudent(&uczen2);
    kurs.addMaterial(material1);
    kurs.addMaterial(material2);

    // Wyświetlanie szczegółów kursu
    kurs.displayDetails();

    return 0;
}
