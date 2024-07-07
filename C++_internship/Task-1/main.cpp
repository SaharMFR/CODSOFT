#include <iostream>
#include <random>
using namespace std;

int main() {
    bool quit = false;
    cout << "\n-------------------------------------------\n"
            "   Welcome in my number guessing game"
            "\n-------------------------------------------\n\n"
            "   Instructions :\n"
            "       A random number will be generated and you will guess it\n"
            "       and enter your guess , then I will provide a feedback on\n"
            "       whether the guess is too high or too low until you guess\n"
            "       the correct number .\n\n"
            "       You can enter `-1` if you want to exit and you are inside\n"
            "       the game .\n\n";
    while (!quit) {
        int choice;
        bool validChoice = false;
        while (!validChoice) {
            cout << "\n-------------------------------------------\n"
                    "(1) Start a game .\n"
                    "(2) Quit .\n"
                    "\nEnter the number of your choice : ";
            cin >> choice;
            if (choice == 1) {
                validChoice = true;
                int range;
                cout << "\nEnter the upper bound of the range of numbers\n"
                        "that you want : ";
                cin >> range;
                srand(time(0));
                int num = 1 + (rand() % range);
                int guess = num - 100;
                cout << "\n\nThe number has been generated ..\n";
//                cout << num << endl;
                while (guess != num && guess != -1) {
                    cout << "You can enter your guess : ";
                    cin >> guess;
                    if (guess == num) {
                        cout << "\n\nCool! You've guessed right ..\n"
                                "Congratulations :)\n\n";
                    } else if (guess < num) {
                        cout << "\nYour guess is lower than generated number\n"
                                "Try higher ..\n\n";
                    } else if (guess > num) {
                        cout << "\nYour guess is higher than generated number\n"
                                "Try lower ..\n\n";
                    }
                }
            } else if (choice == 2) {
                validChoice = true;
                quit = true;
                cout << "\nThank you for playing my guessing game :)\n"
                        "I hope this is not the last time .. Bye\n\n";
            } else {
                cout << "\nThis is invalid choice :(\nPlease try again ..\n\n";
            }
        }

    }

    return 0;
}
