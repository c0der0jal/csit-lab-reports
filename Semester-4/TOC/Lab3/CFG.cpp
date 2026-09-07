#include <iostream>
#include <string>
using namespace std;

int main() {
    // Derive strings for the grammar: S -> aSb | e
    // This generates strings of the form a^n b^n
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    string derived_string;
    for (int i = 0; i < n; ++i) {
        derived_string = "a" + derived_string + "b";
    }

    cout << "Derived string: " << derived_string << endl;
    return 0;
}
