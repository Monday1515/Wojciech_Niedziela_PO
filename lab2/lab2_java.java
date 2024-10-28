package Wojciech_Niedziela_PO.lab2;
public class lab2_java{
    public static void main(String[] args){
        Samochód samochód1 = new Samochód("Fiat", "126p", 1973);
        Samochód samochód2 = new Samochód();
        samochód1.displayInfo();
        System.out.println();
        samochód2.displayInfo();

        @SuppressWarnings("unused")
        Tablica tablica1 = new Tablica();
        @SuppressWarnings("unused")
        Tablica tablica2 = new Tablica(20);
    }
}


class Samochód{

    private String marka;
    private String model;
    private int rokProdukcji;

    public Samochód(String marka, String model, int rokProdukcji){
        this.marka = marka;
        this.model = model;
        this.rokProdukcji = rokProdukcji;
    }

    public Samochód(){
        this.marka = "nieznana marka";
        this.model = "nieznany model";
        this.rokProdukcji = 0;
    }

    void displayInfo()
    {
        System.out.println("Marka: " + marka);
        System.out.println("Model: " + model);
        System.out.println("Rok produkcji: " + rokProdukcji);
    }


}

class Tablica {
    @SuppressWarnings("unused")
    private int[] arr;  // dynamicznie alokowana tablica int
    private int size;   // rozmiar tablicy

    // Konstruktor domyślny - alokuje tablicę o wielkości 10 elementów
    public Tablica() {
        this.size = 10;
        this.arr = new int[size];  // dynamiczna alokacja pamięci
        System.out.println("Konstruktor domyślny: alokuję tablicę o rozmiarze 10.");
    }

    // Konstruktor z parametrem - alokuje tablicę o podanej wielkości
    public Tablica(int s) {
        this.size = s;
        this.arr = new int[size];  // dynamiczna alokacja pamięci
        System.out.println("Konstruktor z parametrem: alokuję tablicę o rozmiarze " + size + ".");
    }

    // Finalizer (odradzane użycie)
    @Override
    protected void finalize() throws Throwable {
        System.out.println("Finalizer wywołany, zwalnianie zasobów.");
        super.finalize();
    }
}