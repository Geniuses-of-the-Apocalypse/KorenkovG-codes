#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Triplet {
private:
    T elements[3];

public:
    Triplet();
    Triplet(const T& first, const T& second, const T& third);
    Triplet(const Triplet& other);

    void rotate(); // метод сдвига путём отзеркаливание значений
    
    string toString() const;
    
    friend ostream& operator<<(ostream& os, const Triplet& triplet) {    // вывод в поток
        os << triplet.toString();
        return os;
    }
    
    friend istream& operator>>(istream& is, Triplet& triplet) { // чтение из потока
        for (int i = 0; i < 3; i++) {
            is >> triplet.elements[i];
        }
        return is;
    }
    
    // Очистка содержимого
    void clear();
     
    T getFirst() const;
    T getSecond() const;
    T getThird() const;
    
    void setFirst(const T& value);
    void setSecond(const T& value);
    void setThird(const T& value);
};

template <typename T> // конструктор
Triplet<T>::Triplet() {
    elements[0] = T();
    elements[1] = T();
    elements[2] = T();
}

template <typename T>
Triplet<T>::Triplet(const T& first, const T& second, const T& third) {
    elements[0] = first;
    elements[1] = second;
    elements[2] = third;
}

template <typename T>
Triplet<T>::Triplet(const Triplet& other) {
    for (int i = 0; i < 3; i++) {
        elements[i] = other.elements[i];
    }
}

template <typename T> // отзеркаливание значений
void Triplet<T>::rotate() {
    T temp = elements[0];
    elements[0] = elements[2];
    elements[2] = temp;
}

template <typename T> // возврат в строку
string Triplet<T>::toString() const {
    return "(" + to_string(elements[0]) + ", " + 
                  to_string(elements[1]) + ", " + 
                  to_string(elements[2]) + ")";
}

template <> // специализация для строк
string Triplet<string>::toString() const {
    return "(" + elements[0] + ", " + elements[1] + ", " + elements[2] + ")";
}

// Очистка содержимого
template <typename T>
void Triplet<T>::clear() {
    for (int i = 0; i < 3; i++) {
        elements[i] = T();
    }
}

//-------------------------------получение элементов------------------------------------
template <typename T>
T Triplet<T>::getFirst() const {
    return elements[0];}

template <typename T>
T Triplet<T>::getSecond() const {
    return elements[1];}

template <typename T>
T Triplet<T>::getThird() const {
    return elements[2];}

//----------------------------------установка элементов-----------------------------------------
template <typename T>
void Triplet<T>::setFirst(const T& value) {
    elements[0] = value;}

template <typename T>
void Triplet<T>::setSecond(const T& value) {
    elements[1] = value;}

template <typename T>
void Triplet<T>::setThird(const T& value) {
    elements[2] = value;}

int main() {
    Triplet<int> intTriplet(1, 2, 3);
    cout << "Исходный triplet: " << intTriplet << endl;
    intTriplet.rotate();
    cout << "После rotate(): " << intTriplet << endl;
    
    Triplet<string> stringTriplet("Hi", "how", "you");
    cout << "\nСтроковый triplet: " << stringTriplet << endl;
    stringTriplet.rotate();
    cout << "После rotate(): " << stringTriplet << endl;
    
    Triplet<string> words("Hello", "world", "!");
    cout << "\nДругой пример: " << words << endl;
    words.rotate();
    cout << "После rotate(): " << words << endl;
  
    Triplet<int> anotherIntTriplet(10, 20, 30);
    cout << "\nAnother int triplet: " << anotherIntTriplet << endl;
    anotherIntTriplet.rotate();
    cout << "После rotate(): " << anotherIntTriplet << endl;
    
    Triplet<string> inputTriplet;
    cout << "\nВведите три слова через пробел: ";
    cin >> inputTriplet;
    cout << "Введенный triplet: " << inputTriplet << endl;
    
    inputTriplet.rotate();
    cout << "После rotate(): " << inputTriplet << endl;
    return 0;
}
