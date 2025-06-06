#ifndef CURRENT_SOURCE_H
#define CURRENT_SOURCE_H

#include <bits/stdc++.h>
#include "../include/Source.h"
using namespace std;

class CurrentSource: public Source
{
    public:
    static vector<CurrentSource*> currentSources;
    CurrentSource(string name, string node1, string node2, float value, float amp, float freq);
    static void addCurrentSource(string name, string node1, string node2, float value, float amp, float freq);
    static void deleteCurrentSource(string name);
    static void printAll();
};

#endif