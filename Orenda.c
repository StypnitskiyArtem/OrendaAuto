#include "STANDART LIBRARIES.h"

int checkUser(char *username, char *password, User *user) {
    FILE *fp;
    int found = 0;

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    while (fread(user, sizeof(User), 1, fp)) {
        if (strcmp(user->username, username) == 0 && strcmp(user->password, password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);
    return found;
}


int main() {
    int days, car, action;
    float total;
    char carList[5][10] = {"BMW", "Audi", "Mercedes", "Toyota", "Honda"};
    float carCost[5] = {2000, 1800, 2200, 1200, 1000};
    char selectedCar[10] = "";
    char username[20], password[20];
    User user;

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

            if (checkUser(username, password, &user)) {
                printf("Login successful!\n");

                while (1) {
                    system("cls||clear");
                    printf("Choose an action:\n");
                    printf("1. Select a car\n");
                    printf("2. Show rented cars\n");
                    printf("3. Delete rented car\n");
                    printf("4. Logout\n");
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
                        getchar();
                        strcpy(user.rentedCars[user.rentedCarCount++], selectedCar);
                        updateUser(&user);
                    } else if (action == 2) {
                        if (user.rentedCarCount == 0) {
                            printf("You don't have any rented cars, would you like to rent one?\n");
                        } else {
                            printf("Your rented cars:\n");
                            for (int i = 0; i < user.rentedCarCount; i++) {
                                printf("%d. %s\n", i+1, user.rentedCars[i]);
                            }
                        }
                    } else if (action == 3) {
                        if (user.rentedCarCount == 0) {
                            printf("You don't have any rented cars to delete!\n");
                        } else {
                            printf("Select a car to delete:\n");
                            for (int i = 0; i < user.rentedCarCount; i++) {
                                printf("%d. %s\n", i+1, user.rentedCars[i]);
                            }
                            car = getch() - '0';
                            for (int i = car-1; i < user.rentedCarCount-1; i++) {
                                strcpy(user.rentedCars[i], user.rentedCars[i+1]);
                            }
                            user.rentedCarCount--;
                            updateUser(&user);
                        }
                    } else if (action == 4) {
                        break;
                    }
                    getchar();
                    
                }
            } else {
                printf("Invalid username or password!\n");
            }
        } else if (action == 3) {
            printf("Goodbye!\n");
            getchar();
            getchar();
            break;
        }
        getchar();
        getchar();
    }
    return 0;
}
