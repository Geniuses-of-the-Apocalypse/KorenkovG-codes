#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Money {
private:
    static const int R_COUNT = 9;  // кол-во рублей
    static const int K_COUNT = 4;  // кол-во копеек
    
    int r_nom[9]; // номинал
    int r_cnt[9];  // количество купюр 
    
    double k_nom[4]; // номинал
    int k_cnt[4];     // количество монет 
    
    double total;
    
    void normalize(double amt);  // нормализация суммы по номиналам

public:
    Money();
    Money(double amt);
    Money(const Money& other);
    
    Money operator+(const Money& other) const;  // сложение
    Money operator-(const Money& other) const;  // вычитание
    double operator/(const Money& other) const; // деление сумм
    Money operator/(double num) const;          // деление на число
    Money operator*(double num) const;          // умножение на число
    
    bool operator==(const Money& other) const;  // равенство
    bool operator!=(const Money& other) const;  // неравенство
    bool operator>(const Money& other) const;   // больше
    bool operator<(const Money& other) const;   // меньше

    string toString() const;
    
    // Операторы ввода-вывода
    friend ostream& operator<<(ostream& os, const Money& money);
    friend istream& operator>>(istream& is, Money& money);
};

Money::Money() : total(0) {
    int temp_r_nom[9] = {5000, 1000, 500, 100, 50, 10, 5, 2, 1};
    double temp_k_nom[4] = {0.5, 0.1, 0.05, 0.01};
    for (int i = 0; i < R_COUNT; i++) {
        r_nom[i] = temp_r_nom[i];
        r_cnt[i] = 0;
    }
    for (int i = 0; i < K_COUNT; i++) {
        k_nom[i] = temp_k_nom[i];
        k_cnt[i] = 0;
    }
}

Money::Money(double amt) {
    int temp_r_nom[9] = {5000, 1000, 500, 100, 50, 10, 5, 2, 1};
    double temp_k_nom[4] = {0.5, 0.1, 0.05, 0.01};
    for (int i = 0; i < R_COUNT; i++) {
        r_nom[i] = temp_r_nom[i];
    }
    for (int i = 0; i < K_COUNT; i++) {
        k_nom[i] = temp_k_nom[i];
    }
    normalize(amt);
}

// Конструктор копирования
Money::Money(const Money& other) : total(other.total) {
    for (int i = 0; i < R_COUNT; i++) {
        r_nom[i] = other.r_nom[i];
        r_cnt[i] = other.r_cnt[i];
    }
    for (int i = 0; i < K_COUNT; i++) {
        k_nom[i] = other.k_nom[i];
        k_cnt[i] = other.k_cnt[i];
    }
}

void Money::normalize(double amt) { // нормализация суммы по номиналам
    total = amt;
    for (int i = 0; i < R_COUNT; i++) r_cnt[i] = 0;
    for (int i = 0; i < K_COUNT; i++) k_cnt[i] = 0;
    int rub = (int)amt;
    for (int i = 0; i < R_COUNT; i++) {
        r_cnt[i] = rub / r_nom[i];
        rub %= r_nom[i];
    }
    int kop = (int)((amt - (int)amt) * 100 + 0.5);
    for (int i = 0; i < K_COUNT; i++) {
        int k_val = (int)(k_nom[i] * 100);
        k_cnt[i] = kop / k_val;
        kop %= k_val;
    }
}

string Money::toString() const {
    string str = to_string(total);
    return str.substr(0, str.find('.') + 3) + " руб.";
}

//                                              -перегрузка арифметических операторов-

Money Money::operator+(const Money& other) const {
    Money res;
    res.normalize(this->total + other.total);
    return res;
}

Money Money::operator-(const Money& other) const {
    if (this->total < other.total) {
        throw "Ошибка: отрицательная сумма!";
    }
    Money res;
    res.normalize(this->total - other.total);
    return res;
}

double Money::operator/(const Money& other) const {
    if (other.total == 0) {
        throw "Ошибка: деление на ноль!";
    }
    return this->total / other.total;
}

Money Money::operator/(double num) const {
    if (num == 0) {
        throw "Ошибка: деление на ноль!";
    }
    Money res;
    res.normalize(this->total / num);
    return res;
}

Money Money::operator*(double num) const {
    Money res;
    res.normalize(this->total * num);
    return res;
}

//                                               -перегрузка операторов сравнения-

bool Money::operator==(const Money& other) const {
    return fabs(this->total - other.total) < 0.001;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator>(const Money& other) const {
    return this->total > other.total;
}

bool Money::operator<(const Money& other) const {
    return this->total < other.total;
}

// Оператор вывода
ostream& operator<<(ostream& os, const Money& money) {
    os << money.toString();
    return os;
}

// Оператор ввода
istream& operator>>(istream& is, Money& money) {
    double amt;
    cout << "Введите сумму: ";
    is >> amt;
    money.normalize(amt);
    return is;
}

int main() {
    
    cout << "1. Тестирование конструкторов:" << endl;
    Money m1;           // конструктор без аргументов
    Money m2(150.75);   // конструктор инициализации
    Money m3(m2);       // конструктор копирования
    
    cout << "m1: " << m1 << endl;
    cout << "m2: " << m2 << endl;
    cout << "m3: " << m3 << endl;
    
    cout << "\n2. Арифметические операции с перегрузкой:" << endl;
    
    Money sum = m2 + m3;
    cout << "m2 + m3 = " << sum << endl;
    
    Money diff = m2 - m1;
    cout << "m2 - m1 = " << diff << endl;
    
    double divVal = m2 / m3;
    cout << "m2 / m3 = " << divVal << endl;
    
    Money divNum = m2 / 3;
    cout << "m2 / 3 = " << divNum << endl;
    
    Money mulNum = m2 * 2;
    cout << "m2 * 2 = " << mulNum << endl;
    
    cout << "\n3. Операции сравнения с перегрузкой:" << endl;
    cout << "m2 == m3: " << (m2 == m3 ? "да" : "нет") << endl;
    cout << "m2 != m1: " << (m2 != m1 ? "да" : "нет") << endl;
    cout << "m2 > m1: " << (m2 > m1 ? "да" : "нет") << endl;
    cout << "m2 < m3: " << (m2 < m3 ? "да" : "нет") << endl;
    
    cout << "\n4. Массив объектов:" << endl;
    Money arr[3] = { Money(50.25), Money(100.50), Money(200.75) };
    for (int i = 0; i < 3; i++) {
        cout << "arr[" << i << "]: " << arr[i] << endl;
    }
    
    cout << "\n5. Сложные выражения:" << endl;
    Money test1(10.10);
    Money test2(5.05);
    Money test3 = test1 + test2;
    cout << "10.10 + 5.05 = " << test3 << endl;
    
    Money test4 = test1 - test2;
    cout << "10.10 - 5.05 = " << test4 << endl;
    
    Money complex = (test1 + test2) * 2 - Money(5.00); // комбинированные операции показывающие плюсы перегрузки
    cout << "(10.10 + 5.05) * 2 - 5.00 = " << complex << endl;
    
    cout << "\n6. Тестирование оператора ввода:" << endl; // пример использования оператора ввода
    Money inputMoney;
    cin >> inputMoney;
    cout << "Вы ввели: " << inputMoney << endl;

    return 0;
}
