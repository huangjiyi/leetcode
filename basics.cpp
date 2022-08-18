#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

// O(n)循环求x^n
int func1(int x, int n) {
    int res = x;
    for (int i = 0; i < n - 1; ++i) {
        res *= x;
    }
    return res;
}

// O(n)递归求x^n
int func2(int x, int n) {
    if (n == 0) return 1;
    return func2(x, n - 1) * x;
}

// O(logn)递归求x^n
int func3(int x, int n) {
    if (n == 1) return x;
    int t = func3(x, n / 2);
    if (n % 2) return t * t * x;
    return t * t;
}

// O(n^2)求斐波那契数列
int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// O(n)求斐波那契数列
int fibonacci(int first, int second, int n) {
    if (n <= 0) return 0;
    if (n < 3)
        return 1;
    else if (n == 3)
        return first + second;
    else
        return fibonacci(second, first + second, n - 1);
}

// O(n)循环求斐波那契数列
int fibonacci_2(int n) {
    if (n <= 0) return 0;
    if (n < 3) return 1;
    int first = 1, second = 1;
    for (int i = 3; i < n; ++i) {
        second = first + second;
        first = second;
    }
    return first + second;
}


int main() {
    cout << func1(2, 3) << endl;
    cout << func2(2, 3) << endl;
    cout << func3(2, 3) << endl;

    auto start = system_clock::now();
    for (int i = 0; i < 30; ++i) {
        cout << fibonacci_2(i + 1) << " ";
    }
    auto end = system_clock::now();
    auto time_elapsed = duration_cast<milliseconds>(end - start);
    cout << endl << time_elapsed.count() << "ms" << endl;

    struct node {
        char ch;
        int ah;
    } st{};

    // 内存对齐
    int a[100];
    char b[100];
    cout << sizeof(int) << endl;  //
    cout << sizeof(char) << endl;
    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
    cout << sizeof(st) << endl;
}