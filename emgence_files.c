#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct Patient {
    char name[MAX_NAME_LENGTH];
    int priority;
    struct Patient* next;
} Patient;

Patient* createPatient(const char* name, int priority) {
    Patient* patient = (Patient*)malloc(sizeof(Patient));
    strncpy(patient->name, name, MAX_NAME_LENGTH);
    patient->priority = priority;
    patient->next = NULL;
    return patient;
}

void enqueue(Patient** head, const char* name, int priority) {
    Patient* newPatient = createPatient(name, priority);

    if (*head == NULL || priority < (*head)->priority) {
        newPatient->next = *head;
        *head = newPatient;
    } else {
        Patient* current = *head;
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }
        newPatient->next = current->next;
        current->next = newPatient;
    }

    FILE* file = fopen("enqueue.txt", "a");
    if (file != NULL) {
        fprintf(file, "Name: %s\n", newPatient->name);
        fprintf(file, "Priority: %d\n\n", newPatient->priority);
        fclose(file);
    }
}

void dequeue(Patient** head) {
    if (*head == NULL) {
        printf("No patients in the queue.\n");
        return;
    }

    Patient* temp = *head;
    *head = (*head)->next;

    FILE* file = fopen("dequeue.txt", "a");
    if (file != NULL) {
        fprintf(file, "Name: %s\n", temp->name);
        fprintf(file, "Priority: %d\n\n", temp->priority);
        fclose(file);
    }

    free(temp);
    printf("Patient dequeued.\n");
}

void displayQueue(Patient* head) {
    if (head == NULL) {
        printf("No patients in the queue.\n");
        return;
    }

    Patient* current = head;
    printf("Patient Queue:\n");
    while (current != NULL) {
        printf("Name: %s\n", current->name);
        printf("Priority: %d\n\n", current->priority);
        current = current->next;
    }
}

void clearQueue(Patient** head) {
    Patient* current = *head;
    Patient* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
    printf("Queue cleared.\n");
}

int main() {
    Patient* head = NULL;
    int option = 0;

    while (option != 4) {
        printf("Emergency Room Menu:\n");
        printf("1. Add Patient\n");
        printf("2. Dequeue Patient\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                char name[MAX_NAME_LENGTH];
                int priority;

                printf("Enter patient name: ");
                scanf("%s", name);
                printf("Enter priority (1-10, with 10 being the highest): ");
                scanf("%d", &priority);

                enqueue(&head, name, priority);
                break;
            }
            case 2:
                dequeue(&head);
                break;
            case 3:
                displayQueue(head);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }

    clearQueue(&head);

    return 0;
}
