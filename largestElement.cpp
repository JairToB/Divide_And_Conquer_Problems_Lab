
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>

int randomizedPartition(std::vector<int>& A, int p, int r) {
    int randomIndex = p + std::rand() % (r - p + 1);

    std::swap(A[randomIndex], A[r]);

    int pivot = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (A[j] <= pivot) {
            i++;
            std::swap(A[i], A[j]);
        }
    }

    std::swap(A[i + 1], A[r]);

    return i + 1;
}

int randomizedSelect(std::vector<int>& A, int p, int r, int i) {
    if (p == r) {
        return A[p];
    }

    int q = randomizedPartition(A, p, r);
    int k = q - p + 1;

    if (i == k) {
        return A[q];
    }
    else if (i < k) {
        return randomizedSelect(A, p, q - 1, i);
    }
    else {
        return randomizedSelect(A, q + 1, r, i - k);
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int n, k;
    std::cin >> n >> k;

    std::vector<int> A(n);

    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    int rank = n - k + 1;
    std::cout << randomizedSelect(A, 0, n - 1, rank) << '\n';

    return 0;
}

