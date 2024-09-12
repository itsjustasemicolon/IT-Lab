#include <stdio.h>

void display(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        printf("After pass %d: ", i);
        display(arr, n);
    }
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
        printf("After pass %d: ", i + 1);
        display(arr, n);
    }
}

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        printf("After pass %d: ", i + 1);
        display(arr, n);
    }
}

void quickSort(int arr[], int low, int high, int n) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;

        printf("After pass: ");
        display(arr, n);

        quickSort(arr, low, pi - 1, n);
        quickSort(arr, pi + 1, high, n);
    }
}

void merge(int arr[], int l, int m, int r, int n) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    printf("After merging: ");
    display(arr, n);
}

void mergeSort(int arr[], int l, int r, int n) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, n);
        mergeSort(arr, m + 1, r, n);
        merge(arr, l, m, r, n);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
        printf("After pass: ");
        display(arr, n);
    }
}

int main() {
    int choice, n, arr[100], i;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    do {
        int arrCopy[100];
        for (i = 0; i < n; i++) arrCopy[i] = arr[i];

        printf("\nMenu:\n");
        printf("1. Insertion Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Bubble Sort\n");
        printf("4. Quick Sort\n");
        printf("5. Merge Sort\n");
        printf("6. Heap Sort\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Insertion Sort:\n");
                insertionSort(arrCopy, n);
                break;
            case 2:
                printf("Selection Sort:\n");
                selectionSort(arrCopy, n);
                break;
            case 3:
                printf("Bubble Sort:\n");
                bubbleSort(arrCopy, n);
                break;
            case 4:
                printf("Quick Sort:\n");
                quickSort(arrCopy, 0, n - 1, n);
                break;
            case 5:
                printf("Merge Sort:\n");
                mergeSort(arrCopy, 0, n - 1, n);
                break;
            case 6:
                printf("Heap Sort:\n");
                heapSort(arrCopy, n);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);

    return 0;
}
