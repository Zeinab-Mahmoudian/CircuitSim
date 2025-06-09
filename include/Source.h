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
    float value, amp, freq, phase;
    complex<float> complexValue;
    string type;

    public:
    Source(string name, string node1, string node2, float value, float amp, float freq);

    string getName();
    pair<Node*, Node*> getNodes();
    float getValue();
    string getType();
    float getFreq();
    complex<float> getComplexValue();

    static vector<Source*> sources;
    static void printAll();

    static void calComplexValues(float freq);
    static Source* findSource(string name);

};


#endif 