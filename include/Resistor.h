#ifndef RESISTOR_H
#define RESISTOR_H

#include <bits/stdc++.h>
#include "../include/Element.h"

class Resistor: public Element
{
    public:
    Resistor(string name, string node1, string node2, float value);
    static void addResistor(string name, string node1, string node2, float value);
    static void deleteResistor(string name);
    static void printAll();
};

#endif