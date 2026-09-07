#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "Hello we are ce";
    
    cout << "Original text: " << text << endl;
    
    // Replaces all 'e' with 'i'
    for(int i = 0; i < text.length(); i++) {
        if(text[i] == 'e') {
            text[i] = 'i';
        }
    }
    
    cout << "Modified text: " << text << endl;
    
    return 0;
}
