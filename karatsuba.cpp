#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> addition(std::vector<int> A, std::vector<int> B){
    if (A.size() < B.size()) {
        size_t diferencia = B.size() - A.size();
        A.insert(A.begin(), diferencia, 0);
    }

    if(B.size() < A.size()){
        size_t diferencia = A.size() - B.size();
        B.insert(B.begin(), diferencia, 0);
    }

    int n = A.size();
    std::vector<int> C(n + 1, 0);
    for(int i = n-1; i >= 0; --i){
        int a = A[i] + B[i] + C[i + 1]; 
        C[i + 1] = a % 10;
        C[i] = a / 10;
    }
    if (C[0] == 0 && C.size() > 1) {
        C.erase(C.begin());
    }

    return C;
}
std::vector<int> multiplication(std::vector<int>& A, std::vector<int>& B){
    int n = A.size();
    int m = B.size();
    
    if (n == 0 || m == 0) return {0};
    
    std::vector<int> result(n + m, 0);

    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            int prod = A[i] * B[j];
            int sum = prod + result[i + j + 1];

            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}
std::vector<int> substraction(std::vector<int> A, std::vector<int> B){
    if (B.size() < A.size()){
        size_t diferencia = A.size() - B.size();
        B.insert(B.begin(), diferencia, 0);
    }
    int n = A.size();
    std::vector<int> C(n, 0);
    int borrow = 0;
    for(int i = n - 1; i >= 0; --i){
        int diff = A[i] - B[i] - borrow;
        if(diff < 0){
            C[i] = diff + 10;
            borrow = 1;
        }else{
            C[i] = diff;
            borrow = 0;
        }
    }
    while (C.size() > 1 && C[0] == 0) {
        C.erase(C.begin());
    }
    return C;
}

std::vector<int> create_10(int m){
    std::vector<int> pow10(m + 1, 0);
    pow10[0] = 1;
    return pow10;
}

std::vector<int> karatsuba(std::vector<int> A, std::vector<int> B, int initial, int end){
    int n = end - initial;
    if(n <= 1){
        std::vector<int> Z = multiplication(A, B);
        return Z;
    }
    while(A.size() < n) A.insert(A.begin(), 0);
    while(B.size() < n) B.insert(B.begin(), 0);

    int m = n / 2;

    std::vector<int> A1(A.begin() + initial, A.begin() + initial + (n - m));
    std::vector<int> A0(A.begin() + initial + (n - m), A.begin() + end);

    std::vector<int> B1(B.begin() + initial, B.begin() + initial + (n - m));
    std::vector<int> B0(B.begin() + initial + (n - m), B.begin() + end);

    std::vector<int> X = karatsuba(A1, B1, 0, A1.size());
    std::vector<int> Y = karatsuba(A0, B0, 0, A0.size());

    std::vector<int> sumA = addition(A1, A0);
    std::vector<int> sumB = addition(B1, B0);
    std::vector<int> Z = karatsuba(sumA, sumB, 0, std::max(sumA.size(), sumB.size()));

    std::vector<int> V_10_2_m = create_10(2 * m);
    std::vector<int> V_10_m = create_10(m);

    std::vector<int> C = substraction(substraction(Z, X), Y);

    std::vector<int> R = addition(addition(multiplication(X, V_10_2_m), multiplication(C, V_10_m)), Y);

    return R;
}
int main(){
    std::vector<int> A = {1,2,3,4};
    std::vector<int> B = {5,6,7,8};
    int initial = 0;
    int end = std::max(A.size(), B.size());
    std::vector<int> result = karatsuba(A, B, initial, end);
    for(int i = 0; i < result.size(); ++i){
        std::cout << result[i] << " ";
    }
    std::cout<<std::endl;

    return 0;
}
