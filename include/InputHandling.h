#ifndef INPUT_HANDLING_H
#define INPUT_HANDLING_H

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
#include "../include/Source.h"
#include "../include/VoltageSource.h"
#include "../include/CurrentSource.h"
#include "../include/CircuitUtils.h"
#include <bits/stdc++.h>

bool parseCommands(string input);

vector<string> separateArgs (string input);

#endif