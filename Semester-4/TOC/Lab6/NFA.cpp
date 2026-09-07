#include <iostream>
#include <string>
using namespace std;

bool checkEndsWithOne(string str) {
    
    bool inState1 = false;
    
    for(char c : str) {
        if(c == '1') {
            inState1 = true;  // We can be in accept state
        } else if(c == '0') {
            inState1 = false; // Cannot be in accept state after 0
        }
    }
    
    return inState1;
}

int main() {
    string input;
    
    cout << "Enter binary string: ";
    cin >> input;
    
    if(checkEndsWithOne(input)) {
        cout << "ACCEPTED - ends with 1" << endl;
    } else {
        cout << "REJECTED - doesn't end with 1" << endl;
    }
    
    return 0;
}