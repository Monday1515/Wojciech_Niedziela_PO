#include<iostream>  // poprawnie

using namespace std;

// Klasa użytkownika
class User {
private:
    string name;
    string surename;
    string mail;
public:
    User(const string name, const string surename, const string mail) 
    : name(name), surename(surename), mail(mail) {}

    string getName() const{
        return name;
    }
    
    string getSurename() const{
        return surename;
    }

    string getMail() const{
        return mail;
    }


};

// Klasa odpowiedzialna za zapis użytkownika
class UserSaver {
public:
    void saveUser(const User& user) {
        // Zapis do pliku
        cout << "Zapisano uzytkownika: " << user.getName() << " " << user.getSurename() << " " << user.getMail() 
        << endl;    
        
    }
};

int main() {
    
    User user("Wojciech", "Niedziela", "mail@gmail.com");
    UserSaver userSaver;
    
    userSaver.saveUser(user);

    return 0;
}
