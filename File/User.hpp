#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>


typedef struct _User {
    int score;
    std::string name;
} User;

class UserTable {
private:
    int total_user;
    User *table;
    int capacity = 100;
    void resizeTable(void);
public:
    UserTable(void);
    void Update(void);
    void clearTable();
    void Save(void);
    void Sort(void);
    void AddNewUser(User newuser);
    User& operator[](int idx);
    int size (void);
    void GiveName(std::string name);
    friend std::istream &operator>>(std::istream &in, User &user);
    friend std::ostream &operator<<(std::ostream &out, User &user);
};
#endif
