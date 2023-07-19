#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define FILENAME "users.bin"
#define MAX_CARS 10

typedef struct {
    char username[20];
    char password[20];
    char rentedCars[MAX_CARS][10];
    int rentedCarCount;
} User;

void color()
{
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void updateUser(User *user) {
    FILE *fp;
    User tempUser;

    fp = fopen(FILENAME, "r+b");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    while (fread(&tempUser, sizeof(User), 1, fp)) {
        if (strcmp(tempUser.username, user->username) == 0 && strcmp(tempUser.password, user->password) == 0) {
            fseek(fp, -(long)sizeof(User), SEEK_CUR);
            fwrite(user, sizeof(User), 1, fp);
            break;
        }
    }

    fclose(fp);
}

void registerUser() {
    FILE *fp;
    User user;

    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    printf("Enter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    scanf("%s", user.password);
    user.rentedCarCount = 0;

    fwrite(&user, sizeof(User), 1, fp);
    fclose(fp);
}