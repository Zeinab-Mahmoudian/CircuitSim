#include "../include/Node.h"
#include <bits/stdc++.h>
using namespace std;

vector<Node*> Node::nodes;


Node::Node(string name)
{
    this->name = name;
}

string Node::getName() {return name;}
void Node::setGround(bool mode) {isGround = mode;}
void Node::rename(string name) {this->name = name;}

Node* Node::getNode(string node)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->getName() == node)
        return nodes[i];
    }

    Node *newnode = new Node(node);
    nodes.push_back(newnode);

    return newnode;
}

Node* Node::findNode(string node)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->getName() == node)
        return nodes[i];
    }
    return nullptr;
}

void Node::printAll()
{
    cout << "Available nodes:" << endl;
    for(int i = 0; i < nodes.size(); i++)
    {
        cout << nodes[i]->getName();
        if(i != nodes.size() - 1) cout << ", ";
    }
    cout << endl;
}

void Node::setComplexVoltage(complex<float> cv){
    this->complexVoltage = cv;
}

complex<float> Node::getComplexVoltage(){
    return complexVoltage;
}

void Node::setIndex(int i){
    this->index = i;
}

int Node::getIndex(){
    return index;
}

int Node::setIndices(){
    int c = 0;
    for (Node* n : nodes){
        if (n->isGround){
            n->index = -1;
        }
        else{
            n->index = c++;
        }
    }
    return c;
}