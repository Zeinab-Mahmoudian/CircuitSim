#include <bits/stdc++.h>
#include "../include/Exceptions.h"
#include "../include/Node.h"
#include "../include/Element.h"
#include "../include/Resistor.h"
#include "../include/Capacitor.h"
#include "../include/Inductor.h"
#include "../include/Diode.h"
#include "../include/Schematic.h"
#include "../include/CircuitUtils.h"
#include "../include/SchematicManager.h"
#include "../include/InputHandling.h"
// #include "../include/Source.h"
// #include "../include/VoltageSource.h"
// #include "../include/CurrentSource.h"
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