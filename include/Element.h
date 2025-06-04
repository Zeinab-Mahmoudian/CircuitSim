#ifndef ELEMENT_H
#define ELEMENT_H

#include <bits/stdc++.h>
#include "Node.h"

class Element
{
    protected:
    string name;
    Node *n1, *n2;
    float value;
    string type;

    public:
    Element(string name, string node1, string node2, float value);

    string getName();
    pair<Node*, Node*> getNodes();
    float getValue();
    string getType();

    static vector<Element*> elements;
    static void printAll();
};

#endif 