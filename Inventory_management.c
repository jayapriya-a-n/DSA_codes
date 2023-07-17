/*Inventory Management: In a retail store, how would you use an array to manage the stock of different products?
For example, you need to keep track of the quantity and availability of each item.
Write a c program to execute the following using files store it in a file inventory.txt*/

#include <stdio.h>

#define MAX_PRODUCTS 100

// Structure to represent a product
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Product;

// Function to read product data from file
int readInventory(Product inventory[]) {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("Failed to open the inventory file.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%d %s %d %f", &inventory[count].id, inventory[count].name,
                  &inventory[count].quantity, &inventory[count].price) == 4) {
        count++;
    }

    fclose(file);
    return count;
}

// Function to write product data to file
void writeInventory(Product inventory[], int count) {
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("Failed to open the inventory file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %d %.2f\n", inventory[i].id, inventory[i].name,
                inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
}

int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;

    // Read existing inventory data from the file
    productCount = readInventory(inventory);

    // Display the current inventory
    printf("Current Inventory:\n");
    printf("------------------\n");
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d, Name: %s, Quantity: %d, Price: %.2f\n", inventory[i].id, inventory[i].name,
               inventory[i].quantity, inventory[i].price);
    }
    printf("\n");

    // Add a new product
    printf("Adding a new product...\n");
    Product newProduct;
    printf("Enter product ID: ");
    scanf("%d", &newProduct.id);
    printf("Enter product name: ");
    scanf("%s", newProduct.name);
    printf("Enter product quantity: ");
    scanf("%d", &newProduct.quantity);
    printf("Enter product price: ");
    scanf("%f", &newProduct.price);
    inventory[productCount] = newProduct;
    productCount++;

    // Write the updated inventory data to the file
    writeInventory(inventory, productCount);
    printf("Inventory updated and saved to file.\n");

    return 0;
}
