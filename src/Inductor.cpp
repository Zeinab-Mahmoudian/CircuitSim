#include "../include/Element.h"
#include "../include/Inductor.h"
#include <bits/stdc++.h>
using namespace std;

Inductor::Inductor(string name, string node1, string node2, float value):
Element(name, node1, node2, value) {this->type = "inductor";}

void Inductor::addInductor(string name, string node1, string node2, float value)
{
    if(value == 0)
    {cout << "Error: Inductance cannot be zero or negative" << endl; return;}

    for(auto e: elements)
    {
        if(e->getName() == name)
        {cout << "Error: inductor " << name << " already exists in the circuit" << endl; return;}
    }

    elements.push_back(new Inductor(name, node1, node2, value));
}

void Inductor::deleteInductor(string name)
{
    for(int i = 0; i < elements.size(); i++)
    {
        if(elements[i]->getName() == name)
        {delete elements[i]; elements.erase(elements.begin() + i); return;}
    }

    cout << "Error: Cannot delete inductor; component not found" << endl;
}

void Inductor::printAll()
{
    cout << "Inductors:" << endl;
    for(auto e: elements)
    {
        if(e->getType() == "inductor") cout << e->getName() << endl;
    }
}