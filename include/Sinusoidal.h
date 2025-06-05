#ifndef SINUSOIDAL_H
#define SINUSOIDAL_H

#include <bits/stdc++.h>
using namespace std;

class Sinusoidal {
    private:
        float amp, freq, phase, dc;
    public:
        Sinusoidal(float amp, float freq, float phase, float dc);
        vector <float> value(float tstart, float stop, float tsetp);

};

void fill(vector<vector<float>> &ans, int i, complex<float> x, float freq, float tstart, float tstop, float tstep);


#endif