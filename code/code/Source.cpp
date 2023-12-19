#include <iostream>
#include <vector>

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

    User* login(const string& username, const string& password) {
        for (auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                cout << "Пользователь " << username << " вошел в чат." << endl;
                return &user;
            }
        }
        cout << "Неверные логин или пароль." << endl;
        return nullptr;
    }

    void sendMessage(const User& sender, const string& recipient, const string& message) {
        messages.push_back({ sender, recipient, message });
        cout << sender.getName() << " отправил сообщение для " << recipient << ": " << message << endl;
    }

    void broadcastMessage(const User& sender, const string& message) {
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

    chat.registerUser("user1", "password1", "User One");
    chat.registerUser("user2", "password2", "User Two");

    User* currentUser1 = chat.login("user1", "password1");
    User* currentUser2 = chat.login("user2", "password2");

    if (currentUser1 && currentUser2) {
        chat.sendMessage(*currentUser1, "user2", "Привет, как дела?");
        chat.sendMessage(*currentUser2, "user1", "Привет! Все хорошо, спасибо.");

        chat.broadcastMessage(*currentUser1, "Это групповое сообщение от user1.");
        chat.broadcastMessage(*currentUser2, "Это групповое сообщение от user2.");

        chat.showAllMessages();



        return 0;
    }

    return 1;
}
