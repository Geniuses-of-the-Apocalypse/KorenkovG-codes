#include <iostream>

using namespace std;

// Constexpr лямбда для сортировки массива
template<typename T, size_t N>
constexpr auto sortArray = [](T arr[N]) {
    // Сортировка пузырьком
    for (size_t i = 0; i < N - 1; i++)
        for (size_t j = 0; j < N - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
};

int main() {
    setlocale(LC_ALL, "RUS");
    
    // Тестируем сортировку
    int arr[] = {5, 2, 8, 1, 9};
    
    cout << "Исходный массив: ";
    for (int num : arr) cout << num << " ";
    
    sortArray<int, 5>(arr);
    
    cout << "\nОтсортированный: ";
    for (int num : arr) cout << num << " ";
    
    return 0;
}
