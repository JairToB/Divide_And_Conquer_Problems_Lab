#include<iostream>
#include<vector>
#include<algorithm>

int merge(std::vector<int>& A, std::vector<int>& aux, int inicio, int medio, int fin){
    int i = inicio;
    int j = medio + 1;
    int k = inicio;
    int countInversion = 0;

    while (i <= medio && j <= fin) {
        if (A[i] <= A[j]) {
        aux[k] = A[i];
        i++;
        }else{
            aux[k] = A[j];
            j++;
            countInversion += medio - i + 1;
        }
        k++;
    }

    while (i <= medio) {
        aux[k] = A[i];
        i++;
        k++;
    }

    while (j <= fin) {
        aux[k] = A[j];
        j++;
        k++;
    }

    for (int p = inicio; p <= fin; p++) {
        A[p] = aux[p];
    }

    return countInversion;
}

int mergeSort(std::vector<int>& A, std::vector<int> aux, int inicio, int fin) {
    if (inicio >= fin) {
        return 0;
    }

    int medio = inicio + (fin - inicio) / 2;
    int countInversion = 0;

    countInversion += mergeSort(A, aux, inicio, medio);
    countInversion += mergeSort(A, aux, medio + 1, fin);
    countInversion += merge(A, aux, inicio, medio, fin);

    return countInversion;
}

int exchangeCount(std::vector<int>& A) {
  if (A.empty()) {
    return 0;
  }

  std::vector<int> aux(A.size());
  return mergeSort(A, aux, 0, A.size() - 1);
}

int main(){
    int n;
    while(std::cin >> n && n != 0){
        std::vector<int> A(n);

        for(int i = 0; i < n; ++i){
            std::cin >> A[i];
        }
        std::cout << exchangeCount(A) << '\n';
    }
    return 0;
}
