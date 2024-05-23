#include <iostream>
#include <vector>
#include <string>

class User {
protected:
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    std::string group;
    std::string account;
    std::string accountType;

public:
    User(std::string ln, std::string fn, std::string p, std::string g, std::string a, std::string at)
        : lastName(ln), firstName(fn), patronymic(p), group(g), account(a), accountType(at) {}

    virtual void display() const {
        std::cout << "Last Name: " << lastName << ", First Name: " << firstName 
                  << ", Patronymic: " << patronymic << ", Group: " << group 
                  << ", Account: " << account << ", Account Type: " << accountType << std::endl;
    }

    virtual ~User() {}
};

class SpecializedUser : public User {
private:
    std::string ipAddress;
    std::string macAddress;

public:
    SpecializedUser(std::string ln, std::string fn, std::string p, std::string g, std::string a, std::string at, std::string ip, std::string mac)
        : User(ln, fn, p, g, a, at), ipAddress(ip), macAddress(mac) {}

    void display() const override {
        User::display();
        std::cout << "IP Address: " << ipAddress << ", MAC Address: " << macAddress << std::endl;
    }
};

class UserDatabase {
private:
    std::vector<User*> users;

public:
    ~UserDatabase() {
        for (User* user : users) {
            delete user;
        }
    }

    void addUser(User* user) {
        users.push_back(user);
    }

    void removeUser(int index) {
        if (index >= 0 && index < users.size()) {
            delete users[index];
            users.erase(users.begin() + index);
        }
    }

    void displayUsers() const {
        for (const User* user : users) {
            user->display();
            std::cout << "-------------------" << std::endl;
        }
    }
};

int main() {
    UserDatabase db;
    db.addUser(new User("Ivanov", "Ivan", "Ivanovich", "Group1", "ivanov", "admin"));
    db.addUser(new SpecializedUser("Petrov", "Petro", "Petrovich", "Group2", "petrov", "user", "192.168.1.1", "00:1A:2B:3C:4D:5E"));

    std::cout << "All users:" << std::endl;
    db.displayUsers();

    db.removeUser(0);

    std::cout << "After removing the first user:" << std::endl;
    db.displayUsers();

    return 0;
}
