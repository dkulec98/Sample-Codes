/*
    Written by Damian Kulec
    02/15/20
    
    This program shows the implementation of (3) sorting algorithms: Insertion Sort, Quick Sort, & Heap Sort.
    Arrays containing 1000 elements need to be properly sorted in ascending order, and verified for correctness.
    The number of moves and comparisons required to sort each algorithm was analyzed.
    Each algorithm was tested under three unique scenarios: best case (already ordered), worst case (ordered in reverse), and average case (purely random)
    Results are then displayed at the end of program.
*/

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <chrono>

using namespace std;

//declaring global variables for counting moves and comparisons
int moves = 0, comps = 0;

// Function duplicates another array
// Used to create a 3 test arrays for each case, so that each algorithm can be run on the same exact set of data
void copy_array(int *array1, int *array2, int size) {
    for(int x = 0; x < size; x++)
        array2[x] = array1[x];
}

// Function displays the elements in the array
void display(int *array, int size) {
    for(int i = 0; i<size; i++)
        cout << array[i] << " ";
    cout << endl;
}

/* Function swaps two array elements
    Since a temporary place holder variable is needed, each swap function constitutes 3 moves to the overall count
    In some cases, a and b will be equal while swap() is called, but elements won't actually move places
 */
void swap(int &a, int &b) {
    // If statement makes sure # of moves doesn't increase if swap() is called with a = b
    if(a == b)
        moves += 0;
    else {
        int temp;
        temp = a;
        a = b;
        b = temp;
        moves += 3;
    }
}

// Function sets the global variables to 0
void reset_vars() {
    moves = 0;
    comps = 0;
}

// Function verifies whether array is sorted correctly or not
bool check_array(int *array, int size) {
    bool check = false;
    for(int x = 0; x < size - 1; x++) {
        if(array[x] > array[x+1])
           return check;
    }
    check = true;
    return check;
}

//Insertion Sort Algorithm
void insertionSort(int *array, int size) {
    int next;
    for(int x = 1; x < size; x++) {
        comps++;
        next = array[x];
        int loc = x;
        while((loc > 0) && (array[loc-1] > next)) {
            comps++;
            moves++;
            array[loc] = array[loc-1];
            loc--;
        }
        if(loc != x)
            array[loc] = next;
    }
}



int partition(int array[], int low, int high) {
    // Select the pivot element
    int pivot = array[high];
    int i = (low - 1);

    // Put the elements smaller than pivot on the left
    // and greater than pivot on the right of pivot
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
        comps++;
    }
    swap(array[i + 1], array[high]);
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {
      // Select pivot position and put all the elements smaller
      // than pivot on left and greater than pivot on right
      int part = partition(array, low, high);

      // Sort the elements on the left of pivot
      quickSort(array, low, part - 1);

      // Sort the elements on the right of pivot
      quickSort(array, part + 1, high);
    }
}


// Heapify Algorithm
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
  
    // Check is left child is largest
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
        comps++;
    }
    // Check's if right child is largest
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
        comps++;
    }
  
    // Checks if largest is not root
    if (largest != i) {
        comps++;
        swap(arr[i], arr[largest]);
        // Recursively call heapify
        heapify(arr, n, largest);
    }
}
  
// Heap Sort Algorithm
void heapSort(int arr[], int n) {
    // For loop builds heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
  
    // Extract elements from newly constructed heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
  
        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}


int main() {
    // Makes random variable definitions different each time program is run
    srand(time(NULL));
    int size = 1000;
    int BST[size], WST[size], AVG[size];
    for(int r = 0; r < size; r++) {
        BST[r] = (r + 1) * 10;
        WST[r] = (size - r) * 10;
        AVG[r] = rand() & 10000;
    }
    int tAVG[size], tBST[size], tWST[size];

    /************** INSERTION SORT ANALYSIS*************/
    
    // Worst, Avg, and Best case arrays copied into temporary arrays for analysis
     copy_array(WST, tWST, size);
     copy_array(AVG, tAVG, size);
     copy_array(BST, tBST, size);
     reset_vars();
     
     cout << "========= Insertion Sort =========" << endl;
     cout << "BEST CASE" << endl;
     insertionSort(tBST, size);
     cout << "Moves: " << moves << endl << "Comparisons: " << comps << endl;
     outfile << moves << "    " << comps << endl;
     if(check_array(tBST,size))
         cout << "Array is ordered correctly \n" << endl;
     else
         cout << "Array not ordered \n" << endl;
    
    reset_vars();

     cout << "AVERAGE CASE" << endl;
     insertionSort(tAVG, size);
     cout << "Moves: " << moves << endl << "Comparisons: " << comps << endl;
     outfile << moves << "    " << comps << endl;
     if(check_array(tAVG,size))
         cout << "Array is ordered correctly \n" << endl;
     else
         cout << "Array not ordered \n" << endl;
    
    reset_vars();

     cout << "WORST CASE" << endl;
     insertionSort(tWST, size);
     cout << "Moves: " << moves << endl << "Comparisons: " << comps << endl;
     outfile << moves << "    " << comps << endl;
     if(check_array(tWST,size))
         cout << "Array is ordered correctly \n" << endl;
     else
         cout << "Array not ordered \n" << endl;
     
    /************** HEAP SORT ANALYSIS *************/
    copy_array(WST, tWST, size);
    copy_array(AVG, tAVG, size);
    copy_array(BST, tBST, size);
    reset_vars();
    cout << "========= Heap Sort =========" << endl;
    cout << "BEST CASE" << endl;
    heapSort(tBST, size);
    cout << "Moves: " << moves << endl << "Comparisons: " << comps << endl;
    outfile << moves << "    " << comps << endl;
    if(check_array(tBST,size))
        cout << "Array is ordered correctly \n" << endl;
    else
        cout << "Array not ordered \n" << endl;
   
    reset_vars();

    cout << "Average CASE" << endl;
    heapSort(tAVG, size);
    cout << "Moves: " << moves << endl << "Comparisons: " << comps << endl;
    outfile << moves << "    " << comps << endl;
    if(check_array(tAVG,size))
        cout << "Array is ordered correctly \n" << endl;
    else
        cout << "Array not ordered \n" << endl;
   
    reset_vars();
    
    cout << "BEST CASE" << endl;
    heapSort(tWST, size);
    cout << "Moves: " << moves << endl << "Comparisons: " << comps << endl;
    outfile << moves << "    " << comps << endl;
    if(check_array(tWST,size))
        cout << "Array is ordered correctly \n" << endl;
    else
        cout << "Array not ordered \n" << endl;
   
    reset_vars();
   
    /************* Quick Sort ***********/
    
     copy_array(WST, tWST, size);
     copy_array(AVG, tAVG, size);
     copy_array(BST, tBST, size);
     reset_vars();
     
     cout << "========= Quick Sort =========" << endl;
     cout << "BEST CASE" << endl;
     quickSort(tBST, 0, size - 1);
     cout << "Moves: " << moves << endl << "Comparisons: " << comps << endl;
     outfile << moves << "    " << comps << endl;
     if(check_array(tBST,size))
         cout << "Array is ordered correctly \n" << endl;
     else
         cout << "Array not ordered \n" << endl;
    
    reset_vars();

     cout << "AVERAGE CASE" << endl;
     quickSort(tAVG, 0, size - 1);
     cout << "Moves: " << moves << endl << "Comparisons: " << comps << endl;
     outfile << moves << "    " << comps << endl;
     if(check_array(tAVG,size))
         cout << "Array is ordered correctly \n" << endl;
     else
         cout << "Array not ordered \n" << endl;
    
    reset_vars();

     cout << "WORST CASE" << endl;
     quickSort(tWST, 0, size - 1);
     cout << "Moves: " << moves << endl << "Comparisons: " << comps << endl;
     outfile << moves << "    " << comps << endl;
     if(check_array(tWST,size))
         cout << "Array is ordered correctly \n" << endl;
     else
         cout << "Array not ordered \n" << endl;
}
