#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int *arr, size_t arr_len);
void print_array(const int *const arr, size_t arr_len);

int main(int argc, char *argv[]) {
    int array[] = {3, 7, 2, 5, 4, 2, 1};
    int arr_len = sizeof(array) / sizeof(array[0]);

    printf("Before sorting:\n");
    print_array(array, arr_len);

    bubble_sort(array, arr_len);

    printf("After sorting:\n");
    print_array(array, arr_len);
    return 0;
}

void bubble_sort(int *arr, size_t arr_len) {
    bool sorted = false;
    int unsorted_length = arr_len;
    while(!sorted){
        sorted = true;
        for (int i = 0; i < unsorted_length - 1; ++i) {
            if(arr[i] > arr[i+1]){
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                sorted = false;
            }
        }
    }
}

void print_array(const int *const arr, size_t arr_len) {
    for (int i = 0; i < arr_len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
