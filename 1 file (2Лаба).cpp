#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// ===== РЕАЛИЗАЦИЯ ЧЕРЕЗ СТРУКТУРУ И ВНЕШНИЕ ФУНКЦИИ =================================================================

struct MoneyStruct {
    static const int R_COUNT = 9;  // кол-во рублей
    static const int K_COUNT = 4;  // кол-во  копеек
    
    int r_nom[9] = {5000, 1000, 500, 100, 50, 10, 5, 2, 1};
    int r_cnt[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    double k_nom[4] = {0.5, 0.1, 0.05, 0.01};
    int k_cnt[4] = {0, 0, 0, 0};
    
    double total;
};

void init(MoneyStruct& m, double amt) {
    m.total = amt;
    
    for (int i = 0; i < MoneyStruct::R_COUNT; i++) m.r_cnt[i] = 0;   // обнуляем счетчики
    for (int i = 0; i < MoneyStruct::K_COUNT; i++) m.k_cnt[i] = 0;
    
    int rub = (int)amt; // распределяем рубли
    for (int i = 0; i < MoneyStruct::R_COUNT; i++) {
        m.r_cnt[i] = rub / m.r_nom[i];
        rub %= m.r_nom[i];
    }
    
    int kop = (int)((amt - (int)amt) * 100 + 0.5); // распределяем копейки
    for (int i = 0; i < MoneyStruct::K_COUNT; i++) {
        int k_val = (int)(m.k_nom[i] * 100);
        m.k_cnt[i] = kop / k_val;
        kop %= k_val;
    }
}

void read(MoneyStruct& m) {
    double amt;
    cout << "Введите сумму: ";
    cin >> amt;
    init(m, amt);
}

void display(const MoneyStruct& m) {
    cout << "Сумма: " << fixed << m.total << " руб." << endl;
    cout << "Состав:" << endl;
    
    cout << "Рубли: ";
    bool has_r = false;
    for (int i = 0; i < MoneyStruct::R_COUNT; i++) {
        if (m.r_cnt[i] > 0) {
            cout << m.r_nom[i] << " руб.: " << m.r_cnt[i] << " шт.; ";
            has_r = true;
        }
    }
    if (!has_r) cout << "нет";
    cout << endl;
    
    cout << "Копейки: ";
    bool has_k = false;
    for (int i = 0; i < MoneyStruct::K_COUNT; i++) {
        if (m.k_cnt[i] > 0) {
            cout << m.k_nom[i] << " коп.: " << m.k_cnt[i] << " шт.; ";
            has_k = true;
        }
    }
    if (!has_k) cout << "нет";
    cout << endl;
}

string toString(const MoneyStruct& m) { // функция преобразования суммы в строку
    return to_string(m.total).substr(0, to_string(m.total).find('.') + 3) + " руб.";
}

//                            -арифметические операции-
MoneyStruct add(const MoneyStruct& a, const MoneyStruct& b) {
    MoneyStruct res;
    init(res, a.total + b.total);
    return res;
}

MoneyStruct sub(const MoneyStruct& a, const MoneyStruct& b) {
    if (a.total < b.total) {
        throw "Ошибка: отрицательная сумма!";
    }
    MoneyStruct res;
    init(res, a.total - b.total);
    return res;
}

double div(const MoneyStruct& a, const MoneyStruct& b) {
    if (b.total == 0) {
        throw "Ошибка: деление на ноль!";
    }
    return a.total / b.total;
}

MoneyStruct divByNum(const MoneyStruct& m, double num) {
    if (num == 0) {
        throw "Ошибка: деление на ноль!";
    }
    MoneyStruct res;
    init(res, m.total / num);
    return res;
}

MoneyStruct mulByNum(const MoneyStruct& m, double num) {
    MoneyStruct res;
    init(res, m.total * num);
    return res;
}

//                                -операции сравнения-
bool eq(const MoneyStruct& a, const MoneyStruct& b) {
    return fabs(a.total - b.total) < 0.001;
}

bool neq(const MoneyStruct& a, const MoneyStruct& b) {
    return !eq(a, b);
}

bool gt(const MoneyStruct& a, const MoneyStruct& b) {
    return a.total > b.total;
}

bool lt(const MoneyStruct& a, const MoneyStruct& b) {
    return a.total < b.total;
}
// ===== РЕАЛИЗАЦИЯ ЧЕРЕЗ КЛАСС С ЗАКРЫТЫМИ ПОЛЯМИ =====================================================================================

class MoneyClass {
private:
    static const int R_COUNT = 9;
    static const int K_COUNT = 4;
    
    int r_nom[9];
    int r_cnt[9];
    
    double k_nom[4];
    int k_cnt[4];
    
    double total;
    
    void normalize(double amt);

public:
    MoneyClass();
    MoneyClass(double amt);
    MoneyClass(const MoneyClass& other);
    
    void init(double amt);
    void read();
    void display() const;
    string toString() const; 
    
    MoneyClass add(const MoneyClass& other) const;
    MoneyClass sub(const MoneyClass& other) const;
    double div(const MoneyClass& other) const;
    MoneyClass divByNum(double num) const;
    MoneyClass mulByNum(double num) const;
    
    bool eq(const MoneyClass& other) const;
    bool neq(const MoneyClass& other) const;
    bool gt(const MoneyClass& other) const;
    bool lt(const MoneyClass& other) const;
    
    double getTotal() const;
};

MoneyClass::MoneyClass() : total(0) {
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

MoneyClass::MoneyClass(double amt) {
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

MoneyClass::MoneyClass(const MoneyClass& other) : total(other.total) {
    for (int i = 0; i < R_COUNT; i++) {
        r_nom[i] = other.r_nom[i];
        r_cnt[i] = other.r_cnt[i];
    }
    for (int i = 0; i < K_COUNT; i++) {
        k_nom[i] = other.k_nom[i];
        k_cnt[i] = other.k_cnt[i];
    }
}

//                           -закрытый метод нормализации-
void MoneyClass::normalize(double amt) {
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

void MoneyClass::init(double amt) { // паблик
    normalize(amt);
}

void MoneyClass::read() {
    double amt;
    cout << "Введите сумму: ";
    cin >> amt;
    normalize(amt);
}

void MoneyClass::display() const {
    cout << "Сумма: " << fixed << total << " руб." << endl;
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
    if (!has_k) cout << "нет";
    cout << endl;
}


string MoneyClass::toString() const { // метод преобразования в строку 
    string str = to_string(total);
    return str.substr(0, str.find('.') + 3) + " руб.";
}

//                                   -арифметические операции-
MoneyClass MoneyClass::add(const MoneyClass& other) const {
    MoneyClass res;
    res.normalize(this->total + other.total);
    return res;
}

MoneyClass MoneyClass::sub(const MoneyClass& other) const {
    if (this->total < other.total) {
        throw "Ошибка: отрицательная сумма!";
    }
    MoneyClass res;
    res.normalize(this->total - other.total);
    return res;
}

double MoneyClass::div(const MoneyClass& other) const {
    if (other.total == 0) {
        throw "Ошибка: деление на ноль!";
    }
    return this->total / other.total;
}

MoneyClass MoneyClass::divByNum(double num) const {
    if (num == 0) {
        throw "Ошибка: деление на ноль!";
    }
    MoneyClass res;
    res.normalize(this->total / num);
    return res;
}

MoneyClass MoneyClass::mulByNum(double num) const {
    MoneyClass res;
    res.normalize(this->total * num);
    return res;
}

//                                -операции сравнения-
bool MoneyClass::eq(const MoneyClass& other) const {
    return fabs(this->total - other.total) < 0.001;
}

bool MoneyClass::neq(const MoneyClass& other) const {
    return !eq(other);
}

bool MoneyClass::gt(const MoneyClass& other) const {
    return this->total > other.total;
}

bool MoneyClass::lt(const MoneyClass& other) const {
    return this->total < other.total;
}
// ===== ДЕМОНСТРАЦИЯ =====

void demoStruct() {
    cout << "=== РЕАЛИЗАЦИЯ ЧЕРЕЗ СТРУКТУРУ (ВНЕШНИЕ ФУНКЦИИ) ===" << endl;
    
    MoneyStruct m1, m2, m3;
    
    init(m1, 1234.56);
    cout << "\n1. Инициализация m1 (1234.56):" << endl;
    display(m1);
    
    cout << "\n2. Ввод m2 с клавиатуры:" << endl;
    read(m2);
    display(m2);
    
    m3 = m1;
    cout << "\n3. Копирование m1 в m3:" << endl;
    display(m3);
    
    cout << "\n4. Арифметические операции:" << endl;
    
    MoneyStruct sum = add(m1, m2);
    cout << "m1 + m2 = ";
    display(sum);
    
    MoneyStruct diff = sub(m1, m2);
    cout << "m1 - m2 = ";
    display(diff);
    
    double ratio = div(m1, m2);
    cout << "m1 / m2 = " << ratio << endl;
    
    MoneyStruct divNum = divByNum(m1, 3.0);
    cout << "m1 / 3.0 = ";
    display(divNum);
    
    MoneyStruct mulNum = mulByNum(m1, 1.5);
    cout << "m1 * 1.5 = ";
    display(mulNum);
    
    cout << "\n5. Операции сравнения:" << endl;
    cout << "m1 == m3: " << (eq(m1, m3) ? "да" : "нет") << endl;
    cout << "m1 != m2: " << (neq(m1, m2) ? "да" : "нет") << endl;
    cout << "m1 > m2: " << (gt(m1, m2) ? "да" : "нет") << endl;
    cout << "m1 < m2: " << (lt(m1, m2) ? "да" : "нет") << endl;
    
    cout << "\n6. Преобразование в строку:" << endl;
    cout << "m1: " << toString(m1) << endl;
    cout << "m2: " << toString(m2) << endl;
}

void demoClass() {
    cout << "\n\n=== РЕАЛИЗАЦИЯ ЧЕРЕЗ КЛАСС (МЕТОДЫ ВНЕ КЛАССА) ===" << endl;
    
    MoneyClass m1, m2, m3;
    
    m1.init(1234.56);
    cout << "\n1. Инициализация m1 (1234.56):" << endl;
    m1.display();
    
    cout << "\n2. Ввод m2 с клавиатуры:" << endl;
    m2.read();
    m2.display();
    
    MoneyClass m4(m1);
    cout << "\n3. Конструктор копирования m1 в m4:" << endl;
    m4.display();
    
    cout << "\n4. Арифметические операции:" << endl;
    
    MoneyClass sum = m1.add(m2);
    cout << "m1 + m2 = ";
    sum.display();
    
    MoneyClass diff = m1.sub(m2);
    cout << "m1 - m2 = ";
    diff.display();
    
    double ratio = m1.div(m2);
    cout << "m1 / m2 = " << ratio << endl;
    
    MoneyClass divNum = m1.divByNum(3.0);
    cout << "m1 / 3.0 = ";
    divNum.display();
    
    MoneyClass mulNum = m1.mulByNum(1.5);
    cout << "m1 * 1.5 = ";
    mulNum.display();
    
    cout << "\n5. Операции сравнения:" << endl;
    cout << "m1 == m4: " << (m1.eq(m4) ? "да" : "нет") << endl;
    cout << "m1 != m2: " << (m1.neq(m2) ? "да" : "нет") << endl;
    cout << "m1 > m2: " << (m1.gt(m2) ? "да" : "нет") << endl;
    cout << "m1 < m2: " << (m1.lt(m2) ? "да" : "нет") << endl;
    
    cout << "\n6. Преобразование в строку:" << endl;
    cout << "m1: " << m1.toString() << endl;
    cout << "m2: " << m2.toString() << endl;
    
    cout << "\n7. Комбинированные операции:" << endl;
    MoneyClass result = m1.add(m2).mulByNum(0.5).sub(MoneyClass(100));
    cout << "(m1 + m2) * 0.5 - 100 руб. = " << result.toString() << endl;
}

int main() {
    cout.precision(2); // устанавка точности вывода для всех чисел с плавающей точкой
    cout << fixed;
    
    demoStruct();
    demoClass();
    
    cout << "\nПрограмма завершена успешно!" << endl;
    return 0;
}
