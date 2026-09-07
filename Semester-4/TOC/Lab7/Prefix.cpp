#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;
    
    cout << "\nPrefixes: ";
    for(int i = 0; i <= s.length(); i++)
        cout << s.substr(0, i) << " ";
    
    cout << "\nSuffixes: ";
    for(int i = 0; i <= s.length(); i++)
        cout << s.substr(s.length() - i) << " ";
    
    cout << "\nSubstrings: ";
    for(int i = 0; i < s.length(); i++)
        for(int j = 1; j <= s.length() - i; j++)
            cout << s.substr(i, j) << " ";
    
    return 0;
}
