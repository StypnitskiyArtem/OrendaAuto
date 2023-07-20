#include "STANDART LIBRARIES.h"

int main() {
    int days, car, action;
    float total;
    char carList[5][10] = {"BMW", "Audi", "Mercedes", "Toyota", "Honda"};
    float carCost[5] = {2000, 1800, 2200, 1200, 1000};
    
    char selectedCar[10] = "";

    color();

    while (1) {
        system("cls||clear");
        printf("Choose an action:\n");
        printf("1. Select a car\n");
        printf("2. Show selected car\n");
        printf("3. Exit\n");
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
            printf("Goodbye!\n");
            break;
        }
        getchar();
        getchar();
    }
    return 0;
}
