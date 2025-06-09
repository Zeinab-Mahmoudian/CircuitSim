#include "../include/Element.h"
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
complex<float> Element::getComplexValue(){return complexValue;}
float Element::getDCValue(){return DCValue;}


void Element::printAll()
{
    cout << "All Elements:" << endl;
    for(auto e: elements)
    {
        cout << e->getName() << endl;
    }
}

void Element::calComplexValues(float freq)
{
    float r, i;
    for (auto e : elements){
        if (e->type == "resistor"){
            r = e->value;
            i = 0;
        }
        else if (e->getType() == "capacitor"){
            r = 0;
            i = (-1) /((e->value) * freq);
        }
        else if (e->getType() == "inductor"){
            r = 0;
            i = (e->value) * freq;
        }
        e->complexValue = complex<float>(r, i);
    }
}

int Element::calDCValues()
{
    int cnt = 0;
    for (auto e : elements){
        if (e->type == "resistor"){
            e->DCValue = e->value;
        }
        else if (e->getType() == "capacitor"){
            e->DCValue = -1;
        }
        else if (e->getType() == "inductor"){
            e->DCValue = 0;
            cnt++;
        }
    }
    return cnt;
}

Element* Element::findElement(string name){
    for (Element* e : elements){
        if (e->name == name){
            return e;
        }
    }
    return nullptr;
}
