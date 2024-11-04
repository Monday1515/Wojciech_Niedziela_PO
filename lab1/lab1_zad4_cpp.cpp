#include <iostream>     // oba rozwiazania poporawne
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Parrot {
    private:
        vector<string> phrases;  // Zbiór fraz

    public:
        // Konstruktor, który inicjalizuje generator losowy
        Parrot() {
            srand(time(0)); 
        }

        // Metoda do dodawania fraz do zbioru
        void addPhrase(string newPhrase) {
            phrases.push_back(newPhrase);
        }

        // Metoda wypowiadająca losową frazę określoną liczbę razy
        void say(int repeat) {
            if (phrases.empty()) {
                cout << "The parrot doesn't know any phrases!" << endl;
                return;
            }

            // Losowanie frazy ze zbioru
            int randomIndex = rand() % phrases.size();
            string selectedPhrase = phrases[randomIndex];

            // Wypowiadanie wybranej frazy określoną liczbę razy
            for (int i = 0; i < repeat; i++) {
                cout << selectedPhrase << endl;
            }
        }
};

int main() {
    Parrot myParrot;

    // Dodawanie fraz do zbioru papugi
    myParrot.addPhrase("Hello!");
    myParrot.addPhrase("Good morning!");
    myParrot.addPhrase("Good night!");

    // Papuga wypowiada losową frazę trzy razy
    myParrot.say(3);

    return 0;
}
