#include "../include/Source.h"
//#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

vector<Source*> Source::sources;

Source::Source(string name, string node1, string node2, float value, float amp, float freq)
{
    this->name = name;
    n1 = Node::getNode(node1);
    n2 = Node::getNode(node2);
    this->value = value;
    this->amp = amp;
    //this->freq = freq * 2.0f * static_cast<float>(M_PI);
    const float PI_F = 3.1415927f;
    this->freq = freq * 2.0f * PI_F;
}



string Source::getName() {return name;}
pair<Node*, Node*> Source::getNodes() {return {n1, n2};}
float Source::getValue() {return value;}
string Source::getType() {return type;}
float Source::getFreq(){return freq;}
complex<float> Source::getComplexValue(){return complexValue;}


void Source::calComplexValues(float freq)
{

}

