#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define MAX_SIZE 100

struct Stack
{
    int elements[MAX_SIZE];
    int top;
};

void initialize(struct Stack* s)
{
    s->top=-1;
}

int isFull(struct Stack* s)
{
    return s->top ==MAX_SIZE-1;
}

int isEmpty(struct Stack* s)
{
    return s->top==-1;
}

void push(struct Stack* s, int num)
{
    if (isFull(s))
    {
        printf("Stack is full. Cannot push element.\n");
        return;
    }
    s->elements[++s->top] = num;

    FILE* p1 = fopen("Push.txt", "a"); // ptr to push
    if (p1 == NULL)
    {
        printf("Unable to open Push.txt for writing.\n");
        return;
    }
    fprintf(p1,"%d\n",num);
    FILE* l1=fopen("Log.txt", "a");
    fprintf(l1,"Push");

    fclose(p1);
}

int pop(struct Stack* s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty. Cannot pop element.\n");
        return -1;
    }
    int num = s->elements[s->top--];

    FILE* p2 =fopen("Pop.txt", "a"); // ptr to pop file
    if (p2==NULL)
    {
        printf("Unable to open Pop.txt for writing.\n");
        return num;
    }
    fprintf(p2, "%d\n", num);
    fclose(p2);

    return num;
}

int main()
{
    FILE *fp,*fp1,*fp2;
    int n,p,q;
    int arr[100];
    printf("Enter the number of elements to generate");
    scanf("%d",&n);

    printf("Enter the range (P Q) to generate numbers in");
    scanf("%d %d",&p,&q);

    fp=fopen("Input.txt", "w");
    fp1=fopen("Push.txt","w");
    fp2=fopen("Pop.txt","w");
    fclose(fp1);
    fclose(fp2);


    srand(time(0)); // seed for random number generator

    for (int i=0;i<n;i++)
    {
        int num = rand() % (q-p+1)+p; // generate random number in range p, q
        fprintf(fp,"%d",num); // write number to file
    }

    fclose(fp);


    FILE* i1=fopen("Input.txt", "r+");
    if (i1==NULL)
    {
        printf("Unable to open Input.txt for reading.\n");
        return 1;
    }

    struct Stack stack;
    initialize(&stack);

    int num,a;
    while(a!=3)
    {
    printf("enter\n 1 for push\n 2 for pop\n 3 for exit\n");
    scanf("%d\n",&a);
    while(fscanf(i1,"%d",&num)!= EOF && a==1)
    {
        push(&stack, num);
    }

    fclose(i1);

    FILE* s1=fopen("Stack.txt", "w");
    if (s1==NULL)
    {
        printf("Unable to open Stack.txt for writing.\n");
        return 1;
    }

    while (!isEmpty(&stack)&& a==2)
    {
        num = pop(&stack);
        fprintf(s1,"%d\n",num);
    }

    fclose(s1);
    }
    printf("Numbers have been written to Stack.txt, Push.txt, and Pop.txt.\n");

    return 0;
}
