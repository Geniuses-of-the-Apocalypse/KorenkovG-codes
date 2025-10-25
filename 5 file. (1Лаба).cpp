#include <iostream>

using namespace std;

template <typename T> // шаблон
void revers(T arr[], int size) {
    if (size <= 1) return;
    
    for (int i = 0; i < size / 2; ++i) {
        T temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50}; // примеры
    int n = 5;
    
    cout << "До реверса: ";
    for (int i = 0; i < n; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    revers(numbers, n);
    
    cout << "После реверса: "; //50 40 30 20 10
    for (int i = 0; i < n; ++i) {
        cout << numbers[i] << " ";
    }
    return 0;
}
