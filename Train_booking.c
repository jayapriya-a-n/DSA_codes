#include <stdio.h>
#include <stdlib.h>

// Structure to represent a seat
typedef struct Seat {
    int seatNumber;
    int booked;
    struct Seat* next;
} Seat;

// Function to book a seat
void bookSeat(Seat** head, int seatNumber) {
    Seat* current = *head;

    while (current != NULL) {
        if (current->seatNumber == seatNumber) {
            if (current->booked) {
                printf("Seat %d is already booked.\n", seatNumber);
                return;
            } else {
                current->booked = 1;
                printf("Seat %d booked successfully.\n", seatNumber);
                return;
            }
        }
        current = current->next;
    }

    printf("Invalid seat number.\n");
}

// Function to cancel a booking
void cancelBooking(Seat** head, int seatNumber) {
    Seat* current = *head;

    while (current != NULL) {
        if (current->seatNumber == seatNumber) {
            if (current->booked) {
                current->booked = 0;
                printf("Booking for seat %d canceled successfully.\n", seatNumber);
                return;
            } else {
                printf("Seat %d is not booked.\n", seatNumber);
                return;
            }
        }
        current = current->next;
    }

    printf("Invalid seat number.\n");
}

// Function to display the status of all seats
void displayStatus(Seat* head) {
    FILE* fp = fopen("status.txt", "w");
    if (fp == NULL) {
        printf("Unable to open status.txt file.\n");
        return;
    }

    Seat* current = head;

    fprintf(fp, "Seat Status:\n");
    while (current != NULL) {
        fprintf(fp, "Seat %d: %s\n", current->seatNumber, current->booked ? "Booked" : "Available");
        current = current->next;
    }

    fclose(fp);
    printf("Seat status written to status.txt file.\n");
}

int main() {
    // Create a linked list of seats
    Seat* head = NULL;
    Seat* current = NULL;

    int numSeats;
    printf("Enter the number of seats: ");
    scanf("%d", &numSeats);

    for (int i = 1; i <= numSeats; i++) {
        Seat* newSeat = (Seat*)malloc(sizeof(Seat));
        newSeat->seatNumber = i;
        newSeat->booked = 0;
        newSeat->next = NULL;

        if (head == NULL) {
            head = newSeat;
            current = newSeat;
        } else {
            current->next = newSeat;
            current = newSeat;
        }
    }

    // Menu-driven loop for booking, canceling, and displaying status
    int choice, seatNumber;
    FILE* fp;

    do {
        printf("\nTrain Booking System\n");
        printf("1. Book a seat\n");
        printf("2. Cancel booking\n");
        printf("3. Display seat status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter seat number to book: ");
                scanf("%d", &seatNumber);
                bookSeat(&head, seatNumber);
                fp = fopen("booking.txt", "a");
                if (fp == NULL) {
                    printf("Unable to open booking.txt file.\n");
                    return 0;
                }
                fprintf(fp, "Seat %d booked.\n", seatNumber);
                fclose(fp);
                break;

            case 2:
                printf("Enter seat number to cancel booking: ");
                scanf("%d", &seatNumber);
                cancelBooking(&head, seatNumber);
                fp = fopen("cancel.txt", "a");
                if (fp == NULL) {
                    printf("Unable to open cancel.txt file.\n");
                    return 0;
                }
                fprintf(fp, "Booking for seat %d canceled.\n", seatNumber);
                fclose(fp);
                break;

            case 3:
                displayStatus(head);
                break;

            case 4:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);

    // Free memory
    current = head;
    while (current != NULL) {
        Seat* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
