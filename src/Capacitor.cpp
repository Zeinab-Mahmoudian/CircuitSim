#include "../include/Capacitor.h"
#include <bits/stdc++.h>
using namespace std;

Capacitor::Capacitor(string name, string node1, string node2, float value):
Element(name, node1, node2, value) {this->type = "capacitor";}

void Capacitor::addCapacitor(string name, string node1, string node2, float value)
{
    if(value <= 0)
    {
        throw CRangeException();
        return;
    }

    for(auto e: elements)
    {
        if(e->getName() == name)
        {
            throw CDuplicateNameException(name);
            return;
        }
    }

    elements.push_back((Element*) new Capacitor(name, node1, node2, value));
}

void Capacitor::deleteCapacitor(string name)
{
    for(int i = 0; i < elements.size(); i++)
    {
        if(elements[i]->getName() == name)
        {delete elements[i]; elements.erase(elements.begin() + i); return;}
    }
    throw C404Exception();
}

void Capacitor::printAll()
{
    cout << "Capacitors:" << endl;
    for(auto e: elements)
    {
        if(e->getType() == "capacitor") cout << e->getName() << endl;
    }
}