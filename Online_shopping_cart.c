#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the items in the cart
struct Item {
    char name[50];
    float price;
    struct Item *next;
};

// Function to add an item to the cart
void addToCart(struct Item **cart, char itemName[], float itemPrice) {
    struct Item *newItem = (struct Item *)malloc(sizeof(struct Item));
    strcpy(newItem->name, itemName);
    newItem->price = itemPrice;
    newItem->next = NULL;

    if (*cart == NULL) {
        *cart = newItem;
    } else {
        struct Item *temp = *cart;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
}

// Function to display the contents of the cart
void displayCart(struct Item *cart) {
    printf("\nItems in the cart:\n");
    printf("------------------\n");
    struct Item *temp = cart;
    while (temp != NULL) {
        printf("Item: %s\n", temp->name);
        printf("Price: $%.2f\n", temp->price);
        printf("------------------\n");
        temp = temp->next;
    }
}

int main() {
    struct Item *cart = NULL;
    int choice;
    char itemName[50];
    float itemPrice;

    do {
        printf("Online Shopping Cart\n");
        printf("1. Add Item to Cart\n");
        printf("2. View Cart\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item name: ");
                scanf("%s", itemName);
                printf("Enter item price: ");
                scanf("%f", &itemPrice);
                addToCart(&cart, itemName, itemPrice);
                printf("Item added to cart!\n");
                break;
            case 2:
                displayCart(cart);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 3);

    // Free memory allocated for the cart items
    struct Item *temp = cart;
    while (temp != NULL) {
        struct Item *toFree = temp;
        temp = temp->next;
        free(toFree);
    }

    return 0;
}
