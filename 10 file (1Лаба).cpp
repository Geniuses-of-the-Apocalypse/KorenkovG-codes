#include <iostream>
using namespace std;

// НОД для двух чисел
template<typename T>
T gcd(T a, T b) {
    while (b != 0) {
        T temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// НОК для двух чисел
template<typename T>
T lcm_two(T a, T b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

// Рекурсивная функция НОК для любого количества аргументов
template<typename T>
T lcm(T a) {
    return a;
}

template<typename T, typename... Args>
T lcm(T first, T second, Args... args) {
    return lcm(lcm_two(first, second), args...);
}

int main() {
    // Тестирование функции
    cout << "lcm(2, 3) = " << lcm(2, 3) << endl;                    // 6
    cout << "lcm(4, 6, 8) = " << lcm(4, 6, 8) << endl;              // 24
    cout << "lcm(5, 10, 15) = " << lcm(5, 10, 15) << endl;          // 30
    
    return 0;
}
