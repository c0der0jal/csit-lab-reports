#include <iostream>
#include <string>
using namespace std;

class DFA {
    int state;

public:
    DFA() { state = 0; }

    void reset() { state = 0; }

    void process(char ch) {
        switch (state) {
            case 0:
                state = (ch == '0') ? 1 : 0;
                break;
            case 1:
                state = (ch == '0') ? 2 : 0;
                break;
            case 2:
                if (ch == '1')
                    state = 3;
                else if (ch == '0')
                    state = 2;
                else
                    state = 0;
                break;
            case 3:
                // Accepting state, stays here
                break;
        }
    }

    bool accepts(const string& input) {
        reset();
        for (size_t i = 0; i < input.length(); i++) {
            process(input[i]);
        }
        return state == 3;
    }
};

int main() {
    DFA dfa;
    string input;
    cout << "Enter binary string: ";
    cin >> input;

    if (dfa.accepts(input))
        cout << "Accepted: contains '001'\n";
    else
        cout << "Rejected: does not contain '001'\n";

    return 0;
}

