#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

enum status { ok, error };

class Vector {
    short* V;
    int count;
    status state;
    static int objectCount;
public:
    Vector();
    Vector(int c);
    Vector(int c, short b);
    Vector(const Vector& s);
    Vector& operator=(const Vector& s);
    ~Vector();

    void setElement(int index, short value);
    short getElement(int index) const;
    void print() const;
    Vector add(const Vector& a) const;
    Vector sub(const Vector& a) const;
    Vector mul(unsigned char multiplier) const;
    bool isEqual(const Vector& a) const;
    bool isGreater(const Vector& a) const;
    bool isNotEqual(const Vector& a) const;

    void inputFromKeyboard();
    void inputFromFile(const string& filename);
    void inputRandom(int size);

    static int getObjectCount();
};

int Vector::objectCount = 0;

Vector::Vector() : V(new short[1] {0}), count(1), state(ok) { objectCount++; }

Vector::Vector(int c) : count(c), state(ok) {
    if (c <= 0) {
        V = nullptr;
        count = 0;
        state = error;
    }
    else {
        V = new short[c] {};
    }
    objectCount++;
}

Vector::Vector(int c, short b) : count(c), state(ok) {
    if (c <= 0) {
        V = nullptr;
        count = 0;
        state = error;
    }
    else {
        V = new short[c];
        for (int i = 0; i < c; i++) V[i] = b;
    }
    objectCount++;
}

Vector::Vector(const Vector& s) : count(s.count), state(s.state) {
    V = new short[count];
    for (int i = 0; i < count; i++) V[i] = s.V[i];
    objectCount++;
}

Vector& Vector::operator=(const Vector& s) {
    if (this == &s) return *this;
    delete[] V;
    count = s.count;
    state = s.state;
    V = new short[count];
    for (int i = 0; i < count; i++) V[i] = s.V[i];
    return *this;
}

Vector::~Vector() {
    delete[] V;
    objectCount--;
}

void Vector::setElement(int index, short value) {
    if (index >= 0 && index < count) V[index] = value;
}

short Vector::getElement(int index) const {
    return (index >= 0 && index < count) ? V[index] : 0;
}

void Vector::print() const {
    for (int i = 0; i < count; i++) cout << V[i] << " ";
    cout << endl;
}

Vector Vector::add(const Vector& a) const {
    int minCount = min(count, a.count);
    Vector result(minCount);
    for (int i = 0; i < minCount; i++) result.V[i] = V[i] + a.V[i];
    return result;
}

Vector Vector::sub(const Vector& a) const {
    int minCount = min(count, a.count);
    Vector result(minCount);
    for (int i = 0; i < minCount; i++) result.V[i] = V[i] - a.V[i];
    return result;
}

Vector Vector::mul(unsigned char multiplier) const {
    Vector result(count);
    for (int i = 0; i < count; i++) result.V[i] = V[i] * multiplier;
    return result;
}

bool Vector::isEqual(const Vector& a) const {
    if (count != a.count) return false;
    for (int i = 0; i < count; i++) if (V[i] != a.V[i]) return false;
    return true;
}

bool Vector::isGreater(const Vector& a) const {
    for (int i = 0; i < min(count, a.count); i++) {
        if (V[i] > a.V[i]) return true;
        if (V[i] < a.V[i]) return false;
    }
    return count > a.count;
}

bool Vector::isNotEqual(const Vector& a) const {
    return !isEqual(a);
}

void Vector::inputFromKeyboard() {
    cout << "Enter vector size: ";
    cin >> count;
    delete[] V;
    V = new short[count];
    cout << "Enter " << count << " elements: ";
    for (int i = 0; i < count; i++) cin >> V[i];
}

void Vector::inputFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    file >> count;
    delete[] V;
    V = new short[count];
    for (int i = 0; i < count; i++) file >> V[i];
    file.close();
}

void Vector::inputRandom(int size) {
    count = size;
    delete[] V;
    V = new short[count];
    srand(time(0));
    for (int i = 0; i < count; i++) V[i] = rand() % 100;
}

int Vector::getObjectCount() {
    return objectCount;
}

void inputVector(Vector& v, const string& name) {
    int inputChoice;
    cout << "\nInput options for vector " << name << ":\n";
    cout << "1. Enter from keyboard\n";
    cout << "2. Read from file\n";
    cout << "3. Generate random values\n";
    cout << "Choice: ";
    cin >> inputChoice;

    switch (inputChoice) {
    case 1:
        v.inputFromKeyboard();
        break;
    case 2: {
        string filename;
        cout << "Enter filename: ";
        cin >> filename;
        v.inputFromFile(filename);
        break;
    }
    case 3: {
        int size;
        cout << "Enter vector size: ";
        cin >> size;
        v.inputRandom(size);
        break;
    }
    default:
        cout << "Invalid choice, using keyboard input\n";
        v.inputFromKeyboard();
    }
}

int main() {
    Vector v1, v2;
    int choice;

    cout << "Choose operation:\n";
    cout << "1. Add\n";
    cout << "2. Subtract\n";
    cout << "3. Multiply\n";
    cout << "4. Compare (Equal)\n";
    cout << "5. Compare (Greater)\n";
    cout << "6. Compare (Not Equal)\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1 || choice == 2 || choice == 4 || choice == 5 || choice == 6) {
        inputVector(v1, "v1");
        inputVector(v2, "v2");
    }
    else if (choice == 3) {
        inputVector(v1, "v1");
    }

    cout << "\nResult:\n";
    if (choice == 1) {
        cout << "Sum: ";
        v1.add(v2).print();
    }
    else if (choice == 2) {
        cout << "Difference: ";
        v1.sub(v2).print();
    }
    else if (choice == 3) {
        unsigned char factor;
        cout << "Enter multiplier: ";
        cin >> factor;
        cout << "Product: ";
        v1.mul(factor).print();
    }
    else if (choice == 4) {
        cout << (v1.isEqual(v2) ? "Vectors are Equal" : "Vectors are Not Equal") << endl;
    }
    else if (choice == 5) {
        cout << (v1.isGreater(v2) ? "First vector is Greater" : "Second vector is Greater or Equal") << endl;
    }
    else if (choice == 6) {
        cout << (v1.isNotEqual(v2) ? "Vectors are Not Equal" : "Vectors are Equal") << endl;
    }
    else {
        cout << "Invalid choice!" << endl;
    }

    cout << "\nNumber of Vector objects: " << Vector::getObjectCount() << endl;

    return 0;
}