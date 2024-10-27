#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <sstream>
using namespace std;

// Class Stack menggunakan STL stack
class Stack {
private:
    stack<double> s;
public:
    void push(double value) {
        s.push(value);
    }

    double pop() {
        if (!s.empty()) {
            double top = s.top();
            s.pop();
            return top;
        } else {
            cout << "Stack kosong, tidak dapat melakukan pop.\n";
            return 0;
        }
    }

    bool isEmpty() {
        return s.empty();
    }

    double top() {
        return s.top();
    }
};

// Fungsi untuk mengecek apakah karakter adalah operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Fungsi untuk mengevaluasi ekspresi postfix
double evaluasiPostfix(const string &exp) {
    Stack stack;
    stringstream ss(exp);
    string token;

    cout << "Langkah-langkah evaluasi:\n";

    while (ss >> token) {
        if (isdigit(token[0])) {  // Jika token adalah angka
            double num = stod(token);
            stack.push(num);
            cout << "Push " << num << " ke stack.\n";
        } else if (isOperator(token[0])) {  // Jika token adalah operator
            double operand2 = stack.pop();
            double operand1 = stack.pop();
            double result = 0;

            switch (token[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 != 0) {
                        result = operand1 / operand2;
                    } else {
                        cout << "Error: Pembagian dengan nol.\n";
                        return 0;
                    }
                    break;
                case '^':
                    result = pow(operand1, operand2);
                    break;
            }
            cout << operand1 << " " << token[0] << " " << operand2 << " = " << result << "\n";
            stack.push(result);
        } else {
            cout << "Token tidak valid: " << token << "\n";
            return 0;
        }
    }

    return stack.pop();  // Hasil akhir ada di stack
}

int main() {
    string ekspresi;
    cout << "Masukkan ekspresi postfix (gunakan spasi sebagai pemisah): ";
    getline(cin, ekspresi);

    double hasil = evaluasiPostfix(ekspresi);
    cout << "Hasil evaluasi: " << hasil << endl;

    return 0;
}
