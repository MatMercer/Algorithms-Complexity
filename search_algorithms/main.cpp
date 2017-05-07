#include <iostream>
#include <zconf.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int linearSearch(int *array, int size, int searchInt) {
    for (int i = 0; i < size; i++) {
        if (array[i] == searchInt) {
            return i;
        }
    }

    return -1;
}

int sentinelSearch(int *array, int size, int searchInt) {
    if (array[size - 1] == searchInt) {
        return size - 1;
    } else {
        int last = array[size - 1];

        array[size - 1] = searchInt;

        int i = 0;
        while (array[i] != searchInt) {
            i += 1;
        }

        array[size - 1] = last;

        if (i < size - 1) {
            return i;
        } else {
            return -1;
        }
    }
}

int binarySearch(int *array, int start, int end, int searchInt) {
    int count = end - start;
    int m = end - (count / 2);

    if (count == 1) {
        return array[m] == searchInt ? m : -1;
    } else if (searchInt == array[m]) {
        return m;
    } else if (searchInt > array[m]) {
        return binarySearch(array, m, end, searchInt);
    } else {
        return binarySearch(array, start, m, searchInt);
    }
}

void printArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i];
        if (i + 1 != size) {
            cout << " ";
        }
    }
    cout << "\n";
}


int invalidUsage() {
    cerr << "Usage:" << endl;
    cerr << "search_alg <algorithm id> <size > 0> <number to search>." << endl;
    cerr << "Number to search can be -1 to be random between 0 and 10000." << endl;
    cerr << endl << "Available algorithms:" << endl;
    cerr << "1: sequential" << endl;
    cerr << "2: sentinel" << endl;
    cerr << "3: binary" << endl;

    return 1;
}

void sortArray(int *array, int size) {
    for (int i = 1; i < size; i++) {
        int idx = array[i];
        int j = i;

        while (j > 0 && array[j - 1] > idx) {
            array[j] = array[j - 1];
            j -= 1;
        }
        array[j] = idx;
    }
}

int *createSortedArray(int size) {
    int *array = new int[size];

    /* populate the array and sort it */
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10001;
    }
    sortArray(array, size);

    return array;
}

string algoIdToStr(int id) {
    switch (id) {
        case 1:
            return "Sequential";
        case 2:
            return "Sentinel";
        case 3:
            return "Binary";
        default:
            return "Unknown";
    }
}

int searchForElement(int *array, int size, int searchInt, int algoId) {
    int foundIdx = -1;

    /* run the desired algorithm */
    switch (algoId) {
        case 1:
            foundIdx = linearSearch(array, size, searchInt);
            break;
        case 2:
            foundIdx = sentinelSearch(array, size, searchInt);
        case 3:
            foundIdx = binarySearch(array, 0, size - 1, searchInt);
        default:
            break;
    }

    return foundIdx;
}

int main(int argc, char **argv) {
    int elFound = -1;

    /* random seed, XOR different sources */
    srand(static_cast<unsigned int>(getpid()) ^
          static_cast<unsigned int>(pthread_self()) ^
          static_cast<unsigned int >(time(NULL)));

    if (argc < 4) {
        return invalidUsage();
    }

    /* get the arguments */
    int algoId = atoi(argv[1]);
    int size = atoi(argv[2]);
    int searchInt = atoi(argv[3]);

    if (searchInt == -1) {
        searchInt = rand() % 10001;
    }

    if (algoId > 3 || algoId < 1 || size < 1) {
        return invalidUsage();
    }

    int *array = createSortedArray(size);

    /* time measurement */
    auto t1 = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
    /* searches for the element */
    elFound = searchForElement(array, size, searchInt, algoId);
    /* time measurement */
    auto t2 = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();

    //printArray(array, size);

    /*
     * csv program output
     * algorithm name:search int:queue size:if it was found:time in nano seconds
     */
    cout << algoIdToStr(algoId) << ":" << searchInt << ":" << size << ":" << elFound << ":" << t2 - t1 << endl;

    return 0;
}


