#ifndef CAPACITOR_H
#define CAPACITOR_H

#include <bits/stdc++.h>
#include "../include/Element.h"

class Capacitor: public Element
{
    public:
    Capacitor(string name, string node1, string node2, float value);

    static void addCapacitor(string name, string node1, string node2, float value);
    static void deleteCapacitor(string name);
    static void printAll();
};

#endif