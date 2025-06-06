#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>
using namespace std;

class Node
{
    private:
    string name;
    bool isGround = false;
    complex<float> complexVoltage;
    int index;

    public:
    Node(string name);
    void setIndex(int i);
    int getIndex();
    string getName();
    void setGround(bool mode);
    void setComplexVoltage(complex<float> cv);
    complex<float> getComplexVoltage();
    void rename(string name);

    static vector<Node*> nodes;
    static Node* getNode(string node);
    static Node* findNode(string node);
    static void printAll();
    static int setIndices();
};

#endif