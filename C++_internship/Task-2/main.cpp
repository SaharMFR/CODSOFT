#include <iostream>
using namespace std;

int main() {
    cout << "\n----------------------------------------------\n"
            "        Welcome to my simple calculator"
            "\n----------------------------------------------\n\n";
    cout << "   Instructions :\n"
            "       This program performs basic arithmetic operations\n"
            "       such as addition, subtraction, multiplication, and\n"
            "       division. You should enter two numbers and choose\n"
            "       an operation to perform in this format :\n"
            "           <first_number> <operation> <second_number>\n"
            "       These are the valid operations : [+ , - , * , /]\n\n";
    bool quit = false;
    while (!quit) {
        bool validChoice = false;
        while (!validChoice) {
            int choice;
            cout << "\n\n----------------------------------------\n"
                    "\n(1) Perform an operation ."
                    "\n(2) Quit ."
                    "\n\nEnter The number of your choice : ";
            cin >> choice;
            if (choice == 1) {
                validChoice = true;
                bool validOperation = false;
                while (!validOperation) {
                    cout << "\nEnter the operation that you want to perform : ";
                    long double num1, num2;
                    char operation;
                    cin >> num1 >> operation >> num2;
                    if (operation == '+') {
                        validOperation = true;
                        cout << num1 << " + " << num2 << " = " << num1 + num2;
                    } else if (operation == '-') {
                        validOperation = true;
                        cout << num1 << " - " << num2 << " = " << num1 - num2;
                    } else if (operation == '*') {
                        validOperation = true;
                        cout << num1 << " * " << num2 << " = " << num1 * num2;
                    } else if (operation == '/') {
                        if (num2 != 0) {
                            validOperation = true;
                            cout << num1 << " / " << num2 << " = " << num1 / num2;
                        } else {
                            cout << "\nCan't divide on ZERO\nTry again ..\n";
                        }
                    } else {
                        cout << "\n\nSorry! Invalid operation :("
                                "\nEnter one of the valid operations :"
                                "\n   [+ , - , * , /]"
                                "\nIn this format :"
                                "\n   <first_number> <operation> <second_number>\n\n";
                    }
                }
            } else if (choice == 2) {
                validChoice = true;
                quit = true;
                cout << "\n\nThank you for using my calculator :)\n"
                        "I hope this is not the last time .. Bye\n\n";
            } else {
                cout << "\n\nSorry! Invalid choice :(\n"
                        "Choose 1 or 2, please ..\n\n";
            }
        }
    }
    return 0;
}
