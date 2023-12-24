#include <iostream>
#include <vector>
#include <string>
using namespace std;

class User {
public:
    User(const string& username, const string& password, const string& name)
        : username(username), password(password), name(name) {}

    const string& getUsername() const { return username; }
    const string& getName() const { return name; }
    const string& getPassword() const { return password; }

private:
    string username;
    string password;
    string name;
};

class Chat {
public:
    void registerUser(const string& username, const string& password, const string& name) {
        users.push_back(User(username, password, name));
        cout << "Пользователь " << username << " зарегистрирован." << endl;
    }

    vector<User>::iterator login(const string& username, const string& password) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->getUsername() == username && it->getPassword() == password) {
                cout << "Пользователь " << username << " вошел в систему." << endl;
                return it;
            }
        }
        cout << "Неверные логин или пароль." << endl;
        return users.end();
    }

    void sendMessage(User& sender, const string& recipient, const string& message) {
        messages.push_back({ sender, recipient, message });
        cout << sender.getName() << " отправил сообщение для " << recipient << ": " << message << endl;
    }

    void broadcastMessage(User& sender, const string& message) {
        messages.push_back({ sender, "", message });
        cout << sender.getName() << " отправил групповое сообщение: " << message << endl;
    }

    void showAllMessages() const {
        cout << "Все сообщения в чате:" << endl;
        for (const auto& message : messages) {
            cout << "[" << message.sender.getName() << " -> " << message.recipient << "]: "
                << message.content << endl;
        }
    }

private:
    vector<User> users;

    struct Message {
        User sender;
        string recipient;
        string content;
    };

    vector<Message> messages;
};

int main() {
    setlocale(LC_ALL, "RU");

    Chat chat;

    int choice;
    vector<User>::iterator currentUser = chat.login("", "");

    do {
        cout << "1 - Регистрация, 2 - Вход, 3 - Отправить сообщение, 4 - Отправить групповое сообщение, 5 - Показать все сообщения, 0 - Выйти" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            string username, password, name;
            cout << "Введите логин: ";
            cin >> username;
            cout << "Введите пароль: ";
            cin >> password;
            cout << "Введите имя: ";
            cin.ignore();
            getline(cin, name);
            chat.registerUser(username, password, name);
        }
        break;
        case 2:
        {
            string username, password;
            cout << "Введите логин: ";
            cin >> username;
            cout << "Введите пароль: ";
            cin >> password;
            auto userIterator = chat.login(username, password);
            if (userIterator != chat.login("", "")) {
                currentUser = userIterator;
            }
        }
        break;
        case 3:
            if (currentUser != chat.login("", "")) {
                string recipient, message;
                cout << "Введите получателя: ";
                cin >> recipient;
                cout << "Введите сообщение: ";
                cin.ignore();
                getline(cin, message);
                chat.sendMessage(*currentUser, recipient, message);
            }
            else {
                cout << "Сначала войдите в систему." << endl;
            }
            break;
        case 4:
            if (currentUser != chat.login("", "")) {
                string message;
                cout << "Введите сообщение: ";
                cin.ignore();
                getline(cin, message);
                chat.broadcastMessage(*currentUser, message);
            }
            else {
                cout << "Сначала войдите в систему." << endl;
            }
            break;
        case 5:
            chat.showAllMessages();
            break;
        default:
            break;
        }

    } while (choice != 0);

    return 0;
}
