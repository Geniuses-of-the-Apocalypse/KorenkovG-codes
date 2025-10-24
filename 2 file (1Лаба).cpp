#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Money {
private:
    static const int R_COUNT = 9;  // кол-во  рублей
    static const int K_COUNT = 4;  // кол-во  копеек
    
    int r_nom[9];  // номиналы 
    int r_cnt[9];  // количество купюр
    
    double k_nom[4];  // номиналы 
    int k_cnt[4];     // количество монет
    
    double total; 
    
    void normalize(double amt);  // нормализация суммы по номиналам

public:
    Money();
    Money(double amt);
    Money(const Money& other);
    
    void init(double amt);
    void read();
    void display() const;
    string toString() const;
    
    Money add(const Money& other) const;
    Money sub(const Money& other) const;
    double div(const Money& other) const;
    Money divByNum(double num) const;
    Money mulByNum(double num) const;
    
    bool eq(const Money& other) const;
    bool neq(const Money& other) const;
    bool gt(const Money& other) const;
    bool lt(const Money& other) const;
};


Money::Money() : total(0) { // инициализация номинало

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

Money::Money(double amt) { // конструктор инициализации 
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

Money::Money(const Money& other) : total(other.total) { // конструктор копирования
    for (int i = 0; i < R_COUNT; i++) {
        r_nom[i] = other.r_nom[i];
        r_cnt[i] = other.r_cnt[i];
    }
    for (int i = 0; i < K_COUNT; i++) {
        k_nom[i] = other.k_nom[i];
        k_cnt[i] = other.k_cnt[i];
    }
}

void Money::normalize(double amt) { // нормализации суммы по номиналам
    total = amt;

    for (int i = 0; i < R_COUNT; i++) r_cnt[i] = 0; // обнуляем счетчики
    for (int i = 0; i < K_COUNT; i++) k_cnt[i] = 0;
    
    int rub = (int)amt;
    for (int i = 0; i < R_COUNT; i++) {   // распределение рублей
        r_cnt[i] = rub / r_nom[i];
        rub %= r_nom[i];
    }
    
    int kop = (int)((amt - (int)amt) * 100 + 0.5); // распределение копеек
    for (int i = 0; i < K_COUNT; i++) {
        int k_val = (int)(k_nom[i] * 100);
        k_cnt[i] = kop / k_val;
        kop %= k_val;
    }
}

void Money::init(double amt) {
    normalize(amt);
}

void Money::read() { // ввод
    double amt;
    cout << "Введите сумму: ";
    cin >> amt;
    normalize(amt);
}

void Money::display() const { // вывод
    cout << "Сумма: " << total << " руб." << endl;
    cout << "Состав:" << endl;
    cout << "Рубли: ";
    bool has_r = false;
    for (int i = 0; i < R_COUNT; i++) {
        if (r_cnt[i] > 0) {
            cout << r_nom[i] << " руб.: " << r_cnt[i] << " шт.; ";
            has_r = true;
        }
    }
    if (!has_r) cout << "нет";
    cout << endl;
    cout << "Копейки: ";
    bool has_k = false;
    for (int i = 0; i < K_COUNT; i++) {
        if (k_cnt[i] > 0) {
            cout << k_nom[i] << " коп.: " << k_cnt[i] << " шт.; ";
            has_k = true;
        }
    }
    if (!has_k) cout << "нет"; // нет вообще
    cout << endl;
}

string Money::toString() const { // преобразование суммы в строку
    string str = to_string(total);
    return str.substr(0, str.find('.') + 3) + " руб.";
}

//                                            -арифметические операции-
Money Money::add(const Money& other) const {
    Money res;
    res.normalize(this->total + other.total);
    return res;
}

Money Money::sub(const Money& other) const {
    if (this->total < other.total) {
        throw "Ошибка: отрицательная сумма!";
    }
    Money res;
    res.normalize(this->total - other.total);
    return res;
}

double Money::div(const Money& other) const {
    if (other.total == 0) {
        throw "Ошибка: деление на ноль!";
    }
    return this->total / other.total;
}

Money Money::divByNum(double num) const {
    if (num == 0) {
        throw "Ошибка: деление на ноль!";
    }
    Money res;
    res.normalize(this->total / num);
    return res;
}

Money Money::mulByNum(double num) const {
    Money res;
    res.normalize(this->total * num);
    return res;
}

//                                      -операции сравнения-

bool Money::eq(const Money& other) const {
    return fabs(this->total - other.total) < 0.001;
}

bool Money::neq(const Money& other) const {
    return !eq(other);
}

bool Money::gt(const Money& other) const {
    return this->total > other.total;
}

bool Money::lt(const Money& other) const {
    return this->total < other.total;
}

int main() {
    
    cout << "1. Тестирование конструкторов:" << endl;
    Money m1;                    // конструктор без аргументов
    Money m2(150.75);           // конструктор инициализации
    Money m3(m2);               // конструктор копирования
    
    cout << "m1 (по умолчанию):" << endl;
    m1.display();
    cout << "m2 (150.75):" << endl;
    m2.display();
    cout << "m3 (копия m2):" << endl;
    m3.display();
    
    cout << "\n2. Арифметические операции:" << endl;
    
    Money sum = m2.add(m3);
    cout << "m2 + m3 = ";
    sum.display();
    
    Money diff = m2.sub(m1);
    cout << "m2 - m1 = ";
    diff.display();
    
    double divVal = m2.div(m3);
    cout << "m2 / m3 = " << divVal << endl;
    
    Money divNum = m2.divByNum(3);
    cout << "m2 / 3 = ";
    divNum.display();
    
    Money mulNum = m2.mulByNum(2);
    cout << "m2 * 2 = ";
    mulNum.display();
    
    cout << "\n3. Операции сравнения:" << endl;
    cout << "m2 == m3: " << (m2.eq(m3) ? "да" : "нет") << endl;
    cout << "m2 != m1: " << (m2.neq(m1) ? "да" : "нет") << endl;
    cout << "m2 > m1: " << (m2.gt(m1) ? "да" : "нет") << endl;
    cout << "m2 < m3: " << (m2.lt(m3) ? "да" : "нет") << endl;
    
    cout << "\n4. Массив объектов:" << endl;
    Money arr[3] = { Money(50.25), Money(100.50), Money(200.75) };
    for (int i = 0; i < 3; i++) {
        cout << "arr[" << i << "]: " << arr[i].toString() << endl;
    }
    
    cout << "\n5. Дополнительные тесты:" << endl;
    Money test1(10.10);
    Money test2(5.05);
    Money test3 = test1.add(test2);
    cout << "10.10 + 5.05 = " << test3.toString() << endl;
    
    Money test4 = test1.sub(test2);
    cout << "10.10 - 5.05 = " << test4.toString() << endl;

    return 0;
}
