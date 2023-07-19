#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define FILENAME "users.bin"

typedef struct {
    char username[20];
    char password[20];
} User;

void color()
{
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

int checkUser(char *username, char *password) {
    FILE *fp;
    User user;
    int found = 0;

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    while (fread(&user, sizeof(User), 1, fp)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);
    return found;
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

    fwrite(&user, sizeof(User), 1, fp);
    fclose(fp);
}

int main() {
    int days, car, action;
    float total;
    char carList[5][10] = {"BMW", "Audi", "Mercedes", "Toyota", "Honda"};
    float carCost[5] = {2000, 1800, 2200, 1200, 1000};
    char selectedCar[10] = "";
    char username[20], password[20];

    color();

    while (1) {
        system("cls||clear");
        printf("Choose an action:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        action = getch() - '0';
        system("cls||clear");
        if (action == 1) {
            registerUser();
            printf("Registration successful!\n");
        } else if (action == 2) {
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");
            scanf("%s", password);

            if (checkUser(username, password)) {
                printf("Login successful!\n");

                while (1) {
                    system("cls||clear");
                    printf("Choose an action:\n");
                    printf("1. Select a car\n");
                    printf("2. Show selected car\n");
                    printf("3. Logout\n");
                    action = getch() - '0';
                    system("cls||clear");
                    if (action == 1) {
                        printf("Select a car:\n");
                        for (int i = 0; i < 5; i++) {
                            printf("%d. %s (%.2f Grivnas/day)\n", i+1, carList[i], carCost[i]);
                        }
                        car = getch() - '0';
                        strcpy(selectedCar, carList[car-1]);
                        system("cls||clear");
                        printf("You have selected: %s\n", selectedCar);
                        printf("Enter the number of rental days: ");
                        scanf("%d", &days);
                        system("cls||clear");
                        total = days * carCost[car-1];
                        system("cls||clear");
                        printf("Total rental cost: %.2f Grivnas\n", total);
                    } else if (action == 2) {
                        if (strlen(selectedCar) == 0) {
                            printf("You don't have any cars, would you like to rent one?\n");
                        } else {
                            printf("Your selected car: %s\n", selectedCar);
                        }
                    } else if (action == 3) {
                        break;
                    }
                    getchar();
                    getchar();
                }
            } else {
                printf("Invalid username or password!\n");
            }
        } else if (action == 3) {
            printf("Goodbye!\n");
            break;
        }
        getchar();
        getchar();
    }
    return 0;
}
