#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    bool final = false;
    Node *aip = NULL; // transition on 'a'
    Node *bip = NULL; // transition on 'b'
    Node *eip = NULL; // epsilon transition
};

class Pda {
public:
    Node q0, q1, q2;

    // Stack
    char a[1005];
    char tos;    
    int j;     

    Pda() {
        q0.name = "q0";
        q1.name = "q1";
        q2.name = "q2";
        q2.final = true;

        
        q0.aip = &q0; // stay in q0 on 'a' (push 'a')
        q0.bip = &q1; // move to q1 on first 'b' (pop one 'a')
        q1.bip = &q1; // stay in q1 on 'b' (pop one 'a')
        q1.eip = &q2; // accept by epsilon when stack back to Z

        reset_stack();
    }

    void reset_stack() {
        a[0] = 'Z';
        tos = 'Z';
        j = 1; 
    }

    void st_push(char y) {
        a[j] = y;
        tos = a[j];
        j++;
    }

    bool can_pop_a() const {
        return j > 1 && a[j - 1] == 'a';
    }

    void st_pop() {
        if (j > 1) {
            j--;
            tos = a[j - 1]; 
        }
    }

    bool identify(const string &x) {
        
        reset_stack();

        Node *present = &q0;
        int cntA = 0, cntB = 0;

        for (int i = 0; i < (int)x.size(); i++) {
            char c = x[i];

            if (present == &q0) {
                if (c == 'a') {
                    st_push('a');
                    cntA++;
                    present = present->aip; // stay in q0
                } else if (c == 'b' && can_pop_a()) {
                    st_pop();
                    cntB++;
                    present = present->bip; // move to q1
                } else {
                    return false; // invalid 
                }
            } else if (present == &q1) {
                if (c == 'b' && can_pop_a()) {
                    st_pop();
                    cntB++;
                    present = present->bip; // stay in q1
                } else {
                    return false; 
                }
            } else {
                return false; // unknown state
            }
        }

        
        if (present == &q1 && tos == 'Z' && cntA > 0 && cntB > 0) {
            present = present->eip; 
        }
        return (present == &q2) && q2.final;
    }
};

int main() {
    Pda p;
    string input;
    cout << "Enter a string (only a's followed by b's): ";
    cin >> input;

    if (p.identify(input))
        cout << "Accepted\n";
    else
        cout << "Rejected\n";
    return 0;
}

