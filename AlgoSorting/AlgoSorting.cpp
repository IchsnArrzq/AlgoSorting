#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <ctime>

using namespace std;

int const size_max = 100;

void insertionSort(vector<int> data, int size);

void bubbleSort(vector<int> data, int size);

void shellSort(vector<int> data, int size);

void merge(vector<int> data, int p, int q, int r);

void mergeSort(vector<int> data, int l, int r);

void swap(int* a, int* b);

int partition(vector<int> data, int low, int high);

void quickSort(vector<int> data, int low, int high);

void printArray(vector<int> data, int size);

vector<int> generateRandomArray();

void timestamp(string label);

int main()
{
    string menu = "1. bubble\n2. insertion\n3. shell\npilih menu : ";
    int choose;
    vector<int> data = generateRandomArray();
    int size = size_max;

    do {
        cout << menu;
        cin >> choose;
        switch (choose) {
            case 1:
                bubbleSort(data, size);
                break;
            case 2:
                insertionSort(data, size);
                break;
            case 3:
                shellSort(data, size);
                break;

        }
    } while (true);


    return 0;
}


void timestamp(string label) {

    auto now = chrono::system_clock::now();

    time_t currentTime = chrono::system_clock::to_time_t(now);

    tm localTime;

#ifdef _WIN32
    localtime_s(&localTime, &currentTime);
#else
    localtime_r(&currentTime, &localTime);
#endif

    int hour = localTime.tm_hour;
    int minute = localTime.tm_min;
    int second = localTime.tm_sec;

    auto nowInMs = chrono::time_point_cast<chrono::milliseconds>(now);
    auto nowInNs = chrono::time_point_cast<chrono::nanoseconds>(now);

    auto milliseconds = nowInMs.time_since_epoch().count() % 1000;
    auto nanoseconds = nowInNs.time_since_epoch().count() % 1000000000;

    cout << label << " : "
        << setfill('0') << setw(2) << hour << ":"
        << setfill('0') << setw(2) << minute << ":"
        << setfill('0') << setw(2) << second << " "
        << setfill('0') << setw(3) << milliseconds << "ms "
        << setfill('0') << setw(9) << nanoseconds << "ns"
        << endl;

}

vector<int> generateRandomArray() {
    vector<int> arr; 
    srand((unsigned)time(NULL));

    for (int i = 0; i < size_max; i++) {

        int random = 100 + (rand() % 101);

        arr.push_back(random);
    }

    return arr;
}


void printArray(vector<int> data, int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << data[i] << " ";
    cout << endl;
}

void insertionSort(vector<int> data, int size) {
    for (int step = 1; step < size; step++) {
        int key = data[step];
        int j = step - 1;

        while (j >= 0 && key < data[j]) {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = key;
    }
    timestamp("selesai");
    printArray(data, size);
}

void bubbleSort(vector<int> data, int size) {
    timestamp("mulai");
    for (int step = 0; step < size - 1; ++step) {
        for (int i = 0; i < size - step - 1; ++i) {

            if (data[i] > data[i + 1]) {

                int temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
            }
        }
    }
    timestamp("selesai");
    printArray(data, size);
}

void shellSort(vector<int> data, int size) {
    for (int interval = size / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < size; i += 1) {
            int temp = data[i];
            int j;
            for (j = i; j >= interval && data[j - interval] > temp; j -= interval) {
                data[j] = data[j - interval];
            }
            data[j] = temp;
        }
    }
    timestamp("selesai");
    printArray(data, size);
}

void merge(vector<int> data, int p, int q, int r) {

    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1);
    vector<int> M(n2);

    for (int i = 0; i < n1; i++)
        L[i] = data[p + i];

    for (int j = 0; j < n2; j++)
        M[j] = data[q + 1 + j];

    int i = 0, j = 0, k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            data[k] = L[i];
            i++;
        }
        else {
            data[k] = M[j];
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
        data[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> data, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(data, l, m);
        mergeSort(data, m + 1, r);
        merge(data, l, m, r);
    }
}


void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(vector<int> data, int low, int high) {

    int pivot = data[high];

    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (data[j] <= pivot) {

            i++;
            swap(&data[i], &data[j]);
        }
    }

    swap(&data[i + 1], &data[high]);

    return (i + 1);
}

void quickSort(vector<int> data, int low, int high) {
    if (low < high) {

        int pi = partition(data, low, high);

        quickSort(data, low, pi - 1);

        quickSort(data, pi + 1, high);
    }
}