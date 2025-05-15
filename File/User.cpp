#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#include "File/User.hpp"


UserTable::UserTable(void) {
    std::cout << "init user table" << std::endl;
    FILE *fr = fopen("Resource/scoreboard.txt", "r");


    capacity = 100;
    if (fr) {
        int init_user;
        fscanf(fr, "%d\n", &init_user);
        std::cout << "new user table" << std::endl;
        table = new User[capacity];
        std::cout << "total user " << total_user << std::endl;
        for (int i = 0; i < init_user; i++) {
            char tempname[500];
            int tempscore;
            fscanf(fr, "%s %d\n", tempname, &tempscore);
            User tempUser;
            tempUser.name = tempname;
            tempUser.score = tempscore;
            std::cout << "add new user " << i + 1 << std::endl;
            AddNewUser(tempUser);
        }
    }

    
    fclose(fr);
    Sort();
}
void UserTable::clearTable(void) {
    total_user = 0;
}
void UserTable::Update(void) {
    clearTable();

    FILE *fr = fopen("Resource/scoreboard.txt", "r");

    if (fr) {
        int now_user;
        fscanf(fr, "%d\n", &now_user);
        table = new User[capacity];
        for (int i = 0; i < now_user; i++) {
            char tempname[500];
            int tempscore;
            fscanf(fr, "%s %d\n", tempname, &tempscore);
            User tempUser;
            tempUser.name = tempname;
            tempUser.score = tempscore;
            AddNewUser(tempUser);
        }
    }

    fclose(fr);
    Sort();
}
void UserTable::Save(void) {
    FILE *fw = fopen("Resource/scoreboard.txt", "w");

    fprintf(fw, "%d\n", total_user);

    for (int i = 0; i < total_user; i++) {
        fprintf(fw, "%s %d\n", table[i].name.data(), table[i].score);
    }

    fclose(fw);
}
void UserTable::Sort(void) {
    std::sort(table, table + total_user, [](User u1, User u2) {
        return u1.score > u2.score;
    });
}
User& UserTable::operator[](int idx) {
    return table[idx];
}
int UserTable::size() {
    return total_user;
}
void UserTable::resizeTable(void) {
    capacity *= 2;
    User *temp = table;
    table = new User[capacity];
    memcpy((void*) table, temp, total_user * sizeof(User));
    delete[] temp;
}
void UserTable::AddNewUser(User newuser) {
    if (total_user == capacity) {
        resizeTable();
    }
    table[total_user++] = newuser;
}
void UserTable::GiveName(std::string name) {
    if (name != "") {
        for (int i = 0; i < total_user; i++) {
            if (table[i].name == "[]") {
                table[i].name = name;
            }
        }
    }
}
