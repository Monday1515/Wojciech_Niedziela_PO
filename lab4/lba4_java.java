class Pracownik
{
    protected String stanowisko;
    protected float wynagrodzenie;

    public Pracownik(String stanowisko, float wynagrodzenie)
    {
        this.stanowisko = stanowisko;
        this.wynagrodzenie = wynagrodzenie;
    }

}

class Nauczyciel extends Pracownik
{
    private String przedmiot;

    public Nauczyciel(String stanowisko, float wynagrodzenie, String przedmiot)
    {
        super(stanowisko, wynagrodzenie);
        this.przedmiot = przedmiot;
    }

    void getDane()
    {
        System.out.println("Stanowisko: " + stanowisko);
        System.out.println("Wynagrodzenie: " + wynagrodzenie);
        System.out.println("Przedmiot: " + przedmiot);
    }
}

class Administracja extends Pracownik
{
    private String obowiazki;

    public Administracja(String stanowisko, float wynagrodzenie, String obowiazki)
    {
        super(stanowisko, wynagrodzenie);
        this.obowiazki = obowiazki;
    }

    void getDane()
    {
        System.out.println("Stanowisko: " + stanowisko);
        System.out.println("Wynagrodzenie: " + wynagrodzenie);
        System.out.println("Obowiazki: " + obowiazki);
    }

}


class Osoba
{
    private String imie;
    private String nazwisko;
    private int wiek;
    private String mail;
    private String telefon;

    public Osoba(String imie, String nazwisko, int wiek, String mail, String telefon)
    {
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.wiek = wiek;
        this.mail = mail;
        this.telefon = telefon;
    }

    void GetImie()
    {
        System.out.println(imie);
    }

    void GetNazwisko()
    {
        System.out.println(nazwisko);
    }

    void GetWiek()
    {
        System.out.println(wiek);
    }

    void GetMail()
    {
        System.out.println(mail);
    }

    void GetTelefon()
    {
        System.out.println(telefon);
    }

    void SetImie(String imie)
    {
        this.imie = imie;
    }

    void SetNazwisko(String nazwisko)
    {
        this.nazwisko = nazwisko;
    }

    void SetWiek(int wiek)
    {
        this.wiek = wiek;
    }

    void SetMail(String mail)
    {
        if (mail.contains("@"))
        {
            this.mail = mail;
        }
        else
        {
            System.out.println("Niepoprawny adres email");
        }
    }

    void SetTelefon(String telefon)
    {
        if (telefon.length() == 9)
        {
            this.telefon = telefon;
        }
        else
        {
            System.out.println("Niepoprawny numer telefonu");
            
        }
    }
}

class Main
{
    public static void main(String[] args)
    {
        Osoba osoba = new Osoba("Wojciech", "Niedziela", 20, "wojciech.niedziel2005@gmail.com", "123456789");
        osoba.GetImie();
        osoba.GetNazwisko();
        osoba.GetWiek();
        osoba.GetMail();
        osoba.GetTelefon();
        osoba.SetImie("Jan");
        osoba.SetNazwisko("Kowalski");
        osoba.SetWiek(30);
        osoba.SetMail("testATgmail.com");
        osoba.SetTelefon("1234567890");

        Nauczyciel nauczyciel = new Nauczyciel("Nauczyciel", 3000, "Matematyka");
        nauczyciel.getDane();

        Administracja administracja = new Administracja("Administracja", 2000, "Sprzatanie");
        administracja.getDane();

    }
}