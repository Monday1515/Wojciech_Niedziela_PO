// Interfejs Silnikowy
interface Silnikowy {
    void przyspiesz();
}

// Interfejs Elektryczny
interface Elektryczny {
    void ladowanie();
}

// Klasa Hybryda implementująca oba interfejsy
class Hybryda implements Silnikowy, Elektryczny {

    // Implementacja metody z interfejsu Silnikowy
    @Override
    public void przyspiesz() {
        System.out.println("Hybryda: Przyspieszanie za pomocą napędu hybrydowego!");
    }

    // Implementacja metody z interfejsu Elektryczny
    @Override
    public void ladowanie() {
        System.out.println("Hybryda: Ładowanie baterii elektrycznej!");
    }

    // Dodatkowa metoda pokazująca funkcje
    public void pokazFunkcje() {
        System.out.println("Hybryda: Łączy funkcjonalność napędu spalinowego i elektrycznego.");
    }
}

// Klasa główna
class Main {
    public static void main(String[] args) {
        Hybryda mojPojazd = new Hybryda();

        // Wywołanie metod implementowanych przez klasę Hybryda
        mojPojazd.przyspiesz();
        mojPojazd.ladowanie();
        mojPojazd.pokazFunkcje();
    }
}
