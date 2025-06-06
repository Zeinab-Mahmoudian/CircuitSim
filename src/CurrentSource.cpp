#include "../include/Source.h"
#include "../include/CurrentSource.h"
#include <bits/stdc++.h>
using namespace std;

vector<CurrentSource*> CurrentSource::currentSources;


CurrentSource::CurrentSource(string name, string node1, string node2, float value, float amp, float freq):
Source(name, node1, node2, value, amp, freq) {
    this->type = "current";
    this->complexValue.real(0);
    this->complexValue.imag(-1 * amp);
    currentSources.push_back(this);
}

void CurrentSource::addCurrentSource(string name, string node1, string node2, float value, float amp, float freq)
{
    if(value <= 0)
    {

    }

    for(auto s: sources)
    {

    }

    sources.push_back((Source*) new CurrentSource(name, node1, node2, value, amp, freq));
}

void CurrentSource::deleteCurrentSource(string name)
{

}

void CurrentSource::printAll()
{

}