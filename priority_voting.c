#include <stdio.h>
#include <stdlib.h>

#define MAX_VOTERS 100

struct Voter {
    int id;
    int priority;
};

struct Queue {
    struct Voter voters[MAX_VOTERS];
    int front, rear;
};

void enqueue(struct Queue *q, int id, int priority) {
    if (q->rear == MAX_VOTERS - 1) {
        printf("Queue is full.\n");
        return;
    }
    q->rear++;
    q->voters[q->rear].id = id;
    q->voters[q->rear].priority = priority;
}

struct Voter dequeue(struct Queue *q) {
    if (q->front > q->rear) {
        struct Voter emptyVoter = {-1, -1};
        return emptyVoter;
    }
    struct Voter voter = q->voters[q->front];
    q->front++;
    return voter;
}

int main() {
    struct Queue votingQueue;
    votingQueue.front = 0;
    votingQueue.rear = -1;

    int totalVoters;
    printf("Enter the total number of voters: ");
    scanf("%d", &totalVoters);

    for (int i = 0; i < totalVoters; i++) {
        int id, priority;
        printf("Enter Voter %d's ID: ", i + 1);
        scanf("%d", &id);
        printf("Enter Voter %d's Priority: ", i + 1);
        scanf("%d", &priority);
        enqueue(&votingQueue, id, priority);
    }

    printf("\nVoting Order:\n");
    int count = 1;
    while (votingQueue.front <= votingQueue.rear) {
        struct Voter voter = dequeue(&votingQueue);
        if (voter.id != -1) {
            printf("Voter %d (ID: %d) voted.\n", count, voter.id);
            count++;
        }
    }

    return 0;
}
