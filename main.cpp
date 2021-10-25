#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <cassert>

using namespace std;

#ifndef LENGTH
    #define LENGTH 100000000
#endif

#ifndef BLOCK_SIZE
    #define BLOCK_SIZE 10000
#endif

int partition(vector<int> &arr, int l, int r) {
    int pivot = arr[(l + r) / 2];
    int i = l, j = r;
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swap(arr[i], arr[j]);
        i++, j--;
    }
    return j;

}

void quick_sort(vector<int> &arr, int l, int r) {
    if (l < r) {
        int m = partition(arr, l, r);

        if (m - l > BLOCK_SIZE) {
            #pragma omp task shared(arr, l, m) default(none)
            quick_sort(arr, l, m);
        } else {
            quick_sort(arr, l, m);
        }

        if (r - m > BLOCK_SIZE) {
            #pragma omp task shared(arr, m, r) default(none)
            quick_sort(arr, m + 1, r);
        } else {
            quick_sort(arr, m + 1, r);
        }

        #pragma omp taskwait
    }
}

vector<int> make_test_vector(size_t length) {
    static random_device rd;
    static default_random_engine re{rd()};
    static uniform_int_distribution<int> dist{};

    vector<int> a(length);
    for (size_t i = 0; i < length; ++i) {
        a[i] = dist(re);
    }
    return a;
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Usage: <bin> seq|par [threads_num]" << endl;
        return 1;
    }
    std::string mode = argv[1];
    int threads_num = 8;
    if (argc == 3) {
        threads_num = atoi(argv[2]);
    }
    auto a = make_test_vector(LENGTH);
    if (mode == "seq") {
        quick_sort(a, 0, LENGTH - 1);
    } else if (mode == "par") {
        #pragma omp parallel shared(a) default(none) num_threads(threads_num)
        {
            #pragma omp single
            quick_sort(a, 0, LENGTH - 1);
        }
    } else {
        cerr << "Usage: <bin> seq|par <threads_num>" << endl;
        return 1;
    }
    return 0;
}
