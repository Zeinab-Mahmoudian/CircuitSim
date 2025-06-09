#include "../include/CircuitUtils.h"
#include <bits/stdc++.h>
using namespace std;

void setGround(string node)
{
    Node *gnd = Node::getNode(node);
    gnd->setGround(true);
}

void deleteGround(string node)
{
    Node *gnd = Node::findNode(node);
    if(gnd == nullptr)
    {
        throw NodeNotExistException();
        return;
    }

    gnd->setGround(false);
}

void calNodeVoltage(float freq, vector<Node*> nodes, Source* source, vector<vector<float>>& ans, float tstart, float tstop, float tstep){
    Element::calComplexValues(freq);
    int n = Node::setIndices();
    int m = VoltageSource::voltageSources.size();
    complex<float> a[n + m][n + m];
    complex<float> b[n + m];
    complex<float> x[n + m];

    for (int i = 0; i < n + m; i++){
        for (int j = 0; j < n + m; j++){
            a[i][j] = complex<float>(0, 0);
        }
        b[i] = complex<float>(0, 0);
    }

    for (auto e : Element::elements){
        pair<Node*, Node*> p = e->getNodes();
        int i = p.first->getIndex();
        int j = p.second->getIndex();
        complex<float> z = e->getComplexValue();
        complex<float> g = 1.0f / z;
        if (i != -1){
            a[i][i] += g;
        }
        if (j != -1){
            a[j][j] += g;
        }
        if ((i != -1) && (j != -1)){
            a[i][j] -= g;
            a[j][i] -= g;
        }
    }
    int c = n;
    for (auto s : Source::sources){
        if (s->getType() == "voltage"){
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            complex<float> z = s->getComplexValue();
            if (s != source){
                z = complex<float>(0,0);
            }
            if (i != -1){
                a[c][i] = 1;
                a[i][c] = 1;
            }
            if (j != -1){
                a[c][j] = -1;
                a[j][c] = -1;
            }
            b[c] = z;
            c++;
        }
        else if (s->getType() == "current"){
            if (s != source){
                continue;
            }
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            complex<float> z = s->getComplexValue();
            if (i != -1){
                b[i] -= z;
            }
            if (j != -1){               
                b[j] += z;
            }
        }
    }
    

    const float eps = 1e-10f;
    for (int i = 0; i < n + m; i++) {
        if (abs(a[i][i]) < eps) {
            bool found_pivot = false;
            for (int j = i + 1; j < n + m; j++) {
                if (abs(a[j][i]) > eps) {
                    for (int k = 0; k < n + m; ++k) {
                        swap(a[i][k], a[j][k]);
                    }
                    swap(b[i], b[j]);
                    found_pivot = true;
                    break;
                }
            }
            if (!found_pivot) {
                throw runtime_error("Oops! Is your circuit connected?!");
                //throw runtime_error("Matrix is singular or poorly conditioned");
            }
        }
        for (int j = i + 1; j < n + m; j++) {
            complex<float> factor = a[j][i] / a[i][i];
            for (int k = i; k < n + m; k++)
                a[j][k] -= factor * a[i][k];
            b[j] -= factor * b[i];
        }
    }
    for (int i = n + m - 1; i >= 0; i--) {
        complex<float> sum = b[i];
        for (int j = i + 1; j < n + m; j++)
            sum -= a[i][j] * x[j];
        x[i] = sum / a[i][i];
    }


    for (int i = 0; i < nodes.size(); i++){
        c = nodes[i]->getIndex();
        //fill(ans, i, x[c], freq, tstart, tstop, tstep);
        fill(ans, 0, x[c], freq, tstart, tstop, tstep);
    }

    //
    for (int i = n; i < n + m; i++){

    }

}

void calNodeVoltageDC(vector<Node*> nodes, vector<vector<float>>& ans, float tstart, float tstop, float tstep){

    int Lcnt = Element::calDCValues();
    int n = Node::setIndices();
    int m = VoltageSource::voltageSources.size();
    int itr = m + n;
    m += Lcnt;
    float a[n + m][n + m];
    float b[n + m];
    float x[n + m];

    for (int i = 0; i < n + m; i++){
        for (int j = 0; j < n + m; j++){
            a[i][j] = 0.0f;
        }
        b[i] = 0.0f;
    }

    for (auto e : Element::elements){
        pair<Node*, Node*> p = e->getNodes();
        int i = p.first->getIndex();
        int j = p.second->getIndex();
        float r = e->getDCValue();
        float g;
        if (r == -1){
            //capacitor
            continue;
        }
        if (r == 0){
            //inductor -> V(0)
            if (i != -1){
                a[itr][i] = 1;
                a[i][itr] = 1;
            }
            if (j != -1){
                a[itr][j] = -1;
                a[j][itr] = -1;
            }
            b[itr] = 0;
            itr++;
        }
        else{
            g = 1.0f / r;
            if (i != -1){
                a[i][i] += g;
            }
            if (j != -1){
                a[j][j] += g;
            }
            if ((i != -1) && (j != -1)){
                a[i][j] -= g;
                a[j][i] -= g;
            }
    }
    }
    int c = n;
    for (auto s : Source::sources){
        if (s->getType() == "voltage"){
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            float v = s->getValue();
            if (i != -1){
                a[c][i] = 1;
                a[i][c] = 1;
            }
            if (j != -1){
                a[c][j] = -1;
                a[j][c] = -1;
            }
            b[c] = v;
            c++;
        }
        else if (s->getType() == "current"){
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            float ii = s->getValue();
            if (i != -1){
                b[i] -= ii;
            }
            if (j != -1){               
                b[j] += ii;
            }
        }
    }

    // for (int i = 0; i < n + m; i++){
    //     for (int j = 0; j < n + m; j++){
    //         cout << a[i][j] <<' ';
    //     }
    //     //cout << b[i] << endl;
    // }



    for (int i = 0; i < n + m; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n + m; ++k) {
            if (abs(a[k][i]) > abs(a[maxRow][i])) {
                maxRow = k;
            }
        }
        for (int j = 0; j < n + m; ++j) {
            swap(a[i][j], a[maxRow][j]);
        }
        swap(b[i], b[maxRow]); 
        for (int j = i + 1; j < n + m; j++) {
            float factor = a[j][i] / a[i][i];
            for (int k = i; k < n + m; k++)
                a[j][k] -= factor * a[i][k];
            b[j] -= factor * b[i];
        }
    }
    for (int i = n + m - 1; i >= 0; i--) {
        float sum = b[i];
        for (int j = i + 1; j < n + m; j++)
            sum -= a[i][j] * x[j];
        x[i] = sum / a[i][i];
    }

    // for (int i = 0; i < n + m; i++){
    //     cout << x[i] << endl;
    // }

    for (int i = 0; i < nodes.size(); i++){
        c = nodes[i]->getIndex();
        //fillDC(ans, i, x[c]);
        fillDC(ans, 0, x[c]);
    }

    //
    for (int i = n; i < n + m; i++){

    }
}

void transVoltage(float tstart, float tstop, float tstep, string node){
    Node* n = Node::findNode(node);
    if (n == nullptr){
        throw NodeNotExistNameException(node);
        return;
    }
    int steps = static_cast<int>(round((tstop - tstart) / tstep));
    steps++;
    vector<float> v(steps, 0.0f);
    vector<vector<float>> ans(1, v);
    vector<Node*> nodes(1, n);
    for (auto s : Source::sources){
        calNodeVoltage(s->getFreq(), nodes, s, ans, tstart, tstop, tstep);
    }
    calNodeVoltageDC(nodes, ans, tstart, tstop, tstep);

    cout << "Analysis Result for V(" << node << "):\n";
    cout << setw(10) << "Time" << setw(10) << "Voltage" << "\n";
    int c = 0;
    float time = tstart;
    while (time <= tstop){
        if (c >= ans[0].size()){
            break;
        }
        cout << setw(10) << time << setw(10) << ans[0][c++] << "\n";
        time += tstep;
    }
}

complex<float> calNodeVoltageComplex(float freq, vector<Node*> nodes, Source* source, float tstart, float tstop, float tstep){
    Element::calComplexValues(freq);
    int n = Node::setIndices();
    int m = VoltageSource::voltageSources.size();
    complex<float> a[n + m][n + m];
    complex<float> b[n + m];
    complex<float> x[n + m];

    for (int i = 0; i < n + m; i++){
        for (int j = 0; j < n + m; j++){
            a[i][j] = complex<float>(0, 0);
        }
        b[i] = complex<float>(0, 0);
    }

    for (auto e : Element::elements){
        pair<Node*, Node*> p = e->getNodes();
        int i = p.first->getIndex();
        int j = p.second->getIndex();
        complex<float> z = e->getComplexValue();
        complex<float> g = 1.0f / z;
        if (i != -1){
            a[i][i] += g;
        }
        if (j != -1){
            a[j][j] += g;
        }
        if ((i != -1) && (j != -1)){
            a[i][j] -= g;
            a[j][i] -= g;
        }
    }
    int c = n;
    for (auto s : Source::sources){
        if (s->getType() == "voltage"){
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            complex<float> z = s->getComplexValue();
            if (s != source){
                z = complex<float>(0,0);
            }
            if (i != -1){
                a[c][i] = 1;
                a[i][c] = 1;
            }
            if (j != -1){
                a[c][j] = -1;
                a[j][c] = -1;
            }
            b[c] = z;
            c++;
        }
        else if (s->getType() == "current"){
            if (s != source){
                continue;
            }
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            complex<float> z = s->getComplexValue();
            if (i != -1){
                b[i] -= z;
            }
            if (j != -1){               
                b[j] += z;
            }
        }
    }
    

    const float eps = 1e-10f;
    for (int i = 0; i < n + m; i++) {
        if (abs(a[i][i]) < eps) {
            bool found_pivot = false;
            for (int j = i + 1; j < n + m; j++) {
                if (abs(a[j][i]) > eps) {
                    for (int k = 0; k < n + m; ++k) {
                        swap(a[i][k], a[j][k]);
                    }
                    swap(b[i], b[j]);
                    found_pivot = true;
                    break;
                }
            }
            if (!found_pivot) {
                throw runtime_error("Oops! Is your circuit connected?!");
            }
        }
        for (int j = i + 1; j < n + m; j++) {
            complex<float> factor = a[j][i] / a[i][i];
            for (int k = i; k < n + m; k++)
                a[j][k] -= factor * a[i][k];
            b[j] -= factor * b[i];
        }
    }
    for (int i = n + m - 1; i >= 0; i--) {
        complex<float> sum = b[i];
        for (int j = i + 1; j < n + m; j++)
            sum -= a[i][j] * x[j];
        x[i] = sum / a[i][i];
    }

    return (x[nodes[0]->getIndex()] - x[nodes[1]->getIndex()]);
}

complex<float> calNodeVoltageDCComplex(vector<Node*> nodes, float tstart, float tstop, float tstep){
    int Lcnt = Element::calDCValues();
    int n = Node::setIndices();
    int m = VoltageSource::voltageSources.size();
    int itr = m + n;
    m += Lcnt;
    float a[n + m][n + m];
    float b[n + m];
    float x[n + m];

    for (int i = 0; i < n + m; i++){
        for (int j = 0; j < n + m; j++){
            a[i][j] = 0.0f;
        }
        b[i] = 0.0f;
    }

    for (auto e : Element::elements){
        pair<Node*, Node*> p = e->getNodes();
        int i = p.first->getIndex();
        int j = p.second->getIndex();
        float r = e->getDCValue();
        float g;
        if (r == -1){
            //capacitor
            continue;
        }
        if (r == 0){
            //inductor -> V(0)
            if (i != -1){
                a[itr][i] = 1;
                a[i][itr] = 1;
            }
            if (j != -1){
                a[itr][j] = -1;
                a[j][itr] = -1;
            }
            b[itr] = 0;
            itr++;
        }
        else{
            g = 1.0f / r;
            if (i != -1){
                a[i][i] += g;
            }
            if (j != -1){
                a[j][j] += g;
            }
            if ((i != -1) && (j != -1)){
                a[i][j] -= g;
                a[j][i] -= g;
            }
        }
    }
    int c = n;
    for (auto s : Source::sources){
        if (s->getType() == "voltage"){
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            float v = s->getValue();
            if (i != -1){
                a[c][i] = 1;
                a[i][c] = 1;
            }
            if (j != -1){
                a[c][j] = -1;
                a[j][c] = -1;
            }
            b[c] = v;
            c++;
        }
        else if (s->getType() == "current"){
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            float ii = s->getValue();
            if (i != -1){
                b[i] -= ii;
            }
            if (j != -1){               
                b[j] += ii;
            }
        }
    }

    for (int i = 0; i < n + m; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n + m; ++k) {
            if (abs(a[k][i]) > abs(a[maxRow][i])) {
                maxRow = k;
            }
        }
        for (int j = 0; j < n + m; ++j) {
            swap(a[i][j], a[maxRow][j]);
        }
        swap(b[i], b[maxRow]); 
        for (int j = i + 1; j < n + m; j++) {
            float factor = a[j][i] / a[i][i];
            for (int k = i; k < n + m; k++)
                a[j][k] -= factor * a[i][k];
            b[j] -= factor * b[i];
        }
    }
    for (int i = n + m - 1; i >= 0; i--) {
        float sum = b[i];
        for (int j = i + 1; j < n + m; j++)
            sum -= a[i][j] * x[j];
        x[i] = sum / a[i][i];
    }
    return (x[nodes[0]->getIndex()] - x[nodes[1]->getIndex()]);
}

void transCurrent(float tstart, float tstop, float tstep, string element){
    Element* e = Element::findElement(element);
    if (e == nullptr){
        throw ComponentNotExistException(element);
        return;
    }
    int steps = static_cast<int>(round((tstop - tstart) / tstep));
    steps++;
    vector<float> v(steps, 0.0f);
    vector<vector<float>> ans(1, v);
    pair<Node*, Node*> p = e->getNodes();
    vector<Node*> nodes;
    nodes.push_back(p.first);
    nodes.push_back(p.second);
    complex<float> deltaV;
    for (auto s : Source::sources){
        deltaV = calNodeVoltageComplex(s->getFreq(), nodes, s, tstart, tstop, tstep);
        Element::calComplexValues(s->getFreq());
        deltaV /= e->getComplexValue();
        fill(ans, 0, deltaV, s->getFreq(), tstart, tstop, tstep);
    }
    deltaV = calNodeVoltageDCComplex(nodes, tstart, tstop, tstep);
    if (e->getType() == "capacitor"){
        deltaV = 0;
    }else if (e->getType() == "resistor"){
        //cout << deltaV << endl;
        deltaV /= e->getComplexValue();
    }else if (e->getType() == "inductor"){
        deltaV = 0;
        // to be calculated
    }

    fill(ans, 0, deltaV, 0, tstart, tstop, tstep);

    cout << "Analysis Result for I(" << element << "):\n";
    cout << setw(10) << "Time" << setw(10) << "Current" << "\n";
    int c = 0;
    float time = tstart;
    while (time <= tstop){
        if (c >= ans[0].size()){
            break;
        }
        cout << setw(10) << time << setw(10) << ans[0][c++] << "\n";
        time += tstep;
    }
}

bool calNodeVoltageDCS(vector<float> &v, Source* source, Node* node, float start, float end, float increment){
    float value = start;
    float res;
    int Lcnt = Element::calDCValues();
    int n = Node::setIndices();
    int m = VoltageSource::voltageSources.size();
    int itr = m + n;
    m += Lcnt;
    float a[n + m][n + m];
    float b[n + m];
    float x[n + m];
    for (int i = 0; i < n + m; i++){
        for (int j = 0; j < n + m; j++){
            a[i][j] = 0.0f;
        }
        b[i] = 0.0f;
    }
    int thenode = node->getIndex();
    int thesource;

    for (auto e : Element::elements){
        pair<Node*, Node*> p = e->getNodes();
        int i = p.first->getIndex();
        int j = p.second->getIndex();
        float r = e->getDCValue();
        float g;
        if (r == -1){
            //capacitor
            continue;
        }
        if (r == 0){
            //inductor -> V(0)
            if (i != -1){
                a[itr][i] = 1;
                a[i][itr] = 1;
            }
            if (j != -1){
                a[itr][j] = -1;
                a[j][itr] = -1;
            }
            b[itr] = 0;
            itr++;
        }
        else{
            g = 1.0f / r;
            if (i != -1){
                a[i][i] += g;
            }
            if (j != -1){
                a[j][j] += g;
            }
            if ((i != -1) && (j != -1)){
                a[i][j] -= g;
                a[j][i] -= g;
            }
        }
    }

    int c = n;
    for (auto s : Source::sources){
        if (s->getType() == "voltage"){
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            float v = s->getValue();
            if (i != -1){
                a[c][i] = 1;
                a[i][c] = 1;
            }
            if (j != -1){
                a[c][j] = -1;
                a[j][c] = -1;
            }
            // b[c] = v;
            if (s == source){
                thesource = c;
            }else{
                b[c] = v;
            }
            c++;
        }
        else if (s->getType() == "current"){
            if (s == source){
                continue;
            }
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            float ii = s->getValue();
            if (i != -1){
                b[i] -= ii;
            }
            if (j != -1){               
                b[j] += ii;
            }
        }
    }

    // for (int i = 0; i < n + m; i++){
    //     for (int j = 0; j < n + m; j++){
    //         cout << a[i][j] << ' ';
    //     }
    //     cout << "      " << b[i] << endl;
    // }

    float aInverse[n + m][n + m];
    //float x[n + m];
    float aug[n + m][2 * (n + m)];
    for (int i = 0; i < n + m; ++i) {
        for (int j = 0; j < n + m; ++j)
            aug[i][j] = a[i][j];
        for (int j = 0; j < n + m; ++j)
            aug[i][j + n + m] = (i == j) ? 1.0f : 0.0f;
    }
    const float EPSILON = 1e-6;
    for (int i = 0; i < n + m; ++i) {
        float pivot = aug[i][i];
        if (fabs(pivot) < EPSILON) {
            return false;
        }
        for (int j = 0; j < 2 * (n + m); ++j)
            aug[i][j] /= pivot;
        for (int k = 0; k < n + m; ++k) {
            if (k == i) continue;
            float factor = aug[k][i];
            for (int j = 0; j < 2 * (n + m); ++j)
                aug[k][j] -= factor * aug[i][j];
        }
    }
    for (int i = 0; i < n + m; ++i)
        for (int j = 0; j < n + m; ++j)
            aInverse[i][j] = aug[i][j + n + m];




    while (value <= end){

        if (source->getType() == "voltage"){
            b[thesource] = value;
        }
        else if (source->getType() == "current"){
            pair<Node*, Node*> p = source->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            if (value != start){
                if (i != -1){
                    b[i] -= increment;
                }
                if (j != -1){               
                    b[j] += increment;
                }
            }else{
                if (i != -1){
                    b[i] -= value;
                }
                if (j != -1){               
                    b[j] += value;
                }
            }
        }

        //x = A-1 * b;
        for (int i = 0; i < n + m; ++i) {
            x[i] = 0;
            for (int j = 0; j < n + m; ++j)
                x[i] += aInverse[i][j] * b[j];
        }

        res = x[thenode];
        v.push_back(res);
        value += increment;
    }
    return true;
}

void DCVoltage(string source, float start, float end, float increment, string node){
    Node* n = Node::findNode(node);
    Source* s = Source::findSource(source);
    if (n == nullptr){
        throw NodeNotExistNameException(node);
        return;
    }
    if (s == nullptr){
        throw SourceNotExistNameException(source);
        return;
    }
    int steps = static_cast<int>(round((end - start) / increment));
    steps++;
    float value = start;
    //vector<float> v(steps, 0.0f);
    vector<float> v;
    bool check = calNodeVoltageDCS(v, s, n, start, end, increment);
    if (!check){
        throw runtime_error("Oops! Is your circuit connected?!");
        return;
    }
    cout << "DC Sweep of " << source << ", Result for V(" << node << "):\n";
    float res;
    int c = 0;
    while (value <= end){
        res = v[c++];
        //v.push_back(res);
        cout << res << ' ';
        value += increment;
    }
    cout << endl;
}

void DCCurrent(string source, float start, float end, float increment, string element){
    //cout << element << endl;
    Element* e = Element::findElement(element);
    Source* s = Source::findSource(source);
    if (e == nullptr){
        throw ElementNotExistNameException(element);
        return;
    }
    if (s == nullptr){
        throw SourceNotExistNameException(source);
        return;
    }
    // if (e->getType() == "capacitor"){
    //     cout << "It's gonna be equal to zero! Capacitor works like oc in DC!" << endl;
    //     return;
    // }    
    // if (e->getType() == "inductor"){
    //     cout << "It's gonna be equal to zero! Capacitor works like oc in DC!" << endl;
    //     return;
    // }
    int steps = static_cast<int>(round((end - start) / increment));
    steps++;
    float value = start;
    //vector<float> v(steps, 0.0f);
    vector<float> v1;
    vector<float> v2;
    pair<Node*, Node*> p = e->getNodes();
    bool check = calNodeVoltageDCS(v1, s, p.first, start, end, increment);
    if (!check){
        throw runtime_error("Oops! Is your circuit connected?!");
        return;
    }
    check = calNodeVoltageDCS(v2, s, p.second, start, end, increment);
    if (!check){
        throw runtime_error("Oops! Is your circuit connected?!");
        return;
    }
        if (e->getType() == "capacitor"){
        cout << "It's gonna be equal to zero! Capacitor works like oc in DC!" << endl;
        return;
    }    
    if (e->getType() == "inductor"){
        cout << "" << endl;
        return;
    }
    cout << "DC Sweep of " << source << ", Result for I(" << element << "):\n";
    float res;
    int c = 0;
    float r = e->getDCValue();
    while (value <= end){
        res = v1[c] - v2[c];
        res /= r;
        cout << res << ' ';
        value += increment;
        c++;
    }
    cout << endl;
}