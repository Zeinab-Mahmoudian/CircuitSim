#ifndef DIODE_H
#define DIODE_H

#include <bits/stdc++.h>
#include "../include/Element.h"

class Diode: public Element
{
    char model;

    public:
    Diode(string name, string node1, string node2, char model);

    static void addDiode(string name, string node1, string node2, char model);
    static void deleteDiode(string name);
    static void printAll();
};

#endif