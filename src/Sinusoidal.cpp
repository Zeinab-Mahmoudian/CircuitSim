#include "../include/Sinusoidal.h"
#include <bits/stdc++.h>
using namespace std;

Sinusoidal::Sinusoidal(float amp, float freq, float phase, float dc){
    this->amp = amp;
    this->freq = freq;
    this->phase = phase;
    this->dc = dc;
}

vector<float> Sinusoidal::value(float tstart, float tstop, float tstep){
    float time = tstart;
    float angle;
    float x;
    vector<float> ans;
    while (time <= tstop){
        angle = freq * time + phase;
        x = cos(angle) * amp + dc;
        ans.push_back(x);
        time += tstep;
    }
    return ans;
}
