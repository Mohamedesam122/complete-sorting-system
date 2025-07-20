#include "SortingSystem.h"
#include<iostream>
#include <chrono>
#include "fstream"
#include "cstring"
using namespace std;
using namespace std::chrono;

template<class T>
SortingSystem<T>::SortingSystem(int n) {
    size = n;
    data = new T[size];
    for (int i = 0; i < n; i++) {
        cout << "Enter data " << i + 1 << ": ";
        cin >> data[i];
    }
}

template<class T>
SortingSystem<T>::~SortingSystem() {
    delete[] data;
}

template<class T>
void SortingSystem<T>::displayData() {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

template<class T>
void SortingSystem<T>::selectionSort() {
    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++) {
            if (data[j] < data[min]) {
                min = j;
            }
        }
        swap(data[i], data[min]);

        cout << "Iteration " << i + 1 << ": ";
        displayData();
    }

}
template<class T>
void SortingSystem<T>::merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T* L = new T[n1];
    T* R = new T[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = data[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = data[mid + 1 + j];
    }

    cout << "Merging: Left = [";
    for (int i = 0; i < n1; i++) {
        cout << L[i] << (i < n1 - 1 ? ", " : "");
    }
    cout << "] | Right = [";
    for (int j = 0; j < n2; j++) {
        cout << R[j] << (j < n2 - 1 ? ", " : "");
    }
    cout << "]\n";

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            i++;
        } else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;

    cout << "After Merging: ";
    displayData();
}
template<class T>
void SortingSystem<T>:: insertionSort() {
    for (int i = 1; i < size; i++) {
        T key = data[i];
        int j = i - 1;

        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;

        cout << "Iteration " << i << ": ";
        displayData();
    }
}




template<class T>
void SortingSystem<T>::mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        cout << "Dividing: Left Index = " << left << ", Mid Index = " << mid << ", Right Index = " << right << "\n";

        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);

        static int count = 1;
        cout << "Iteration " << count++ << ": ";
        displayData();
    }
}
template <class T>
void SortingSystem<T>::bubbleSort() {

    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                T temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                swapped = true;
            }
        }
        cout << "Iteration " << i + 1 << ": ";
        displayData();
        if (!swapped) break;
    }
}
template<class T>
int SortingSystem<T>::partition(int low, int high) {
    T pivot = data[low];
    int left = low + 1;
    int right = high;

    while (true) {
        while (left <= right && data[left] <= pivot)
            left++;

        while (left <= right && data[right] > pivot)
            right--;

        if (left > right)
            break;

        swap(data[left], data[right]);
    }

    swap(data[low], data[right]);


    cout << "Pivot: " << pivot << " -> [";
    for (int i = low; i < right; i++) {
        cout << data[i] << (i < right - 1 ? ", " : "");
    }
    cout << "] " << pivot << " [";
    for (int i = right + 1; i <= high; i++) {
        cout << data[i] << (i < high ? ", " : "");
    }
    cout << "]\n";

    return right;
}

template<class T>
void SortingSystem<T>::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}
template< class T>
void SortingSystem<T>::bucketSort() {
    T *arr = data;
    int n = size;

    if (n <= 0) return;
    if constexpr (is_arithmetic<T>::value) {
        const int bucketCount = 10;
        double buckets[10][100];
        int bucketSizes[10] = {0};

        cout << "Iteration 1 (Make Buckets):\n";
        for (int i = 0; i < n; i++) {
            int index = static_cast<int>(arr[i]) / 10;
            if (index >= bucketCount) index = bucketCount - 1;
            buckets[index][bucketSizes[index]++] = arr[i];
        }

        for (int i = 0; i < bucketCount; i++) {
            cout << "Bucket " << i << ": ";
            if (bucketSizes[i] > 0) {
                for (int j = 0; j < bucketSizes[i]; j++) {
                    cout << buckets[i][j] << " ";
                }
            } else {
                cout << " - ";
            }
            cout << endl;
        }

        cout << "Iteration 2 (Sort each bucket):\n";
        for (int i = 0; i < bucketCount; i++) {
            for (int j = 1; j < bucketSizes[i]; j++) {
                double key = buckets[i][j];
                int k = j - 1;
                while (k >= 0 && buckets[i][k] > key) {
                    buckets[i][k + 1] = buckets[i][k];
                    k--;
                }
                buckets[i][k + 1] = key;
            }

            if (bucketSizes[i] > 0) {
                cout << "Bucket " << i << " (sorted): ";
                for (int j = 0; j < bucketSizes[i]; j++) {
                    cout << buckets[i][j] << " ";
                }
                cout << endl;
            } else {
                cout << "Bucket " << i << " (sorted): - " << endl;
            }
        }

        cout << "Iteration 3 (Gather sorted data):\n";
        int index = 0;
        for (int i = 0; i < bucketCount; i++) {
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[index++] = buckets[i][j];
            }
        }
    } else {
        char buckets[26][100][50];
        int bucketSizes[26] = {0};

        cout << "Iteration 1 (Make Buckets):\n";
        for (int i = 0; i < n; i++) {
            char firstChar = tolower(arr[i][0]);
            if (firstChar >= 'a' && firstChar <= 'z') {
                int index = firstChar - 'a';


                char temp[50];
                strcpy_s(temp, 50, arr[i].c_str());


                strcpy_s(buckets[index][bucketSizes[index]], 50, temp);
                bucketSizes[index]++;
            }
        }

        for (int i = 0; i < 26; i++) {
            cout << "Bucket " << char(i + 'a') << ": ";
            if (bucketSizes[i] > 0) {
                for (int j = 0; j < bucketSizes[i]; j++) {
                    cout << buckets[i][j] << " ";
                }
            } else {
                cout << " - ";
            }
            cout << endl;
        }

        cout << "Iteration 2 (Sort each bucket):\n";
        for (int i = 0; i < 26; i++) {
            for (int j = 1; j < bucketSizes[i]; j++) {
                char key[50];
                strcpy_s(key, 50, buckets[i][j]);
                int k = j - 1;
                while (k >= 0 && strcmp(buckets[i][k], key) > 0) {
                    strcpy_s(buckets[i][k + 1], 50, buckets[i][k]);
                    k--;
                }
                strcpy_s(buckets[i][k + 1], 50, key);
            }

            if (bucketSizes[i] > 0) {
                cout << "Bucket " << char(i + 'a') << " (sorted): ";
                for (int j = 0; j < bucketSizes[i]; j++) {
                    cout << buckets[i][j] << " ";
                }
                cout << endl;
            } else {
                cout << "Bucket " << char(i + 'a') << " (sorted): - " << endl;
            }
        }

        cout << "Iteration 3 (Gather sorted data):\n";
        int index = 0;
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < bucketSizes[i]; j++) {
                char temp[50];
                strcpy_s(temp, 50, buckets[i][j]);

                arr[index] = temp;
                index++;
            }
        }
    }

}
template<class T>
void SortingSystem<T>::shellSort() {
    // Start with a large gap and reduce it
    for (int gap = size / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort
        for (int i = gap; i < size; i++) {
            T temp = data[i];
            int j;

            for (j = i; j >= gap && data[j - gap] > temp; j -= gap) {
                data[j] = data[j - gap];
            }
            data[j] = temp;

            // Print after each comparison
            cout << "Gap " << gap << ", Iteration " << i << ": ";
            displayData();
        }
    }
}
template<class T>
void SortingSystem<T>::merge_helper() {
    mergeSort(0,size-1);
}
template<class T>
void SortingSystem<T>::quick_helper() {
    quickSort(0,size-1);
}




template<class T>
void SortingSystem<T>::measureSortTime(void (SortingSystem<T>::*sortFunc)()) {
    auto start = high_resolution_clock::now();
    (this->*sortFunc)();
    auto stop = high_resolution_clock::now();
    double sortingTime = duration<double>(stop - start).count();
    cout << "Sorting Time: " << sortingTime << " seconds\n";
}


template<class T>
SortingSystem<T>::SortingSystem(const string& filename) {
    loadDataFromFile(filename);
}
template<class T>
void SortingSystem<T>::loadDataFromFile(const string& filename) {
    ifstream file(filename);

    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    file >> size;
    data = new T[size];

    for (int i = 0; i < size; i++) {
        file >> data[i];
    }

    file.close();
}







template<class T>
void SortingSystem<T>::showMenu() {
    int choice;
    char again;

    do {
        cout << "\nSorting Algorithms Menu:\n";
        cout << "1. Insertion Sort\n";
        cout << "2. Selection Sort\n";
        cout << "3. Bubble Sort\n";
        cout << "4. Shell Sort\n";
        cout << "5. Merge Sort\n";
        cout << "6. Quick Sort\n";
        cout << "7. Count Sort\n";
        cout << "8. Radix Sort\n";
        cout << "9. Bucket Sort\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;


        T* tempData = new T[size];
        for (int i = 0; i < size; i++) {
            tempData[i] = data[i];
        }

        switch (choice) {
            case 1:
                cout << "Sorting using insertion Sort...\n";
                cout << "Initial Data: ";
                displayData();
                measureSortTime(&SortingSystem<T>::insertionSort);
                cout << "Sorted Data: ";
                displayData();
                break;

            case 2:
                cout << "Sorting using selection Sort...\n";
                cout << "Initial Data: ";
                displayData();
                measureSortTime(&SortingSystem<T>::selectionSort);
                cout << "Sorted Data: ";
                displayData();
                break;
            case 3:
                cout << "Sorting using Bubble Sort...\n";
                cout << "Initial Data: ";
                displayData();
                measureSortTime(&SortingSystem<T>::bubbleSort);
                cout << "Sorted Data: ";
                displayData();
                break;

            case 4:
                cout << "Sorting using shell Sort...\n";
                cout << "Initial Data: ";
                displayData();
                measureSortTime(&SortingSystem<T>::shellSort);
                cout << "Sorted Data: ";
                displayData();
                break;

            case 5:
                cout << "Sorting using Merge Sort...\n";
                cout << "Initial Data: ";
                displayData();
                measureSortTime(&SortingSystem<T>::merge_helper);
                cout << "Sorted Data: ";
                displayData();
                break;
            case 6:
                cout << "Sorting using quick Sort...\n";
                cout << "Initial Data: ";
                displayData();
                measureSortTime(&SortingSystem<T>::quick_helper);
                cout << "Sorted Data: ";
                displayData();
                break;


            case 9:
                cout << "Sorting using bucket Sort...\n";
                cout << "Initial Data: ";
                displayData();
                measureSortTime(&SortingSystem<T>::bucketSort);
                cout << "Sorted Data: ";
                displayData();
                break;




            case 0:
                cout << "Exiting the program...\n";
                delete[] tempData;
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
        }


        for (int i = 0; i < size; i++) {
            data[i] = tempData[i];
        }
        delete[] tempData;

        if (choice != 0) {
            cout << "\nDo you want to try another sorting algorithm? (y/n): ";
            cin >> again;
        }
    } while (choice != 0 && (again == 'y' || again == 'Y'));

    cout << "Returning to main menu...\n";
}



int main() {
    char restart;

    do {
        cout << "\nSelect Data Type to Sort:\n";
        cout << "1. Integer\n";
        cout << "2. Float\n";
        cout << "3. String\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice < 1 || choice > 3) {
            cout << "Invalid choice! Try again.\n";
            continue;
        }

        string filename;
        cout << "Enter the filename containing data: ";
        cin >> filename;

        if (choice == 1) {
            SortingSystem<int> sort(filename);
            sort.showMenu();
        }
        else if (choice == 2) {
            SortingSystem<float> sort(filename);
            sort.showMenu();
        }
        else if (choice == 3) {
            SortingSystem<string> sort(filename);
            sort.showMenu();
        }

        cout << "\nDo you want to restart with new data? (y/n): ";
        cin >> restart;
    } while (restart == 'y' || restart == 'Y');

    cout << "Thank you for using the sorting system! Goodbye!\n";
    return 0;
}


