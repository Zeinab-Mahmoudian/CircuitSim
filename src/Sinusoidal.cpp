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
    //int c = 0;
    while (time <= tstop){
        //cout << c++ << ' ' ;
        angle = freq * time + phase;
        x = cos(angle) * amp + dc;
        ans.push_back(x);
        time += tstep;
    }
    //cout << ans.size()<< endl;
    return ans;
}

void fill(vector<vector<float>> &ans, int i, complex<float> x, float freq, float tstart, float tstop, float tstep){
    //cout << "is is " << i << endl;
    float amp = abs(x);
    float phase = atan2(x.imag(), x.real());
    Sinusoidal* s = new Sinusoidal(amp, freq, phase, 0);
    auto v = s->value(tstart, tstop, tstep);
    //cout << v.size() << endl;
    for (int j = 0; j < min(v.size(), ans.size()); j++){
        //cout << j << ' ';
        ans[i][j] += v[j];
    }    
    //cout << "done filling" << endl;
}
