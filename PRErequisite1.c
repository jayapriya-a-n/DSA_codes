#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y)
{
    int temp= *x;
    *x=*y;
    *y=temp;
}

void bubblesort(int arr[],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}

int main() {
    int n, p, q;
    int arr[100000];
    FILE *fp;

    printf("Enter the number of elements to generate: ");
    scanf("%d", &n);

    printf("Enter the range (P Q) to generate numbers in: ");
    scanf("%d %d", &p, &q);

    fp = fopen("Input.txt", "w");
    srand(time(0)); // seed for random number generator

    for (int i = 0; i < n; i++) {
        int num = rand() % (q - p + 1) + p; // generate random number in range [p, q]
        fprintf(fp, "%d ", num); // write number to file
    }

    fclose(fp);

    printf("Generated %d numbers in the range (%d, %d) and wrote to file Input.txt\n", n, p, q);

    FILE *fp_in, *fp_out;

    fp_in = fopen("Input.txt", "r");
    fp_out = fopen("Output.txt", "w");

    printf("Sorting has started\n");

    for (int i = 0; i < n; i++)
    {
        fscanf(fp_in, "%d", &arr[i]);
    }

    //Sort the array using bubble sort
    clock_t start, end;
    start = clock();
    bubblesort(arr, n);
    end = clock();
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++)
    {
        fprintf(fp_out, "%d ", arr[i]);
    }

    fclose(fp_in);
    fclose(fp_out);



    // Open log file for writing
    FILE *fp3;
    fp3 = fopen("log.txt", "a");

    // Write results to log file
    fprintf(fp3, "Sorting technique: Bubble sort\n");
    fprintf(fp3, "Number of elements (X): %d\n", n);
    fprintf(fp3, "Time taken: %lf seconds\n\n", time_taken);

    // Close the log file
    fclose(fp3);
    printf("Time taken: %lf seconds\n\n", time_taken);
    return 0;
}
