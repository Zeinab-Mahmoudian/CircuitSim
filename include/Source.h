#ifndef SOURCE_H
#define SOURCE_H

#include <bits/stdc++.h>
#include "../include/Exceptions.h"
#include "../include/Node.h"

class Source
{
    protected:
    string name;
    Node *n1, *n2;
    float value;
    complex<float> complexValue;
    string type;

    public:
    Source(string name, string node1, string node2, float value);

    string getName();
    pair<Node*, Node*> getNodes();
    float getValue();
    string getType();

    static vector<Source*> sources;
    static void printAll();

    static void calComplexValues(float freq);
};

#endif 