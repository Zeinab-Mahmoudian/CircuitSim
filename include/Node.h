#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>

class Node
{
    private:
    string name;
    bool isGround = false;

    public:
    Node(string name);

    string getName();
    void setGround(bool mode);
    void rename(string name);

    static vector<Node*> nodes;
    static Node* getNode(string node);

    static Node* findNode(string node);

    static void printAll();
};

#endif