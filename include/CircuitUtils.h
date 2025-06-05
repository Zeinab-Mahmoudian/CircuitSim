#ifndef CIRCUIT_UTILS_H
#define CIRCUIT_UTILS_H

#include "../include/Exceptions.h"
#include "../include/Node.h"
#include "../include/Element.h"
#include "../include/Resistor.h"
#include "../include/Capacitor.h"
#include "../include/Inductor.h"
#include "../include/Diode.h"
#include "../include/Schematic.h"
#include "../include/CircuitUtils.h"
#include "../include/SchematicManager.h"
#include "../include/Sinusoidal.h"
#include <bits/stdc++.h>

bool parseCommands(string input);

void setGround(string node);
void deleteGround(string node);

vector<string> separateArgs (string input);

void calNodeVoltage(float freq);

#endif