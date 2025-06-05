#include "../include/Schematic.h"
#include <bits/stdc++.h>
using namespace std;

vector<Schematic*> Schematic::schematics;

Schematic::Schematic(string name, string address)
{
    this->name = name;
    this->address = address;
    schematics.push_back(this);
}

void Schematic::showAll()
{
    cout << "-choose existing schematic:" << endl;
    for (int i = 0; i < schematics.size(); i++)
    {
        cout << i + 1 << '-' << schematics[i]->name << endl;
    }

    string input;
    getline(cin, input);
    smatch match;
    bool valid = false;

    while (!valid)
    {
        if (regex_match(input, match, regex("(\\s*)(return)(\\s*)")))
        {
            return;
        }

        if (regex_match(input, match, regex("(\\s*)(\\d+)(\\s*)")))
        {
            int index = stoi(match[2].str());
            index--;
            if (index >= 0 && index < schematics.size())
            {
                valid = true;
                schematics[index]->show();
            }
        }
        
        if (!valid)
        {
            throw InvalidInputException();
        }
    }
}

void Schematic::show()
{
    cout << name << ":\n";

}