#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

struct Password {
    char username[50];
    char password[50];
    int isOccupied;
};

struct Password passwordTable[SIZE];

int hash(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }
    return hash % SIZE;
}

void insertPassword(char *username, char *password) {
    int index = hash(username);
    while (passwordTable[index].isOccupied) {
        index = (index + 1) % SIZE;
    }
    strcpy(passwordTable[index].username, username);
    strcpy(passwordTable[index].password, password);
    passwordTable[index].isOccupied = 1;
}

void deletePassword(char *username) {
    int index = hash(username);
    while (strcmp(passwordTable[index].username, username) != 0) {
        index = (index + 1) % SIZE;
    }
    passwordTable[index].isOccupied = 0;
}

void displayPasswords() {
    printf("Stored Passwords:\n");
    for (int i = 0; i < SIZE; i++) {
        if (passwordTable[i].isOccupied) {
            printf("Username: %s\tPassword: %s\n", passwordTable[i].username, passwordTable[i].password);
        }
    }
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        passwordTable[i].isOccupied = 0;
    }

    int choice;
    char username[50], password[50];

    do {
        printf("\n1. Insert Password\n");
        printf("2. Delete Password\n");
        printf("3. Display Passwords\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                insertPassword(username, password);
                printf("Password inserted.\n");
                break;
            case 2:
                printf("Enter username to delete: ");
                scanf("%s", username);
                deletePassword(username);
                printf("Password deleted.\n");
                break;
            case 3:
                displayPasswords();
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
