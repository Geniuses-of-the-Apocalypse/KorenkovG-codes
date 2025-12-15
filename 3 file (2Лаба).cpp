#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

class Array {
protected:
    static const int MAX_SIZE = 100;  // размер массива
    unsigned char* arr;               
    int count;                      

public:
    Array(int cnt = 0, unsigned char init_val = 0);
    Array(const Array& other);
    Array& operator=(const Array& other);
    virtual ~Array();

    unsigned char& operator[](int idx); // []
    const unsigned char& operator[](int idx) const;
    int getCount() const; 
    static int getMaxSize();

    virtual Array* add(const Array& other) const;
    virtual void print() const;
    
    friend ostream& operator<<(ostream& os, const Array& array); // операторы ввода-вывода
    friend istream& operator>>(istream& is, Array& array);
};

Array::Array(int cnt, unsigned char init_val) : count(cnt) {
    if (cnt < 0 || cnt > MAX_SIZE) { // проверка 
        cout << "Ошибка: Неверный размер" << endl;
        count = 0;
    }
    arr = new unsigned char[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        arr[i] = (i < count) ? init_val : 0;
    }
}

Array::Array(const Array& other) : count(other.count) {
    arr = new unsigned char[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        arr[i] = other.arr[i];
    }
}

Array& Array::operator=(const Array& other) {
    if (this != &other) { // проверка на самоприсваивание
        delete[] arr;
        count = other.count;
        arr = new unsigned char[MAX_SIZE];
        for (int i = 0; i < MAX_SIZE; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

Array::~Array() {
    delete[] arr;
}

// -----------------------оператор доступа по индексу--------------------
unsigned char& Array::operator[](int idx) {
    if (idx < 0 || idx >= count) {
        cout << "Ошибка: Индекс за границами" << endl;
        static unsigned char temp;
        return temp;
    }
    return arr[idx];
}

// ---------------------константный оператор доступа по индексу----------------------
const unsigned char& Array::operator[](int idx) const {
    if (idx < 0 || idx >= count) {
        cout << "Ошибка: Индекс за границами" << endl;
        static unsigned char temp;
        return temp;
    }
    return arr[idx];
}

int Array::getCount() const {
    return count;
}

int Array::getMaxSize() {
    return MAX_SIZE;
}

Array* Array::add(const Array& other) const { // виртуальный метод сложения
    int max_cnt = (count > other.count) ? count : other.count;
    Array* res = new Array(max_cnt);
    
    for (int i = 0; i < res->count; i++) { // поэлементное сложение
        unsigned char val1 = (i < count) ? arr[i] : 0;
        unsigned char val2 = (i < other.count) ? other.arr[i] : 0;
        (*res)[i] = val1 + val2;
    }
    return res;
}

void Array::print() const {
    cout << *this;  // Используем оператор вывода
}

// Оператор вывода для Array
ostream& operator<<(ostream& os, const Array& array) {
    os << "Массив: ";
    for (int i = array.count - 1; i >= 0; i--) {
        os << (int)array.arr[i] << " ";
    }
    os << "(размер: " << array.count << ")";
    return os;
}

// Оператор ввода для Array
istream& operator>>(istream& is, Array& array) {
    cout << "Введите количество элементов (макс. " << array.MAX_SIZE << "): ";
    is >> array.count;
    
    if (array.count < 0 || array.count > array.MAX_SIZE) {
        cout << "Ошибка: Неверный размер" << endl;
        array.count = 0;
        return is;
    }
    
    cout << "Введите " << array.count << " элементов (через пробел): ";
    for (int i = 0; i < array.count; i++) {
        int val;
        is >> val;
        array.arr[i] = (val >= 0 && val <= 255) ? val : 0;
    }
    
    return is;
}

class Decimal : public Array {
private:
    bool is_negative;  // флаг -числа

public:
    Decimal(int cnt = 0, unsigned char init_val = 0, bool negative = false);
    Decimal(const Decimal& other);
    
    void fromInt(int num);
    int toInt() const;
    bool getSign() const;
    
    Array* add(const Array& other) const override;
    void print() const override;
    
    // Операторы ввода-вывода
    friend ostream& operator<<(ostream& os, const Decimal& decimal);
    friend istream& operator>>(istream& is, Decimal& decimal);
};

Decimal::Decimal(int cnt, unsigned char init_val, bool negative) 
    : Array(cnt, init_val), is_negative(negative) {}

Decimal::Decimal(const Decimal& other) 
    : Array(other), is_negative(other.is_negative) {}

void Decimal::fromInt(int num) { // значения из целого числа
    if (num == 0) {
        count = 1;
        arr[0] = 0;
        is_negative = false;
        return;
    }

    is_negative = (num < 0); // модуль
    num = abs(num);
    
    count = 0;  // числа на цифры
    while (num > 0 && count < MAX_SIZE) {
        arr[count++] = num % 10; 
        num /= 10;
    }
}

int Decimal::toInt() const { // преобразование в целое число
    int res = 0;
    for (int i = count - 1; i >= 0; i--) {
        res = res * 10 + arr[i];
    }
    return is_negative ? -res : res;
}

bool Decimal::getSign() const { // получить знак числа
    return is_negative;
}

Array* Decimal::add(const Array& other) const { // сложение десятичных чисел
    const Decimal* dec_ptr = dynamic_cast<const Decimal*>(&other); // проверка типа
    if (!dec_ptr) {
        cout << "Ошибка: Несовместимые типы" << endl;
        return nullptr;
    }

    Decimal* res = new Decimal();
    
    int max_cnt = (count > dec_ptr->count) ? count : dec_ptr->count;   // максимальный размер
    res->count = max_cnt;
    
    int carry = 0; // сложение
    for (int i = 0; i < max_cnt; i++) {
        int sum = carry;
        if (i < count) sum += arr[i];
        if (i < dec_ptr->count) sum += dec_ptr->arr[i];
        
        res->arr[i] = sum % 10;  // текущая 
        carry = sum / 10;        // слежующая (перенос)
    }
    
    if (carry > 0 && max_cnt < MAX_SIZE) { // обработка последнего переноса
        res->arr[max_cnt] = carry;
        res->count = max_cnt + 1;
    }

    res->is_negative = (is_negative && dec_ptr->is_negative); // логика знака

    return res;
}

void Decimal::print() const {
    cout << *this;  // Используем оператор вывода
}

// Оператор вывода для Decimal
ostream& operator<<(ostream& os, const Decimal& decimal) {
    os << "Десятичное: ";
    if (decimal.is_negative) os << "-";
    for (int i = decimal.count - 1; i >= 0; i--) {
        os << (int)decimal.arr[i];
    }
    os << " (как целое: " << decimal.toInt() << ")";
    return os;
}

// Оператор ввода для Decimal
istream& operator>>(istream& is, Decimal& decimal) {
    cout << "Введите десятичное число (со знаком): ";
    string input;
    is >> input;
    
    // Очистка текущего содержимого
    decimal.count = 0;
    
    // Определение знака
    if (!input.empty() && input[0] == '-') {
        decimal.is_negative = true;
        input = input.substr(1); // Удаляем знак минус
    } else {
        decimal.is_negative = false;
        if (!input.empty() && input[0] == '+') {
            input = input.substr(1); // Удаляем знак плюс
        }
    }
    
    // Проверка, что все символы - цифры
    for (char c : input) {
        if (!isdigit(c)) {
            cout << "Ошибка: Некорректное десятичное число" << endl;
            decimal.fromInt(0);
            return is;
        }
    }
    
    // Заполнение массива цифрами (в обратном порядке)
    decimal.count = input.length();
    if (decimal.count > decimal.MAX_SIZE) {
        cout << "Ошибка: Слишком длинное число" << endl;
        decimal.fromInt(0);
        return is;
    }
    
    for (int i = 0; i < decimal.count; i++) {
        decimal.arr[decimal.count - 1 - i] = input[i] - '0';
    }
    
    // Удаляем ведущие нули
    while (decimal.count > 1 && decimal.arr[decimal.count - 1] == 0) {
        decimal.count--;
    }
    
    // Случай -0
    if (decimal.count == 1 && decimal.arr[0] == 0) {
        decimal.is_negative = false;
    }
    
    return is;
}

class Octal : public Array {
public:
    Octal(int cnt = 0, unsigned char init_val = 0);
    Octal(const Octal& other);
    
    void fromInt(int num);
    int toInt() const;

    Array* add(const Array& other) const override;
    void print() const override;
    
    // Операторы ввода-вывода
    friend ostream& operator<<(ostream& os, const Octal& octal);
    friend istream& operator>>(istream& is, Octal& octal);
};

Octal::Octal(int cnt, unsigned char init_val) : Array(cnt, init_val) {
    for (int i = 0; i < count; i++) {    // от 0-7
        if (arr[i] > 7) {
            arr[i] = 0;
        }
    }
}

Octal::Octal(const Octal& other) : Array(other) {}

void Octal::fromInt(int num) { // установка значения из целого числа
    if (num < 0) num = 0;  // беззнаковое число
    if (num == 0) {
        count = 1;
        arr[0] = 0;
        return;
    }

    count = 0;    // разбираем число на восьмеричные цифры
    while (num > 0 && count < MAX_SIZE) {
        arr[count++] = num % 8;
        num /= 8;
    }
}

int Octal::toInt() const { // преобразование в целое число
    int res = 0;
    for (int i = count - 1; i >= 0; i--) { // собираем число из восьмеричных цифр
        res = res * 8 + arr[i];
    }
    return res;
}

Array* Octal::add(const Array& other) const {
    const Octal* oct_ptr = dynamic_cast<const Octal*>(&other);
    if (!oct_ptr) {
        cout << "Ошибка: Несовместимые типы" << endl;
        return nullptr;
    }

    Octal* res = new Octal();
    
    int max_cnt = (count > oct_ptr->count) ? count : oct_ptr->count;
    res->count = max_cnt;
    
    int carry = 0; // сложение с переносом в восьмеричной системе
    for (int i = 0; i < max_cnt; i++) {
        int sum = carry;
        if (i < count) sum += arr[i];
        if (i < oct_ptr->count) sum += oct_ptr->arr[i];
        
        res->arr[i] = sum % 8;  // текущая
        carry = sum / 8;        // слудующая (перенос)
    }
    
    if (carry > 0 && max_cnt < MAX_SIZE) {
        res->arr[max_cnt] = carry;
        res->count = max_cnt + 1;
    }

    return res;
}

void Octal::print() const {
    cout << *this;  // Используем оператор вывода
}

// Оператор вывода для Octal
ostream& operator<<(ostream& os, const Octal& octal) {
    os << "Восьмеричное: ";
    for (int i = octal.count - 1; i >= 0; i--) {
        os << (int)octal.arr[i];
    }
    os << " (как целое: " << octal.toInt() << ")";
    return os;
}

// Оператор ввода для Octal
istream& operator>>(istream& is, Octal& octal) {
    cout << "Введите восьмеричное число (без префикса): ";
    string input;
    is >> input;
    
    // Очистка текущего содержимого
    octal.count = 0;
    
    // Проверка, что все символы - восьмеричные цифры
    for (char c : input) {
        if (c < '0' || c > '7') {
            cout << "Ошибка: Некорректное восьмеричное число" << endl;
            octal.fromInt(0);
            return is;
        }
    }
    
    // Заполнение массива цифрами (в обратном порядке)
    octal.count = input.length();
    if (octal.count > octal.MAX_SIZE) {
        cout << "Ошибка: Слишком длинное число" << endl;
        octal.fromInt(0);
        return is;
    }
    
    for (int i = 0; i < octal.count; i++) {
        octal.arr[octal.count - 1 - i] = input[i] - '0';
    }
    
    // Удаляем ведущие нули
    while (octal.count > 1 && octal.arr[octal.count - 1] == 0) {
        octal.count--;
    }
    
    return is;
}

void demo() {
    cout << "=== Демонстрация виртуальных методов ===" << endl;

    // Используем операторы ввода
    Decimal dec1, dec2;
    cout << "\nВведите первое десятичное число:" << endl;
    cin >> dec1;
    cout << "\nВведите второе десятичное число:" << endl;
    cin >> dec2;
    
    Octal oct1, oct2;
    cout << "\nВведите первое восьмеричное число:" << endl;
    cin >> oct1;
    cout << "\nВведите второе восьмеричное число:" << endl;
    cin >> oct2;

    Array* arrays[] = {&dec1, &dec2, &oct1, &oct2};
    
    cout << "\nИсходные числа (используем операторы вывода):" << endl;
    for (int i = 0; i < 4; i++) {
        cout << *arrays[i] << endl;
    }

    cout << "\nПрямое сложение Decimal:" << endl;
    Array* res1 = dec1.add(dec2);
    if (res1) {
        cout << *res1 << endl;
        delete res1;
    }

    cout << "\nПрямое сложение Octal:" << endl;
    Array* res2 = oct1.add(oct2);
    if (res2) {
        cout << *res2 << endl;
        delete res2;
    }

    cout << "\nПолиморфизм (через Array*):" << endl;
    Array* poly1 = arrays[0]->add(*arrays[1]);
    if (poly1) {
        cout << *poly1 << endl;
        delete poly1;
    }

    Array* poly2 = arrays[2]->add(*arrays[3]);
    if (poly2) {
        cout << *poly2 << endl;
        delete poly2;
    }

    cout << "\nОбщий интерфейс Array:" << endl;
    for (int i = 0; i < 4; i += 2) {
        Array* temp = arrays[i]->add(*arrays[i + 1]);
        if (temp) {
            cout << *temp << endl;
            delete temp;
        }
    }
    
}
int main() {
    demo();
    return 0;
}
