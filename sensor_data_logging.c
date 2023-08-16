#include <stdio.h>
#include <stdlib.h>

// Structure to hold sensor data
struct SensorData {
    int value;
    struct SensorData* next;
};

// Function to add sensor data to the linked list
void addSensorData(struct SensorData** head, int value) {
    struct SensorData* newSensorData = (struct SensorData*)malloc(sizeof(struct SensorData));
    newSensorData->value = value;
    newSensorData->next = *head;
    *head = newSensorData;
}

// Function to print the sensor data
void printSensorData(struct SensorData* head) {
    printf("Sensor Data:\n");
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct SensorData* head = NULL;
    int value;

    while (1) {
        printf("Enter sensor value (or -1 to exit): ");
        scanf("%d", &value);
        if (value == -1) {
            break;
        }
        addSensorData(&head, value);
    }

    printSensorData(head);

    // Free allocated memory
    while (head != NULL) {
        struct SensorData* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
