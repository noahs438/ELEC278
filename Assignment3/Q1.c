// Assignment 3, Q1 - Serhan, Noah
// Write DateSort() function that sorts an array of dates using quicksort method
// and main() function that reads an array of dates and outputs the sorted array of
// dates.

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int low, int high){
    int pivot = arr[high]; // Setting the pivot to the last element
    int i = (low-1); // Index of smaller element
    for (int n = low; n <= high-1; n++){
        if (arr[n] <= pivot){ // If current element is smaller than or equal to pivot
            i++; //Increment the smaller element's index
            swap(&arr[i], &arr[n]); // Swap the smaller element with the current element
        }
    }
    swap(&arr[i+1], &arr[high]); // Swap the pivot with the smaller element
    return (i+1); // Return the index of the pivot (for the next partition)
}

// Quicksort function
void quicksort(int *arr, int low, int high){
    if (low < high){
        int pivot = partition(arr, low, high); // Partition the array
        quicksort(arr, low, pivot-1); // Sort the elements before the pivot
        quicksort(arr, pivot+1, high); // Sort the elements after the pivot
    }
}

void DateSort(int arr[][3], int size) {
    // Creating a 1D array for the years
    int *years = (int *)malloc(size * sizeof(int));
    // Adding all the years to the array
    for (int i = 0; i < size; i++) {
        years[i] = arr[i][2];
    }

    // Use quicksort to sort the years
    quicksort(years, 0, size-1); // Sorting the years

    // Creating a new array for the output
    int output[size][3];

    // Adding the dates to the output array
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // If the year in the input array is equal to the year in the sorted array, add it and its other values to the output array
            if (years[i] == arr[j][2]) {
                output[i][0] = arr[j][0];
                output[i][1] = arr[j][1];
                output[i][2] = arr[j][2];

                // Then "remove" the date from the input array
                arr[j][0] = 0;
                arr[j][1] = 0;
                arr[j][2] = 0;

                break;
            }
        }
    }

    // Checking if the output array is sorted for the months and the days (could not figure out how to quicksort (not using qsort function from stdlib.h) with the full 2D array)
    for (int n = 0; n < size; n++) {
        // If the years are the same then there's a possibility that the months are not sorted
        if (output[n][2] == output[n+1][2]){
            // If the months are the same then there's a possibility that the days are not sorted
            if (output[n][1] == output[n+1][1]){
                // If the day following the current index's one is smaller, swap them
                if (output[n][0] > output[n+1][0]){
                    // Cannot use swap since we are not using pointers
                    int temp0 = output[n][0];
                    int temp1 = output[n][1];
                    int temp2 = output[n][2];

                    output[n][0] = output[n+1][0];
                    output[n][1] = output[n+1][1];
                    output[n][2] = output[n+1][2];

                    output[n+1][0] = temp0;
                    output[n+1][1] = temp1;
                    output[n+1][2] = temp2;
                }
            }
            // If the month following the current index's one is smaller, swap them
            else if (output[n][1] > output[n+1][1]){
                // Cannot use swap since we are not using pointers
                int temp0 = output[n][0];
                int temp1 = output[n][1];
                int temp2 = output[n][2];

                output[n][0] = output[n+1][0];
                output[n][1] = output[n+1][1];
                output[n][2] = output[n+1][2];

                output[n+1][0] = temp0;
                output[n+1][1] = temp1;
                output[n+1][2] = temp2;
            }
        }
    }

    // Printing the output array
    for (int i = 0; i < size; i++) {
        printf("%0.2d %0.2d %d \n", output[i][0], output[i][1], output[i][2]);
    }
}

int main(){
    int dates[][3] ={{20, 1, 2014}, {25, 3, 2010}, {3, 12, 1676}, {18, 11, 1982}, {19, 4, 2015}, {9, 7, 2015}, {12, 8, 2010}, {30, 8, 2010}, {21, 1, 2014}, {20, 7, 2014}, {18, 11, 2020}};
    int size = sizeof(dates)/sizeof(dates[0]);
    printf("The sorted dates are: \n");
    DateSort(dates, size);
}
