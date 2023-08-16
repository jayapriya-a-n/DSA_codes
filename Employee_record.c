#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold employee information
struct Employee {
    int id;
    char name[50];
    float salary;
    struct Employee* next;
};

// Function to insert a new employee record at the end of the list
void insertEmployee(struct Employee** head, int id, char name[], float salary) {
    struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
    newEmployee->id = id;
    strcpy(newEmployee->name, name);
    newEmployee->salary = salary;
    newEmployee->next = NULL;

    if (*head == NULL) {
        *head = newEmployee;
        return;
    }

    struct Employee* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newEmployee;
}

// Function to display all employee records
void displayEmployees(struct Employee* head) {
    struct Employee* temp = head;
    while (temp != NULL) {
        printf("ID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Salary: %.2f\n\n", temp->salary);
        temp = temp->next;
    }
}

int main() {
    struct Employee* head = NULL;
    int id;
    char name[50];
    float salary;

    int numEmployees;
    printf("Enter the number of employees: ");
    scanf("%d", &numEmployees);

    for (int i = 0; i < numEmployees; i++) {
        printf("Enter details for employee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &id);
        printf("Name: ");
        scanf("%s", name);
        printf("Salary: ");
        scanf("%f", &salary);
        insertEmployee(&head, id, name, salary);
        printf("\n");
    }

    printf("Employee records:\n");
    displayEmployees(head);

    // Free allocated memory
    struct Employee* temp = head;
    while (temp != NULL) {
        struct Employee* next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}
