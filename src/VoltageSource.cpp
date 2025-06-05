#include "../include/Source.h"
#include "../include/VoltageSource.h"
#include <bits/stdc++.h>
using namespace std;

vector<VoltageSource*> VoltageSource::voltageSources;


VoltageSource::VoltageSource(string name, string node1, string node2, float value, float amp, float freq):
Source(name, node1, node2, value, amp, freq) {
    this->type = "voltage";
    // this->complexValue.real(amp);
    // this->complexValue.imag(0);
    this->complexValue.real(0);
    this->complexValue.imag(-1 * amp);
    voltageSources.push_back(this);
}

void VoltageSource::addVoltageSource(string name, string node1, string node2, float value, float amp, float freq)
{
    if(value <= 0)
    {

    }

    for(auto s: sources)
    {

    }

    sources.push_back((Source*) new VoltageSource(name, node1, node2, value, amp, freq));
}

void VoltageSource::deleteVoltageSource(string name)
{

}

void VoltageSource::printAll()
{

}