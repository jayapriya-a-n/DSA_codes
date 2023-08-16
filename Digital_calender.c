#include <stdio.h>
#include <stdlib.h>

struct Date {
    int day, month, year;
};

struct Event {
    char description[100];
    struct Date date;
    struct Event *prev, *next;
};

struct Event *createEvent() {
    struct Event *newEvent = (struct Event *)malloc(sizeof(struct Event));
    if (newEvent == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newEvent->prev = NULL;
    newEvent->next = NULL;
    return newEvent;
}

void insertEvent(struct Event **head, struct Event *newEvent) {
    if (*head == NULL) {
        *head = newEvent;
    } else {
        struct Event *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newEvent;
        newEvent->prev = current;
    }
}

void displayCalendar(struct Event *head) {
    if (head == NULL) {
        printf("No events in the calendar.\n");
        return;
    }

    printf("Calendar:\n");
    struct Event *current = head;
    while (current != NULL) {
        printf("Date: %02d/%02d/%04d\n", current->date.day, current->date.month, current->date.year);
        printf("Event: %s\n\n", current->description);
        current = current->next;
    }
}

int main() {
    struct Event *calendar = NULL;
    int numEvents;

    printf("Enter the number of events: ");
    scanf("%d", &numEvents);

    for (int i = 0; i < numEvents; i++) {
        struct Event *newEvent = createEvent();

        printf("Enter event description: ");
        scanf(" %[^\n]s", newEvent->description);

        printf("Enter event date (dd mm yyyy): ");
        scanf("%d %d %d", &newEvent->date.day, &newEvent->date.month, &newEvent->date.year);

        insertEvent(&calendar, newEvent);
    }

    printf("\n");

    displayCalendar(calendar);

    return 0;
}
