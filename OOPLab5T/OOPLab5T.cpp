#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// =================================================================
// Завдання 1.10: Ієрархія класів
// Створення класу "Точка" та похідного класу "Кольорова точка"
// =================================================================

// Базовий клас Точка
class Point {
protected:
    double x, y; // Координати точки (захищені поля для доступу з похідного класу)
public:
    // Конструктор за замовчуванням
    Point() : x(0), y(0) {
        cout << "Point default constructor called\n";
    }
    // Конструктор з параметрами
    Point(double x, double y) : x(x), y(y) {
        cout << "Point parameterized constructor called\n";
    }
    // Деструктор
    ~Point() {
        cout << "Point destructor called\n";
    }
    // Функція виведення (друку)
    void print() const {
        cout << "Coordinates: (" << x << ", " << y << ")\n";
    }
    // Функція перепризначення координат точки
    void setCoordinates(double newX, double newY) {
        x = newX;
        y = newY;
    }
};

class ColoredPoint : public Point {
private:
    string color; // Додаткове поле кольору
public:
    // Конструктор за замовчуванням (викликає базовий конструктор)
    ColoredPoint() : Point(), color("Black") {
        cout << "ColoredPoint default constructor called\n";
    }
    // Конструктор з параметрами
    ColoredPoint(double x, double y, string c) : Point(x, y), color(c) {
        cout << "ColoredPoint parameterized constructor called\n";
    }
    // Деструктор
    ~ColoredPoint() {
        cout << "ColoredPoint destructor called\n";
    }
    // Перевизначена функція виведення
    void print() const {
        cout << "Colored Point: (" << x << ", " << y << "), Color: " << color << "\n";
    }
    // Функція перепризначення кольору
    void setColor(string c) {
        color = c;
    }
};

void testTask1() {
    cout << "\n--- Task 1.10 Testing ---\n";
    double x, y;
    string color;

    // Введення даних для базового класу з клавіатури
    cout << "Enter X and Y for Point: ";
    cin >> x >> y;
    Point p(x, y);
    p.print();

    // Введення даних для похідного класу з клавіатури
    cout << "Enter X, Y and Color for ColoredPoint: ";
    cin >> x >> y >> color;
    ColoredPoint cp(x, y, color);
    cp.print();

    // Тестування функцій перепризначення
    cout << "Enter new coordinates for ColoredPoint (X Y): ";
    cin >> x >> y;
    cp.setCoordinates(x, y);

    cout << "Enter new color: ";
    cin >> color;
    cp.setColor(color);

    cp.print();
}

// =================================================================
// Завдання 2.10: Композиція та ієрархія
// Клас Процесор, Комп'ютер (містить процесор) та Комп'ютер з монітором
// =================================================================

// Клас, який буде використовуватись для композиції
class Processor {
private:
    int power; // Потужність процесора (МГц)
public:
    Processor() : power(0) {}
    Processor(int p) : power(p) {}
    int getPower() const { return power; }
    void setPower(int p) { power = p; }
};

// Базовий клас, що включає в себе інший клас (Композиція)
class Computer {
protected:
    Processor proc; // Композиція: об'єкт класу Processor як поле
    char* brand;    // Марка (вказівник на рядок, вимагає роботи з динамічною пам'яттю)
    double price;   // Ціна
public:
    // Конструктор за замовчуванням
    Computer() : proc(0), price(0.0) {
        brand = new char[1];
        brand[0] = '\0';
        cout << "Computer default constructor called\n";
    }
    // Конструктор з параметрами
    Computer(int p, const char* b, double pr) : proc(p), price(pr) {
        brand = new char[strlen(b) + 1];
        strcpy(brand, b);
        cout << "Computer parameterized constructor called\n";
    }
    // Конструктор копіювання (глибоке копіювання для вказівника)
    Computer(const Computer& other) : proc(other.proc), price(other.price) {
        brand = new char[strlen(other.brand) + 1];
        strcpy(brand, other.brand);
    }
    // Оператор присвоювання
    Computer& operator=(const Computer& other) {
        if (this != &other) {
            delete[] brand; // Звільняємо стару пам'ять
            proc = other.proc;
            price = other.price;
            brand = new char[strlen(other.brand) + 1]; // Виділяємо нову пам'ять
            strcpy(brand, other.brand);
        }
        return *this;
    }
    // Деструктор (обов'язкове звільнення динамічної пам'яті)
    ~Computer() {
        delete[] brand;
        cout << "Computer destructor called\n";
    }
    // Функція друку
    void print() const {
        cout << "Computer Brand: " << brand << ", Processor: " << proc.getPower() << " MHz, Price: $" << price << "\n";
    }
};

// Похідний клас (Ієрархія)
class ComputerWithMonitor : public Computer {
private:
    double monitorSize; // Додаткове поле: розмір монітора
public:
    // Конструктор за замовчуванням
    ComputerWithMonitor() : Computer(), monitorSize(0.0) {
        cout << "ComputerWithMonitor default constructor called\n";
    }
    // Конструктор з параметрами
    ComputerWithMonitor(int p, const char* b, double pr, double ms) : Computer(p, b, pr), monitorSize(ms) {
        cout << "ComputerWithMonitor parameterized constructor called\n";
    }
    // Деструктор
    ~ComputerWithMonitor() {
        cout << "ComputerWithMonitor destructor called\n";
    }
    // Перевизначена функція друку
    void print() const {
        cout << "Computer Brand: " << brand << ", Processor: " << proc.getPower()
            << " MHz, Price: $" << price << ", Monitor: " << monitorSize << "\"\n";
    }
};

void testTask2() {
    cout << "\n--- Task 2.10 Testing ---\n";
    int power;
    string brandInput;
    double price, monitor;

    cout << "Enter Processor power (MHz), Brand and Price for Computer: ";
    cin >> power >> brandInput >> price;
    Computer comp(power, brandInput.c_str(), price);
    comp.print();

    cout << "Enter Processor power, Brand, Price and Monitor size for ComputerWithMonitor: ";
    cin >> power >> brandInput >> price >> monitor;
    ComputerWithMonitor compMon(power, brandInput.c_str(), price, monitor);
    compMon.print();
}

// =================================================================
// Завдання 3.10: Конструктори копіювання та оператори присвоювання
// Класи Людина (Person) та Службовець (Employee)
// =================================================================

class Person {
protected:
    string name; // ПІБ або просто ім'я
public:
    Person() : name("Unknown") {}
    Person(string n) : name(n) {}

    // Конструктор копіювання базового класу
    Person(const Person& other) : name(other.name) {
        cout << "Person copy constructor called\n";
    }

    // Оператор присвоювання базового класу
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
        }
        cout << "Person assignment operator called\n";
        return *this;
    }

    // Перевизначення виведення у потік (друку)
    friend ostream& operator<<(ostream& os, const Person& p) {
        os << p.name;
        return os;
    }

    // Перевизначення введення з потоку
    friend istream& operator>>(istream& is, Person& p) {
        is >> p.name;
        return is;
    }
};

class Employee : public Person {
private:
    string position; // Посада службовця
public:
    Employee() : Person(), position("None") {}
    Employee(string n, string pos) : Person(n), position(pos) {}

    // Конструктор копіювання похідного класу (викликає відповідну функцію базового класу)
    Employee(const Employee& other) : Person(other), position(other.position) {
        cout << "Employee copy constructor called\n";
    }

    // Оператор присвоювання похідного класу
    Employee& operator=(const Employee& other) {
        if (this != &other) {
            Person::operator=(other); // Виклик оператора присвоювання базового класу
            position = other.position;
        }
        cout << "Employee assignment operator called\n";
        return *this;
    }

    // Перевизначення виведення (використовує приведення до базового типу для виводу імені)
    friend ostream& operator<<(ostream& os, const Employee& e) {
        os << "Name: " << (const Person&)e << ", Position: " << e.position;
        return os;
    }

    // Перевизначення введення
    friend istream& operator>>(istream& is, Employee& e) {
        is >> (Person&)e >> e.position;
        return is;
    }
};

void testTask3() {
    cout << "\n--- Task 3.10 Testing ---\n";

    Employee emp1;
    cout << "Enter Employee data (Name Position): ";
    cin >> emp1;

    cout << "You entered: " << emp1 << "\n";

    // Перевірка конструктора копіювання
    cout << "\nTesting copy constructor...\n";
    Employee emp2(emp1);
    cout << "Copied Employee: " << emp2 << "\n";

    Employee emp3("TestName", "TestPos");
    // Перевірка оператора присвоювання
    cout << "\nTesting assignment operator...\n";
    emp3 = emp1;
    cout << "Assigned Employee: " << emp3 << "\n";
}

int main() {
    char choice;
    do {
        // Головне меню з інтерфейсом англійською мовою
        cout << "\n====== MAIN MENU ======\n";
        cout << "1 - Test Task 1.10 (Hierarchy: Point & ColoredPoint)\n";
        cout << "2 - Test Task 2.10 (Composition & Hierarchy: Computer)\n";
        cout << "3 - Test Task 3.10 (Copy Constructors & Assignment: Employee)\n";
        cout << "0 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Вибір завдання для тестування
        switch (choice) {
        case '1':
            testTask1();
            break;
        case '2':
            testTask2();
            break;
        case '3':
            testTask3();
            break;
        case '0':
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '0');

    return 0;
}