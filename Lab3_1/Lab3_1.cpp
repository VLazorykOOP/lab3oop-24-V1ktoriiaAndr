#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Parallelogram {
    double baseL;
    double height;
    double sideL;
    string color;
public:
    Parallelogram() : baseL(0), height(0), sideL(0), color("undefined") {}
    Parallelogram(double x, double y, double z, string color) {
        baseL = x; height = y; sideL = z; this->color = color;
    }
    double area(double baseL, double height) {
        return baseL * height;
    }
    void outArea(double baseL, double height) {
        cout << "|Area: " << area(baseL, height) << endl;
        cout << "-----------------------" << endl;
    }
    double perimetr(double baseL, double sideL) {
        return 2 * (baseL + sideL);
    }
    void outPerimetr(double baseL, double sideL) {
        cout << "|Perimetr: " << perimetr(baseL, sideL) << endl;
        cout << "-----------------------" << endl;
    }
    void setBaseL(double b) { b != 0 ? baseL = b : baseL = 0; }
    void setHeight(double h) { h != 0 ? height = h : height = 0; }
    void setSideL(double s) { s != 0 ? sideL = s : sideL = 0; }
    void setColor(string c) { c != "" ? color = c : color = "undefined"; }
    void getBaseL() { cout << baseL << endl; }
    void getHeight() { cout << height << endl; }
    void getSideL() { cout << sideL << endl; }
    void getColor() { cout << color << endl; }
    void Output() {
        cout << "-----Parallelogram-----" << endl;
        cout << "|Base length: " << baseL << endl;
        cout << "|Height length: " << height << endl;
        cout << "|Side length: " << sideL << endl;
        cout << "|Color: " << color << endl;
        cout << "-----------------------" << endl;
    }
};

int main() {
    srand(time(0));
    int choice = 0;
    cout << "Choose how to insert data: " << endl;
    cout << "1. By yourself" << endl;
    cout << "2. By reading a file" << endl;
    cout << "3. Randomize" << endl;
    cout << "---------------------------" << '\n';
    cin >> choice;
    double baseL; double height; double sideL; string color;
    switch (choice) {
    case 1: {
        cout << "Enter the length of base: " << endl;
        cin >> baseL;
        cout << "Enter the length of side: " << endl;
        cin >> sideL;
        cout << "Enter the height: " << endl;
        cin >> height;
        cout << "Enter the color: " << endl;
        cin >> color;
        break;
    }
    case 2: {
        ifstream inputFile("pData.txt");

        if (!inputFile) {
            cerr << "Error: could not open the file!" << endl;
            return 1;
        }

        inputFile >> baseL >> height >> sideL >> color;
        inputFile.close();
        break;
    }
    case 3: {
        baseL = rand() % 100 + 1; height = rand() % 100; sideL = rand() % 100;
        string colors[] = { "Red", "Blue", "Green", "Yellow", "Black" };
        color = colors[rand() % 5];
        break;
    }
    default: {
        cout << "Invalid choice" << endl;
        return 1;
    }
    }

    Parallelogram q(baseL, height, sideL, color);
    q.Output();
    q.outArea(baseL, height);
    q.outPerimetr(baseL, sideL);

    return 0;
}
