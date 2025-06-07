#include <bits/stdc++.h>
#include "../include/InputHandling.h"
using namespace std;

int main()
{
    string input;
    bool cond = true;
    while (cond) {
        getline(cin, input);
        try {
            cond = parseCommands(input);
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}