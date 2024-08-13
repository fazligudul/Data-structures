#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

// Function prototypes
int* generate_random_array(int size);
int* generate_almost_sorted_array(int size);
void selection_sort(int arr[], int size, double& duration);
void insertion_sort(int arr[], int size, double& duration);
void bubble_sort(int arr[], int size, double& duration);
void quick_sort(int arr[], int low, int high, double& duration); // Quick Sort function
void print_array(int arr[], int size);

// Constants
const int COMPARISON_TIME = 1; // Time to compare a pair of trees (in seconds)
const int SWAP_TIME = 15;      // Time for a swap (three position changes) (in seconds)

int main() {
    // Define the range of truck capacities (powers of 2)
    const int MIN_TRUCK_CAPACITY = pow(2, 3);   // 2^3 = 8
    const int MAX_TRUCK_CAPACITY = pow(2, 12);  // 2^12 = 4096

    // Loop through each truck size
    for (int truck_capacity = MIN_TRUCK_CAPACITY; truck_capacity <= MAX_TRUCK_CAPACITY; truck_capacity *= 2) {
        cout << "Truck Capacity: " << truck_capacity << endl;

        // Generate random tree heights for the truck
        int* truck_trees = generate_random_array(truck_capacity);

        // Print the original array
        cout << "Before Sorting:" << endl;
        print_array(truck_trees, truck_capacity);

        // Sort the trees using Selection Sort and estimate the duration
        cout << "Selection Sort:" << endl;
        double selection_duration = 0;
        selection_sort(truck_trees, truck_capacity, selection_duration);
        cout << "Total Duration of Labor Work (Selection Sort): " << selection_duration << " seconds" << endl;
        cout << "Sorted Array:" << endl;
        print_array(truck_trees, truck_capacity);

        // Generate almost sorted array for the truck
        int* almost_sorted_truck_trees = generate_almost_sorted_array(truck_capacity);

        // Reset the array
        delete[] truck_trees;

        // Sort the almost sorted trees using Insertion Sort and estimate the duration
        cout << "Insertion Sort (Almost Sorted):" << endl;
        double insertion_duration = 0;
        insertion_sort(almost_sorted_truck_trees, truck_capacity, insertion_duration);
        cout << "Total Duration of Labor Work (Insertion Sort): " << insertion_duration << " seconds" << endl;
        cout << "Sorted Array:" << endl;
        print_array(almost_sorted_truck_trees, truck_capacity);

        // Reset the array
        delete[] almost_sorted_truck_trees;

        // Generate random tree heights for the truck
        truck_trees = generate_random_array(truck_capacity);

        // Sort the trees using Bubble Sort and estimate the duration
        cout << "Bubble Sort:" << endl;
        double bubble_duration = 0;
        bubble_sort(truck_trees, truck_capacity, bubble_duration);
        cout << "Total Duration of Labor Work (Bubble Sort): " << bubble_duration << " seconds" << endl;
        cout << "Sorted Array:" << endl;
        print_array(truck_trees, truck_capacity);

        // Reset the array
        delete[] truck_trees;

        // Generate random tree heights for the truck
        truck_trees = generate_random_array(truck_capacity);

        // Sort the trees using Quick Sort and estimate the duration
        cout << "Quick Sort:" << endl;
        double quick_duration = 0;
        quick_sort(truck_trees, 0, truck_capacity - 1, quick_duration);
        cout << "Total Duration of Labor Work (Quick Sort): " << quick_duration << " seconds" << endl;
        cout << "Sorted Array:" << endl;
        print_array(truck_trees, truck_capacity);

        // Free memory allocated for the array
        delete[] truck_trees;

        cout << endl;
    }

    return 0;
}

// Function to generate a random array of tree heights
int* generate_random_array(int size) {
    int* arr = new int[size];
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; // Adjust range according to requirements
    }
    return arr;
}

// Function to generate an almost sorted array of tree heights
int* generate_almost_sorted_array(int size) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int* random_array = generate_random_array(size);

    // Sorting the random array
    sort(random_array, random_array + size);

    int swap_count = size * 0.03;
    for (int i = 0; i < swap_count; ++i) {
        int first_index = rand() % size;
        int second_index = rand() % size;
        int temp = random_array[first_index];
        random_array[first_index] = random_array[second_index];
        random_array[second_index] = temp;
    }

    return random_array;
}

// Function to perform Selection Sort and estimate the duration
void selection_sort(int arr[], int size, double& duration) {
    int comparisons = 0;
    int swaps = 0;

    for (int last = size - 1; last >= 1; --last) {
        int largest = 0;
        for (int i = 1; i <= last; i++) {
            // Simulate comparison
            comparisons++;
            if (arr[i] > arr[largest]) {
                largest = i;
            }
        }
        // Simulate swap
        swaps++;
        std::swap(arr[largest], arr[last]);
    }

    // Calculate total duration
    duration = comparisons * COMPARISON_TIME + swaps * SWAP_TIME;
}

// Function to perform Insertion Sort and estimate the duration
void insertion_sort(int arr[], int size, double& duration) {
    int comparisons = 0;
    int shifts = 0;

    for (int j = 1; j < size; ++j) {
        int key = arr[j];
        int i = j - 1;
        while (i >= 0 && arr[i] > key) {
            comparisons++;
            arr[i + 1] = arr[i];
            i--;
            shifts++;
        }
        arr[i + 1] = key;
    }

    // Calculate total duration
    duration = comparisons * COMPARISON_TIME + shifts * SWAP_TIME;
}

// Function to perform Bubble Sort and estimate the duration
void bubble_sort(int arr[], int size, double& duration) {
    int comparisons = 0;
    int swaps = 0;
    bool sorted = false;

    for (int pass = 1; pass < size && !sorted; ++pass) {
        sorted = true;
        for (int index = 0; index < size - pass; ++index) {
            int nextIndex = index + 1;
            comparisons++;
            if (arr[index] > arr[nextIndex]) {
                swaps++;
                std::swap(arr[index], arr[nextIndex]);
                sorted = false; // Signal exchange
            }
        }
    }

    // Calculate total duration
    duration = comparisons * COMPARISON_TIME + swaps * SWAP_TIME;
}

void partition(int arr[], int low, int high, int &pivotIndex, double &duration) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
            duration++; // Comparison
        } while (arr[i] < pivot);

        do {
            j--;
            duration++; // Comparison
        } while (arr[j] > pivot);

        if (i >= j) {
            pivotIndex = j;
            return;
        }

        std::swap(arr[i], arr[j]);
        duration += SWAP_TIME; // Swapping (Three position changes)
    }
}
void quick_sort(int arr[], int low, int high, double &duration) {
    if (low < high) {
        int pivotIndex;
        partition(arr, low, high, pivotIndex, duration);
        quick_sort(arr, low, pivotIndex, duration);
        quick_sort(arr, pivotIndex + 1, high, duration);
    }
}

// Function to print array elements
void print_array(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

