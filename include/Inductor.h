#ifndef INDUCTOR_H
#define INDUCTOR_H

#include <bits/stdc++.h>
#include "../include/Element.h"

class Inductor: public Element
{
    public:
    Inductor(string name, string node1, string node2, float value);

    static void addInductor(string name, string node1, string node2, float value);
    static void deleteInductor(string name);
    static void printAll();
};

#endif