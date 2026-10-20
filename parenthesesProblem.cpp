#include<iostream>
#include<string>
#include<vector>

std::vector<int> parenthesesRoad(std::string expression) {
    std::vector<int> result;

    for (int i = 0; i < expression.size(); i++) {
        char op = expression[i];

        if (op == '+' || op == '-' || op == '*') {
            std::string left = expression.substr(0, i);
            std::string right = expression.substr(i + 1);

            std::vector<int> A = parenthesesRoad(left);
            std::vector<int> B = parenthesesRoad(right);

            for (int a : A) {
                for (int b : B) {
                    if (op == '+')
                        result.push_back(a + b);
                    else if (op == '-')
                        result.push_back(a - b);
                    else
                        result.push_back(a * b);
                }
            }
        }
    }

    if (result.empty()) {
        result.push_back(std::stoi(expression));
    }

    return result;
}

void insertionSort(std::vector<int>& result) {
    for (int i = 1; i < result.size(); i++) {
        int key = result[i];
        int j = i - 1;

        while (j >= 0 && result[j] > key) {
            result[j + 1] = result[j];
            j--;
        }

        result[j + 1] = key;
    }
}

int main() {
    std::string expression;
    std::cin >> expression;

    std::vector<int> result = parenthesesRoad(expression);
    insertionSort(result);

    for (int i = 0; i < result.size(); i++) {
        if (i > 0) std::cout << " ";
        std::cout << result[i];
    }

    std::cout << '\n';
    return 0;
}

