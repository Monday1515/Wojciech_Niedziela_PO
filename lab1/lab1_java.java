package Wojciech_Niedziela_PO.lab1;
class Car {
  // zmienne klasy Car
  private String make;
  private String model;
  private int year;
  private int CurrentYear;

  // konstruktor klasy Car
  public Car(String make, String model, int year, int CurrentYear)
  {
    this.make = make;
    this.model = model;
    this.year = year;
    this.CurrentYear = CurrentYear;
  }

  // metoda klasy Car
  void displayInfo()
  {
    System.out.println("Make: " + make);
    System.out.println("Model: " + model);
    System.out.println("Year: " + year);
  }

  int getCarAge()
  {
    return CurrentYear - year;
  }


  boolean isSameCar(Car OtherCar)
  {
    if (this.make.equals(OtherCar.make) && this.model.equals(OtherCar.model) && this.year == OtherCar.year)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  public static void main(String[] args) {
      
    //tworzenie obiektu klasy Car
    Car car1 = new Car("Toyota", "Corolla", 2020, 2024);
    Car car2 = new Car ("Toyota", "Corolla", 2020, 2024);
    Car car3 = new Car("Honda", "Civic", 2021, 2024);

    //wywołanie metody klasy Car
    car1.displayInfo();
    System.out.println("This car is " + car1.getCarAge() + " years old");
    car2.displayInfo();
    System.out.println("This car is " + car2.getCarAge() + " years old");
    car3.displayInfo();
    System.out.println("This car is " + car3.getCarAge() + " years old");


    if (car1.isSameCar(car2))
    {
      System.out.println("Car1 is the same as Car2");
    }
    else
    {
      System.out.println("Car1 is not the same as Car2");
    }

    if (car1.isSameCar(car3))
    {
      System.out.println("Car1 is the same as Car3");
    }
    else
    {
      System.out.println("Car1 is not the same as Car3");
    }


  }


}



    

