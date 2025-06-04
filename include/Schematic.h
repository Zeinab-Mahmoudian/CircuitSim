#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <bits/stdc++.h>
#include "../include/Element.h"

class Schematic
{
    private:
    string name, address;

    public:
    static vector<Schematic*> schematics;
    Schematic(string name, string address);
    static void showAll();
    void show();
};

#endif