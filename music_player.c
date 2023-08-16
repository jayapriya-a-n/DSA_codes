#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song {
    char title[100];
    char artist[100];
    struct Song* prev;
    struct Song* next;
};

struct Song* createSong(const char* title, const char* artist) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->prev = NULL;
    newSong->next = NULL;
    return newSong;
}

void addSong(struct Song** playlist, const char* title, const char* artist) {
    struct Song* newSong = createSong(title, artist);

    if (*playlist == NULL) {
        *playlist = newSong;
    } else {
        struct Song* current = *playlist;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newSong;
        newSong->prev = current;
    }

    printf("Added: %s by %s\n", title, artist);
}

void playPlaylist(struct Song* playlist) {
    if (playlist == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    struct Song* current = playlist;
    printf("Now Playing:\n");
    while (current != NULL) {
        printf("%s by %s\n", current->title, current->artist);
        current = current->next;
    }
}

int main() {
    struct Song* playlist = NULL;
    int choice;
    char title[100], artist[100];

    do {
        printf("\nOnline Music Player\n");
        printf("1. Add Song\n");
        printf("2. Play Playlist\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                scanf("%s", title);
                printf("Enter artist name: ");
                scanf("%s", artist);
                addSong(&playlist, title, artist);
                break;
            case 2:
                playPlaylist(playlist);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    // Free memory before exiting
    struct Song* current = playlist;
    while (current != NULL) {
        struct Song* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
