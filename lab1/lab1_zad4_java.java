package Wojciech_Niedziela_PO.lab1;
import java.util.Vector;

class Parrot {
    private Vector<String> phrazes = new Vector<String>();

    public Parrot(/*String phraze*/) {
        // this.phraze = phraze;
    }

    void say(int repeat) {
        int rnumber = (int) (Math.random() * phrazes.size());
        for (int i = 0; i < repeat; i++) {
            
            System.out.println(phrazes.get(rnumber));
        }
        
    }

    // void setPhraze(String Newphraze) {
    //     this.phraze = Newphraze;
    // }

    void addPhraze(String phraze) {
        phrazes.add(phraze);
    }





    public static void main(String[] args) {

        Parrot parrot = new Parrot();
        parrot.addPhraze("Hello");
        parrot.addPhraze("Bye");
    
    //Parrot parrot = new Parrot("Hello");
    parrot.say(2);  
    //parrot.addPhraze("Bye");
    parrot.say(3);
        
    }
}
