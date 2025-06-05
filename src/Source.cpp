#include "../include/Source.h"
#include "../include/Node.h"
#include <bits/stdc++.h>
using namespace std;

vector<Source*> Source::sources;

Source::Source(string name, string node1, string node2, float value)
{
    this->name = name;
    n1 = Node::getNode(node1);
    n2 = Node::getNode(node2);
    this->value = value;
}



string Source::getName() {return name;}
pair<Node*, Node*> Source::getNodes() {return {n1, n2};}
float Source::getValue() {return value;}
string Source::getType() {return type;}


void Source::calComplexValues(float freq)
{

}

