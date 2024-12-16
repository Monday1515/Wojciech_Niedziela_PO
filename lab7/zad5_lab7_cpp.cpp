#include <iostream>
#include <string>
using namespace std;

// Interfejs usługi wiadomości
class MessageService {
public:
    virtual void sendMessage(const string& message) const = 0;
    virtual ~MessageService() = default;
};

// Implementacja EmailService
class EmailService : public MessageService {
public:
    void sendMessage(const string& message) const override {
        cout << "Sending Email: " << message << endl;
    }
};

// Klasa powiadomień, która zależy od MessageService (abstrakcji)
class Notification {
private:
    MessageService& messageService;

public:
    Notification(MessageService& service) : messageService(service) {}

    void notify(const string& message) const {
        messageService.sendMessage(message);
    }
};

int main() {
    EmailService emailService;
    Notification notification(emailService);

    notification.notify("Hello from SOLID!");
    return 0;
}
