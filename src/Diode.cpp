#include "../include/Element.h"
#include "../include/Diode.h"
#include <bits/stdc++.h>
using namespace std;

Diode::Diode(string name, string node1, string node2, char model):
Element(name, node1, node2, 0)
{
    this->type = "diode"; 
    this->model = model;

    if(model == 'Z') this->value = 0.7;
    else this->value = 0;
}

void Diode::addDiode(string name, string node1, string node2, char model)
{
    if(model != 'Z' && model != 'D')
    {cout << "Error: Model " << model << " not found in library" << endl; return;}

    for(auto e: elements)
    {
        if(e->getName() == name)
        {cout << "Error: diode " << name << " already exists in the circuit" << endl; return;}
    }

    elements.push_back(new Diode(name, node1, node2, model));
}

void Diode::deleteDiode(string name)
{
    for(int i = 0; i < elements.size(); i++)
    {
        if(elements[i]->getName() == name)
        {delete elements[i]; elements.erase(elements.begin() + i); return;}
    }

    cout << "Error: Cannot delete diode; component not found" << endl;
}

void Diode::printAll()
{
    cout << "Diodes:" << endl;
    for(auto e: elements)
    {
        if(e->getType() == "diode") cout << e->getName() << endl;
    }
}