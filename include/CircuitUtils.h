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
#include "../include/Source.h"
#include "../include/VoltageSource.h"
#include "../include/CurrentSource.h"
#include <bits/stdc++.h>


void setGround(string node);
void deleteGround(string node);

void calNodeVoltage(float freq, vector<Node*> nodes, Source* source, vector<vector<float>>& ans, float tstart, float tstop, float tstep);
void calNodeVoltageDC(vector<Node*> nodes, vector<vector<float>>& ans, float tstart, float tstop, float tstep);

complex<float> calNodeVoltageComplex(float freq, vector<Node*> nodes, Source* source, float tstart, float tstop, float tstep);
complex<float> calNodeVoltageDCComplex(vector<Node*> nodes, float tstart, float tstop, float tstep);

void transVoltage(float tstart, float tstop, float tstep, string node);
void transCurrent(float tstart, float tstop, float tstep, string element);

#endif