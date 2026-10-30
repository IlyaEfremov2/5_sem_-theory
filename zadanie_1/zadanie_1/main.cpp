#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <clocale>
#include <algorithm>

using namespace std;

void selectionSort(vector<int>& arr, long long& comp, long long& assign) {
    const size_t n = arr.size();

    for (size_t i = 0; i + 1 < n; ++i) {
        size_t minIndex = i;

        for (size_t j = i + 1; j < n; ++j) {
            ++comp;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            assign += 3;
        }
    }
}

void insertionSort(vector<int>& arr, long long& comp, long long& assign) {
    const size_t n = arr.size();

    for (size_t i = 1; i < n; ++i) {
        const int key = arr[i];
        ++assign;

        size_t left = 0;
        size_t right = i;

        while (left < right) {
            const size_t mid = left + (right - left) / 2;
            ++comp;

            if (arr[mid] <= key) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }

        for (size_t j = i; j > left; --j) {
            arr[j] = arr[j - 1];
            ++assign;
        }

        if (left < i) 
        {
            arr.erase(arr.begin() + i);
            ++assign;

            arr.insert(arr.begin() + left, key);
            ++assign;
        }

void hoareSortExtraMemory(vector<int>& arr, long long& comp, long long& assign) {
    if (arr.size() <= 1) {
        return;
    }

    const int pivot = arr[arr.size() / 2];
    ++assign;

    vector<int> left;
    vector<int> right;
    vector<int> equals;
    left.reserve(arr.size());
    right.reserve(arr.size());
    equals.reserve(arr.size());

    for (size_t i = 0; i < arr.size(); ++i) {
        ++comp;
        if (arr[i] < pivot) {
            left.push_back(arr[i]);
        }
        else {
            ++comp;
            if (arr[i] > pivot) {
                right.push_back(arr[i]);
            }
            else {
                equals.push_back(arr[i]);
            }
        }
        ++assign;
    }

    hoareSortExtraMemory(left, comp, assign);
    hoareSortExtraMemory(right, comp, assign);

    size_t index = 0;
    for (size_t i = 0; i < left.size(); ++i) {
        arr[index++] = left[i];
        ++assign;
    }

    for (size_t i = 0; i < equals.size(); ++i) {
        arr[index++] = equals[i];
        ++assign;
    }

    for (size_t i = 0; i < right.size(); ++i) {
        arr[index++] = right[i];
        ++assign;
    }
}

vector<int> generateRandomArray(size_t size) {
    vector<int> arr(size);

    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % 201 - 100;
    }

    return arr;
}

void printStats(const char* title, const vector<int>& arr,
    long long comparisons, long long assignments) {
    cout << "\n" << title << '\n';
    cout << "Сравнений: " << comparisons << '\n';
    cout << "Присваиваний: " << assignments << '\n';
    cout << "Проверка сортировки: "
        << (is_sorted(arr.begin(), arr.end()) ? "успешна" : "ошибка") << '\n';
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(nullptr)));

    const size_t N = 10000;
    cout << "Создаём массив из " << N << " элементов...\n";

    const vector<int> originalArray = generateRandomArray(N);

    vector<int> arr1 = originalArray;
    long long comp1 = 0;
    long long assign1 = 0;
    selectionSort(arr1, comp1, assign1);
    printStats("1. Сортировка выбором", arr1, comp1, assign1);

    vector<int> arr2 = originalArray;
    long long comp2 = 0;
    long long assign2 = 0;
    insertionSort(arr2, comp2, assign2);
    printStats("2. Сортировка вставками с бинарным поиском", arr2, comp2, assign2);

    vector<int> arr3 = originalArray;
    long long comp3 = 0;
    long long assign3 = 0;
    hoareSortExtraMemory(arr3, comp3, assign3);
    printStats("3. Сортировка Хоара с дополнительной памятью", arr3, comp3, assign3);

    return 0;
}
