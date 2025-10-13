#include <iostream>
#include <cstring>

using namespace std;

// Базовый класс Triad
class Triad {
protected:
    int first;   // первое число
    int second;  // второе число
    int third;   // третье число

public:
    // Конструкторы
    Triad() : first(0), second(0), third(0) {}
    Triad(int f, int s, int t) : first(f), second(s), third(t) {}
    virtual ~Triad() {}

    // Методы получения значений
    int get_first() const { return first; }
    int get_second() const { return second; }
    int get_third() const { return third; }

    // Методы установки значений
    void set_first(int f) { first = f; }
    void set_second(int s) { second = s; }
    void set_third(int t) { third = t; }

    // Методы увеличения на 1
    virtual void inc_first() { first++; }
    virtual void inc_second() { second++; }
    virtual void inc_third() { third++; }

    // Метод преобразования в строку
    virtual char* toString() {
        char* buffer = new char[100];
        // Заменяем sprintf на ручное форматирование
        char temp[20];
        int pos = 0;
        
        buffer[pos++] = '(';
        
        // Первое число
        int num = first;
        int len = 0;
        char num_str[20];
        if (num == 0) {
            num_str[len++] = '0';
        } else {
            if (num < 0) {
                num_str[len++] = '-';
                num = -num;
            }
            int start = len;
            while (num > 0) {
                num_str[len++] = '0' + (num % 10);
                num /= 10;
            }
            // Разворачиваем число
            for (int i = start; i < (start + len) / 2; i++) {
                char temp_c = num_str[i];
                num_str[i] = num_str[len - 1 - i + start];
                num_str[len - 1 - i + start] = temp_c;
            }
        }
        num_str[len] = '\0';
        for (int i = 0; i < len; i++) {
            buffer[pos++] = num_str[i];
        }
        
        buffer[pos++] = ',';
        buffer[pos++] = ' ';
        
        // Второе число
        num = second;
        len = 0;
        if (num == 0) {
            num_str[len++] = '0';
        } else {
            if (num < 0) {
                num_str[len++] = '-';
                num = -num;
            }
            int start = len;
            while (num > 0) {
                num_str[len++] = '0' + (num % 10);
                num /= 10;
            }
            for (int i = start; i < (start + len) / 2; i++) {
                char temp_c = num_str[i];
                num_str[i] = num_str[len - 1 - i + start];
                num_str[len - 1 - i + start] = temp_c;
            }
        }
        num_str[len] = '\0';
        for (int i = 0; i < len; i++) {
            buffer[pos++] = num_str[i];
        }
        
        buffer[pos++] = ',';
        buffer[pos++] = ' ';
        
        // Третье число
        num = third;
        len = 0;
        if (num == 0) {
            num_str[len++] = '0';
        } else {
            if (num < 0) {
                num_str[len++] = '-';
                num = -num;
            }
            int start = len;
            while (num > 0) {
                num_str[len++] = '0' + (num % 10);
                num /= 10;
            }
            for (int i = start; i < (start + len) / 2; i++) {
                char temp_c = num_str[i];
                num_str[i] = num_str[len - 1 - i + start];
                num_str[len - 1 - i + start] = temp_c;
            }
        }
        num_str[len] = '\0';
        for (int i = 0; i < len; i++) {
            buffer[pos++] = num_str[i];
        }
        
        buffer[pos++] = ')';
        buffer[pos] = '\0';
        
        return buffer;
    }

    // Операторы ввода/вывода
    friend ostream& operator<<(ostream& out, Triad& t) {
        out << "(" << t.first << ", " << t.second << ", " << t.third << ")";
        return out;
    }

    friend istream& operator>>(istream& in, Triad& t) {
        in >> t.first >> t.second >> t.third;
        return in;
    }
};

// Производный класс Date
class Date : public Triad {
private:
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int daysInMonth(int month, int year) const {
        if (month == 2) {
            return isLeapYear(year) ? 29 : 28;
        }
        if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        }
        return 31;
    }

    void normalizeDate() {
        // Нормализация дней
        while (third > daysInMonth(second, first)) {
            third -= daysInMonth(second, first);
            second++;
            if (second > 12) {
                second = 1;
                first++;
            }
        }

        while (third < 1) {
            second--;
            if (second < 1) {
                second = 12;
                first--;
            }
            third += daysInMonth(second, first);
        }

        // Нормализация месяцев
        while (second > 12) {
            second -= 12;
            first++;
        }

        while (second < 1) {
            second += 12;
            first--;
        }
    }

public:
    // Конструкторы
    Date() : Triad(2000, 1, 1) {} // Дата по умолчанию: 01.01.2000
    Date(int year, int month, int day) : Triad(year, month, day) {
        normalizeDate();
    }

    // Методы получения даты
    int get_year() const { return first; }
    int get_month() const { return second; }
    int get_day() const { return third; }

    // Методы установки даты
    void set_year(int year) { 
        first = year; 
        normalizeDate();
    }
    void set_month(int month) { 
        second = month; 
        normalizeDate();
    }
    void set_day(int day) { 
        third = day; 
        normalizeDate();
    }

    // Переопределенные методы увеличения на 1
    void inc_first() override { // Увеличение года
        first++;
    }

    void inc_second() override { // Увеличение месяца
        second++;
        if (second > 12) {
            second = 1;
            first++;
        }
        normalizeDate();
    }

    void inc_third() override { // Увеличение дня
        third++;
        normalizeDate();
    }

    // Метод увеличения даты на n дней
    void add_days(int n) {
        third += n;
        normalizeDate();
    }

    // Переопределенный метод toString
    char* toString() override {
        char* buffer = new char[100];
        int pos = 0;
        
        // День
        int day = third;
        if (day < 10) {
            buffer[pos++] = '0';
            buffer[pos++] = '0' + day;
        } else {
            buffer[pos++] = '0' + (day / 10);
            buffer[pos++] = '0' + (day % 10);
        }
        
        buffer[pos++] = '.';
        
        // Месяц
        int month = second;
        if (month < 10) {
            buffer[pos++] = '0';
            buffer[pos++] = '0' + month;
        } else {
            buffer[pos++] = '0' + (month / 10);
            buffer[pos++] = '0' + (month % 10);
        }
        
        buffer[pos++] = '.';
        
        // Год
        int year = first;
        char year_str[10];
        int year_len = 0;
        int temp_year = year;
        
        if (temp_year == 0) {
            year_str[year_len++] = '0';
        } else {
            while (temp_year > 0) {
                year_str[year_len++] = '0' + (temp_year % 10);
                temp_year /= 10;
            }
            // Разворачиваем год
            for (int i = 0; i < year_len / 2; i++) {
                char temp_c = year_str[i];
                year_str[i] = year_str[year_len - 1 - i];
                year_str[year_len - 1 - i] = temp_c;
            }
        }
        
        for (int i = 0; i < year_len; i++) {
            buffer[pos++] = year_str[i];
        }
        
        buffer[pos] = '\0';
        return buffer;
    }

    // Переопределенные операторы ввода/вывода
    friend ostream& operator<<(ostream& out, Date& d) {
        out << d.get_day() << "." << d.get_month() << "." << d.get_year();
        return out;
    }

    friend istream& operator>>(istream& in, Date& d) {
        int day, month, year;
        in >> day >> month >> year;
        d.set_day(day);
        d.set_month(month);
        d.set_year(year);
        return in;
    }
};

// Главная функция для демонстрации
int main() {
    cout << "=== Демонстрация работы с Triad ===" << endl;
    
    // Создание объектов базового класса
    Triad t1;
    Triad t2(5, 10, 15);
    
    cout << "t1: " << t1 << endl;
    cout << "t2: " << t2 << endl;
    
    // Демонстрация методов увеличения
    t1.inc_first();
    t1.inc_second();
    t1.inc_third();
    cout << "t1 после увеличения: " << t1 << endl;
    
    cout << "\n=== Демонстрация работы с Date ===" << endl;
    
    // Создание объектов производного класса
    Date d1;
    Date d2(2023, 12, 31);
    
    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    
    // Демонстрация методов увеличения
    d1.inc_third(); // Увеличиваем день
    cout << "d1 после увеличения дня: " << d1 << endl;
    
    d2.inc_second(); // Увеличиваем месяц
    cout << "d2 после увеличения месяца: " << d2 << endl;
    
    d2.inc_first(); // Увеличиваем год
    cout << "d2 после увеличения года: " << d2 << endl;
    
    // Демонстрация метода add_days
    Date d3(2023, 2, 28);
    cout << "\nИсходная дата d3: " << d3 << endl;
    d3.add_days(5); // Добавляем 5 дней
    cout << "d3 после добавления 5 дней: " << d3 << endl;
    
    // Демонстрация принципа подстановки
    cout << "\n=== Принцип подстановки ===" << endl;
    Triad* basePtr = &d1;
    cout << "Дата через указатель на базовый класс: ";
    
    // Используем toString для демонстрации полиморфизма
    char* str = d1.toString();
    cout << str << endl;
    delete[] str;
    
    // Демонстрация работы с массивом объектов
    cout << "\n=== Работа с массивом объектов ===" << endl;
    Date dates[3] = {Date(2023, 1, 1), Date(2023, 6, 15), Date(2023, 12, 31)};
    
    for (int i = 0; i < 3; i++) {
        cout << "dates[" << i << "]: " << dates[i] << endl;
        dates[i].add_days(10);
        cout << "После добавления 10 дней: " << dates[i] << endl;
    }
    
    return 0;
}
-----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <cstring>

using namespace std;

// Базовый класс Array
class Array {
protected:
    static const int MAX_SIZE = 100;
    unsigned char* data;
    int size;

public:
    // Конструкторы
    Array() : size(0), data(nullptr) {}
    Array(int n, unsigned char init_val = 0) : size(n) {
        if (n < 0 || n > MAX_SIZE) {
            cout << "Ошибка: недопустимый размер массива!" << endl;
            size = 0;
            data = nullptr;
            return;
        }
        data = new unsigned char[n];
        for (int i = 0; i < n; i++) {
            data[i] = init_val;
        }
    }
    
    // Конструктор копирования
    Array(const Array& other) : size(other.size) {
        data = new unsigned char[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // Оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new unsigned char[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    virtual ~Array() {
        delete[] data;
    }

    // Метод доступа к размеру
    int length() const { return size; }

    // Оператор индексирования
    unsigned char& operator[](int index) {
        if (index < 0 || index >= size) {
            cout << "Ошибка: индекс вне диапазона!" << endl;
            static unsigned char dummy = 0;
            return dummy;
        }
        return data[index];
    }

    const unsigned char& operator[](int index) const {
        if (index < 0 || index >= size) {
            cout << "Ошибка: индекс вне диапазона!" << endl;
            static unsigned char dummy = 0;
            return dummy;
        }
        return data[index];
    }

    // Виртуальная функция сложения
    virtual Array* add(const Array& other) const {
        int max_size = (size > other.size) ? size : other.size;
        Array* result = new Array(max_size);
        
        for (int i = 0; i < max_size; i++) {
            unsigned char val1 = (i < size) ? data[i] : 0;
            unsigned char val2 = (i < other.size) ? other.data[i] : 0;
            (*result)[i] = val1 + val2;
        }
        
        return result;
    }

    // Оператор вывода
    friend ostream& operator<<(ostream& out, const Array& arr) {
        for (int i = arr.size - 1; i >= 0; i--) {
            out << (int)arr.data[i] << " ";
        }
        return out;
    }
};

// Класс Decimal для работы с знаковыми десятичными числами
class Decimal : public Array {
private:
    bool sign; // true для отрицательных, false для положительных

    void removeLeadingZeros() {
        while (size > 1 && data[size - 1] == 0) {
            size--;
        }
        if (size == 1 && data[0] == 0) {
            sign = false; // Ноль всегда положительный
        }
    }

public:
    // Конструкторы
    Decimal() : Array(), sign(false) {}
    Decimal(int n, bool s = false) : Array(n), sign(s) {}
    
    // Конструктор из строки
    Decimal(const char* str) {
        int len = strlen(str);
        int start = 0;
        
        // Определяем знак
        if (str[0] == '-') {
            sign = true;
            start = 1;
        } else {
            sign = false;
            if (str[0] == '+') start = 1;
        }
        
        size = len - start;
        if (size == 0) {
            size = 1;
            data = new unsigned char[1];
            data[0] = 0;
            sign = false;
            return;
        }
        
        data = new unsigned char[size];
        
        // Заполняем массив (младшие разряды в начале)
        for (int i = 0; i < size; i++) {
            char c = str[len - 1 - i];
            if (c >= '0' && c <= '9') {
                data[i] = c - '0';
            } else {
                cout << "Ошибка: недопустимый символ в числе!" << endl;
                delete[] data;
                size = 1;
                data = new unsigned char[1];
                data[0] = 0;
                sign = false;
                return;
            }
        }
        
        removeLeadingZeros();
    }

    // Переопределение виртуальной функции сложения
    Array* add(const Array& other) const override {
        const Decimal* other_dec = dynamic_cast<const Decimal*>(&other);
        if (!other_dec) {
            cout << "Ошибка: несовместимые типы для сложения!" << endl;
            return new Decimal(1); // Возвращаем ноль
        }
        
        // Простое сложение без учета знаков (для демонстрации)
        int max_size = (size > other_dec->size) ? size : other_dec->size;
        Decimal* result = new Decimal(max_size + 1, false);
        
        int carry = 0;
        for (int i = 0; i < max_size; i++) {
            int sum = carry;
            if (i < size) sum += data[i];
            if (i < other_dec->size) sum += other_dec->data[i];
            
            (*result)[i] = sum % 10;
            carry = sum / 10;
        }
        
        if (carry > 0) {
            (*result)[max_size] = carry;
            result->size = max_size + 1;
        } else {
            result->size = max_size;
        }
        
        result->removeLeadingZeros();
        return result;
    }

    // Метод преобразования в строку
    char* toString() const {
        if (size == 1 && data[0] == 0) {
            char* result = new char[2];
            result[0] = '0';
            result[1] = '\0';
            return result;
        }
        
        char* result = new char[size + 2]; // +1 для знака, +1 для '\0'
        int pos = 0;
        
        if (sign) {
            result[pos++] = '-';
        }
        
        for (int i = size - 1; i >= 0; i--) {
            result[pos++] = '0' + data[i];
        }
        result[pos] = '\0';
        
        return result;
    }

    // Оператор вывода
    friend ostream& operator<<(ostream& out, const Decimal& dec) {
        char* str = dec.toString();
        out << str;
        delete[] str;
        return out;
    }
};

// Класс Octal для работы с восьмеричными числами
class Octal : public Array {
private:
    void removeLeadingZeros() {
        while (size > 1 && data[size - 1] == 0) {
            size--;
        }
    }

public:
    // Конструкторы
    Octal() : Array() {}
    Octal(int n) : Array(n) {}
    
    // Конструктор из строки
    Octal(const char* str) {
        int len = strlen(str);
        int start = 0;
        
        size = len - start;
        if (size == 0) {
            size = 1;
            data = new unsigned char[1];
            data[0] = 0;
            return;
        }
        
        data = new unsigned char[size];
        
        // Заполняем массив (младшие разряды в начале)
        for (int i = 0; i < size; i++) {
            char c = str[len - 1 - i];
            if (c >= '0' && c <= '7') {
                data[i] = c - '0';
            } else {
                cout << "Ошибка: недопустимый символ в восьмеричном числе!" << endl;
                delete[] data;
                size = 1;
                data = new unsigned char[1];
                data[0] = 0;
                return;
            }
        }
        
        removeLeadingZeros();
    }

    // Переопределение виртуальной функции сложения
    Array* add(const Array& other) const override {
        const Octal* other_oct = dynamic_cast<const Octal*>(&other);
        if (!other_oct) {
            cout << "Ошибка: несовместимые типы для сложения!" << endl;
            return new Octal(1); // Возвращаем ноль
        }
        
        int max_size = (size > other_oct->size) ? size : other_oct->size;
        Octal* result = new Octal(max_size + 1);
        
        int carry = 0;
        for (int i = 0; i < max_size; i++) {
            int sum = carry;
            if (i < size) sum += data[i];
            if (i < other_oct->size) sum += other_oct->data[i];
            
            (*result)[i] = sum % 8;
            carry = sum / 8;
        }
        
        if (carry > 0) {
            (*result)[max_size] = carry;
            result->size = max_size + 1;
        } else {
            result->size = max_size;
        }
        
        result->removeLeadingZeros();
        return result;
    }

    // Метод преобразования в строку
    char* toString() const {
        if (size == 1 && data[0] == 0) {
            char* result = new char[2];
            result[0] = '0';
            result[1] = '\0';
            return result;
        }
        
        char* result = new char[size + 1];
        int pos = 0;
        
        for (int i = size - 1; i >= 0; i--) {
            result[pos++] = '0' + data[i];
        }
        result[pos] = '\0';
        
        return result;
    }

    // Оператор вывода
    friend ostream& operator<<(ostream& out, const Octal& oct) {
        char* str = oct.toString();
        out << str;
        delete[] str;
        return out;
    }
};

// Главная функция для демонстрации
int main() {
    cout << "=== Демонстрация работы с Decimal ===" << endl;
    
    // Создание десятичных чисел
    Decimal dec1("12345");
    Decimal dec2("6789");
    
    cout << "dec1: " << dec1 << endl;
    cout << "dec2: " << dec2 << endl;
    
    // Демонстрация сложения
    Array* sum_dec = dec1.add(dec2);
    Decimal* dec_sum = dynamic_cast<Decimal*>(sum_dec);
    if (dec_sum) {
        cout << "dec1 + dec2: " << *dec_sum << endl;
    }
    delete sum_dec;
    
    cout << "\n=== Демонстрация работы с Octal ===" << endl;
    
    // Создание восьмеричных чисел
    Octal oct1("12345");
    Octal oct2("677");
    
    cout << "oct1: " << oct1 << " (в восьмеричной)" << endl;
    cout << "oct2: " << oct2 << " (в восьмеричной)" << endl;
    
    // Демонстрация сложения
    Array* sum_oct = oct1.add(oct2);
    Octal* oct_sum = dynamic_cast<Octal*>(sum_oct);
    if (oct_sum) {
        cout << "oct1 + oct2: " << *oct_sum << " (в восьмеричной)" << endl;
    }
    delete sum_oct;
    
    cout << "\n=== Демонстрация полиморфизма ===" << endl;
    
    // Массив указателей на базовый класс
    Array* numbers[4];
    numbers[0] = new Decimal("123");
    numbers[1] = new Decimal("456");
    numbers[2] = new Octal("123");
    numbers[3] = new Octal("456");
    
    // Демонстрация виртуального вызова
    for (int i = 0; i < 4; i++) {
        cout << "numbers[" << i << "]: ";
        
        // Определяем тип и выводим соответствующим образом
        if (Decimal* dec = dynamic_cast<Decimal*>(numbers[i])) {
            cout << *dec << " (десятичное)" << endl;
        } else if (Octal* oct = dynamic_cast<Octal*>(numbers[i])) {
            cout << *oct << " (восьмеричное)" << endl;
        }
    }
    
    // Демонстрация сложения через базовый указатель
    cout << "\nСложение через базовый указатель:" << endl;
    Array* result1 = numbers[0]->add(*numbers[1]);
    Array* result2 = numbers[2]->add(*numbers[3]);
    
    if (Decimal* dec_res = dynamic_cast<Decimal*>(result1)) {
        cout << "Decimal result: " << *dec_res << endl;
    }
    if (Octal* oct_res = dynamic_cast<Octal*>(result2)) {
        cout << "Octal result: " << *oct_res << endl;
    }
    
    // Очистка памяти
    delete result1;
    delete result2;
    for (int i = 0; i < 4; i++) {
        delete numbers[i];
    }
    
    return 0;
}
