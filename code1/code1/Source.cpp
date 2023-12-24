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
        cout << "������������ " << username << " ���������������." << endl;
    }

    vector<User>::iterator login(const string& username, const string& password) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->getUsername() == username && it->getPassword() == password) {
                cout << "������������ " << username << " ����� � �������." << endl;
                return it;
            }
        }
        cout << "�������� ����� ��� ������." << endl;
        return users.end();
    }

    void sendMessage(User& sender, const string& recipient, const string& message) {
        messages.push_back({ sender, recipient, message });
        cout << sender.getName() << " �������� ��������� ��� " << recipient << ": " << message << endl;
    }

    void broadcastMessage(User& sender, const string& message) {
        messages.push_back({ sender, "", message });
        cout << sender.getName() << " �������� ��������� ���������: " << message << endl;
    }

    void showAllMessages() const {
        cout << "��� ��������� � ����:" << endl;
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
        cout << "1 - �����������, 2 - ����, 3 - ��������� ���������, 4 - ��������� ��������� ���������, 5 - �������� ��� ���������, 0 - �����" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            string username, password, name;
            cout << "������� �����: ";
            cin >> username;
            cout << "������� ������: ";
            cin >> password;
            cout << "������� ���: ";
            cin.ignore();
            getline(cin, name);
            chat.registerUser(username, password, name);
        }
        break;
        case 2:
        {
            string username, password;
            cout << "������� �����: ";
            cin >> username;
            cout << "������� ������: ";
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
                cout << "������� ����������: ";
                cin >> recipient;
                cout << "������� ���������: ";
                cin.ignore();
                getline(cin, message);
                chat.sendMessage(*currentUser, recipient, message);
            }
            else {
                cout << "������� ������� � �������." << endl;
            }
            break;
        case 4:
            if (currentUser != chat.login("", "")) {
                string message;
                cout << "������� ���������: ";
                cin.ignore();
                getline(cin, message);
                chat.broadcastMessage(*currentUser, message);
            }
            else {
                cout << "������� ������� � �������." << endl;
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
