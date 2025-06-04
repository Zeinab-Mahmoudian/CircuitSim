#include "../include/Element.h"
#include "../include/Node.h"
#include <bits/stdc++.h>
using namespace std;

vector<Element*> Element::elements;

Element::Element(string name, string node1, string node2, float value)
{
    this->name = name;
    n1 = Node::getNode(node1);
    n2 = Node::getNode(node2);
    this->value = value;
}



string Element::getName() {return name;}
pair<Node*, Node*> Element::getNodes() {return {n1, n2};}
float Element::getValue() {return value;}
string Element::getType() {return type;}


void Element::printAll()
{
    cout << "All Elements:" << endl;
    for(auto e: elements)
    {
        cout << e->getName() << endl;
    }
}

