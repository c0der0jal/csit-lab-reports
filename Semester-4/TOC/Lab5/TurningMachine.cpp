#include <iostream>
#include <string>
using namespace std;

int main() {
    string tape;
    cout << "Enter a string (e.g., '0011'): ";
    cin >> tape;
    tape += '#'; // Add end marker

    int i = 0;
    int state = 0; // Start state

    while (state != 4 && state != -1) {
        switch (state) {
            case 0: // Look for first 0
                if (tape[i] == '0') {
                    tape[i] = 'X';
                    i++;
                    state = 1;
                } else if (tape[i] == 'Y') {
                    i++;
                    state = 3;
                } else {
                    state = -1; // Reject
                }
                break;

            case 1: // Skip 0s and Ys to find first 1
                if (tape[i] == '0' || tape[i] == 'Y') {
                    i++;
                } else if (tape[i] == '1') {
                    tape[i] = 'Y';
                    i--;
                    state = 2;
                } else {
                    state = -1;
                }
                break;

            case 2: // Move back to start
                if (tape[i] == '0' || tape[i] == 'Y') {
                    i--;
                } else if (tape[i] == 'X') {
                    i++;
                    state = 0;
                } else {
                    state = -1;
                }
                break;

            case 3: // Check if all remaining symbols are Y
                if (tape[i] == 'Y') {
                    i++;
                } else if (tape[i] == '#') {
                    state = 4; // Accept
                } else {
                    state = -1;
                }
                break;
        }
    }

    if (state == 4)
        cout << "String accepted!\n";
    else
        cout << "String rejected!\n";

    return 0;
}
