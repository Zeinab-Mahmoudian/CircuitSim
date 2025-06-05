#ifndef ELEMENT_H
#define ELEMENT_H

#include <bits/stdc++.h>
#include "../include/Exceptions.h"
#include "../include/Node.h"

class Element
{
    protected:
    string name;
    Node *n1, *n2;
    float value;
    complex<float> complexValue;
    string type;

    public:
    Element(string name, string node1, string node2, float value);

    string getName();
    pair<Node*, Node*> getNodes();
    float getValue();
    string getType();
    complex<float> getComplexValue();
    
    static vector<Element*> elements;
    static void printAll();

    static void calComplexValues(float freq);
};

#endif 