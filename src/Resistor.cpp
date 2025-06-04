#include "../include/Element.h"
#include "../include/Resistor.h"
#include <bits/stdc++.h>
using namespace std;

Resistor::Resistor(string name, string node1, string node2, float value):
Element(name, node1, node2, value) {this->type = "resistor";}

void Resistor::addResistor(string name, string node1, string node2, float value)
{
    if(value <= 0)
    {cout << "Error: Resistance cannot be zero or negative" << endl; return;}

    for(auto e: elements)
    {
        if(e->getName() == name)
        {cout << "Error: Resistor " << name << " already exists in the circuit" << endl; return;}
    }

    elements.push_back((Element*) new Resistor(name, node1, node2, value));
}

void Resistor::deleteResistor(string name)
{
    for(int i = 0; i < elements.size(); i++)
    {
        if(elements[i]->getName() == name)
        {delete elements[i]; elements.erase(elements.begin() + i); return;}
    }

    cout << "Cannot delete resistor; component not found" << endl;
}

void Resistor::printAll()
{
    cout << "Resistors:" << endl;
    for(auto e: elements)
    {
        if(e->getType() == "resistor") cout << e->getName() << endl;
    }
}