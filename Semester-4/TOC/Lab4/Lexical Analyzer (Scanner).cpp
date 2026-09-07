#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
    const char* keyword_array[] = {"if", "else", "while", "int", "return"};
    set<string> keywords(keyword_array, keyword_array + 5); // Sample keywords
    string operators = "+-*/%=";
    string input;

    cout << "Enter a line of code: ";
    //Example: int main() { if x + y == 5 return 1; }
    getline(cin, input);

    string token;
    for (string::size_type i = 0; i < input.length(); i++) {
        char c = input[i];
        if (isspace(c)) {
            if (!token.empty()) {
                if (keywords.find(token) != keywords.end())
                    cout << "'" << token << "' is a keyword\n";
                else
                    cout << "'" << token << "' is an identifier\n";
                token.clear();
            }
        } else if (operators.find(c) != string::npos) {
            if (!token.empty()) {
                cout << "'" << token << "' is an identifier\n";
                token.clear();
            }
            cout << "'" << c << "' is an operator\n";
        } else {
            token += c;
        }
    }
    // Check the last token
    if (!token.empty()) {
        if (keywords.find(token) != keywords.end())
            cout << "'" << token << "' is a keyword\n";
        else
            cout << "'" << token << "' is an identifier\n";
    }
    return 0;
}
