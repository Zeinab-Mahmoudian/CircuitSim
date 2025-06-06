#ifndef VOLTAGE_SOURCE_H
#define VOLTAGE_SOURCE_H

#include <bits/stdc++.h>
#include "../include/Source.h"
using namespace std;

class VoltageSource: public Source
{
    public:
    static vector<VoltageSource*> voltageSources;
    VoltageSource(string name, string node1, string node2, float value, float amp, float freq);
    static void addVoltageSource(string name, string node1, string node2, float value, float amp, float freq);
    static void deleteVoltageSource(string name);
    static void printAll();
};

#endif