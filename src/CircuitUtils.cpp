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
// #include "../include/Source.h"
// #include "../include/VoltageSource.h"
// #include "../include/CurrentSource.h"

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

void calNodeVoltage(float freq, vector<Node*> nodes, Source* s, vector<vector<float>>& ans, float tstart, float tstop, float tstep){
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
    //int c2 = 0;
    //for (auto source : Source::sources){
    //for (auto s : Source::sources){
        if (s->getType() == "voltage"){
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            complex<float> z = s->getComplexValue();
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
            pair<Node*, Node*> p = s->getNodes();
            int i = p.first->getIndex();
            int j = p.second->getIndex();
            complex<float> z = s->getComplexValue();
            if (i != -1){
                b[i] = -1.f * z;
            }
            if (j != -1){               
                b[j] = z;
            }
        }
    //}
    
    // for (int i = 0; i < n + m; i++){
    //     for (int j = 0; j < n + m; j++){
    //         cout << a[i][j] << ' ';
    //     }
    //     cout << b[i] << endl;
    // }

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
            // if (!found_pivot) {
            //     throw runtime_error("Matrix is singular or poorly conditioned");
            // }
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
        //Sinusoidal::fill(ans, i, x[c], freq, tstart, tstop, tstep);
        fill(ans, i, x[c], freq, tstart, tstop, tstep);
    }

    // c = 0;
    // for (int i = 0; i < n; i++){
    //     while (Node::nodes[c]->getIndex() < i){
    //         c++;
    //     }
    //     for (int i = 0; i < nodes.size(); i++){
            
    //         f(ans);
    //     }
    //     //Node::nodes[i]->setComplexVoltage(x[i]);
    //     cout << i << ' ' << x[i] << ' ' << endl;
    // }

    //
    for (int i = n; i < n + m; i++){

    }

}

void transVoltage(float tstart, float tstop, float tstep, string node){
    Node* n = Node::findNode(node);
    int steps = static_cast<int>(round((tstop - tstart) / tstep));
    steps++;
    vector<float> v(steps, 0.0f);
    vector<vector<float>> ans(1, v);
    vector<Node*> nodes(1, n);
    
    for (auto s : Source::sources){
        calNodeVoltage(s->getFreq(), nodes, s, ans, tstart, tstop, tstep);
    }

    cout << "Analysis Result for V(" << node << "):\n";
    cout << setw(10) << "Time" << setw(10) << "Voltage" << "\n";
    int c = 0;
    float time = tstart;
    while (time <= tstop){
        cout << setw(10) << time << setw(10) << ans[0][c++] << "\n";
        time += tstep;
    }
}

vector<string> separateArgs (string input)
{
    stringstream ss(input);
    vector<string> ans = {};
    string arg;
    while (ss >> arg)
    {
        ans.push_back(arg);
    }
    return ans;
}

bool parseCommands(string input)
{
    vector<string> args = separateArgs(input);
    smatch match;

    if(regex_match(input, match, regex("(\\s*)(end)(\\s*)")))
    {
        return false;
    }

    if(regex_match(input, match, regex("(\\s*)(add)(\\s+)(V)(\\S+)(\\s+)(\\S+)(\\s+)(\\S+)(\\s+)(SIN\\()(\\-*\\d+\\.*\\d*)(\\s*)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s*)(\\))(\\s*)")))
    {
        string name = match[5].str();
        string node1 = match[7].str();
        string node2 = match[9].str();
        float offset = stof(match[12].str());
        float amp = stof(match[14].str());
        float freq = stof(match[16].str());
        VoltageSource::addVoltageSource(name, node1, node2, offset, amp, freq);
        return true;
    }

    if(regex_match(input, match, regex("(\\s*)(add)(\\s+)(I)(\\S+)(\\s+)(\\S+)(\\s+)(\\S+)(\\s+)(SIN\\()(\\-*\\d+\\.*\\d*)(\\s*)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s*)(\\))(\\s*)")))
    {
        string name = match[5].str();
        string node1 = match[7].str();
        string node2 = match[9].str();
        float offset = stof(match[12].str());
        float amp = stof(match[14].str());
        float freq = stof(match[16].str());
        CurrentSource::addCurrentSource(name, node1, node2, offset, amp, freq);
        return true;
    }

    //if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(TRAN)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(V\\(n\\d{3}\\))(\\s*)")))
    if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(TRAN)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(V\\()(n\\d{3})(\\))(\\s*)")))
    {
        float tstep = stof(match[6].str());
        float tstop = stof(match[8].str());
        float tstart = stof(match[10].str());
        string node = match[13].str();
        transVoltage(tstart, tstop, tstep, node);
        return true;
    }

    if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(DC)(\\s+)(.+?)(\\s+)(V\\(n\\d{3}\\))(\\s*)")))
    {
        return true;
    }

    if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(TRAN)(\\s+)(.+?)(\\s+)(I\\([RCD]\\S+\\))(\\s*)")))
    {
        return true;
    }

    if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(DC)(\\s+)(.+?)(\\s+)(I\\([RCD]\\S+\\))(\\s*)")))
    {
        return true;
    }

    //multiple variables

    if(regex_match(input, match, regex("(\\s*)(-show)(\\s+)(existing)(\\s+)(schematics)(\\s*)")))
    {
        Schematic::showAll();
        return true;
    }

    if(regex_match(input, match, regex("(\\s*)(NewFile)(\\s+)(\\S+\\.txt)(\\s*)")))
    {
        //auto address;
        string address;
        string name;
        Schematic* s = new Schematic(name, address);
        return true;
    }

    if(args.size() == 1)
    {
        if(args[0] == ".nodes") {Node::printAll(); return true;}
        else if(args[0] == ".list") {Element::printAll(); return true;}
    }

    if(args.size() == 2)
    {
        if(args[0] == "delete" && args[1][0] == 'R')
        {
            Resistor::deleteResistor(args[1].substr(1));
            return true;
        }
        if(args[0] == "delete" && args[1][0] == 'C')
        {
            Capacitor::deleteCapacitor(args[1].substr(1));
            return true;
        }
        if(args[0] == "delete" && args[1][0] == 'L')
        {
            Inductor::deleteInductor(args[1].substr(1));
            return true;
        }
        if(args[0] == ".list")
        {
            cout << args[1] << "s: " << endl;
            for(auto element: Element::elements)
            {
                if(element->getType() == args[1])
                {
                    cout << element->getName() << endl;
                }
            }
            return true;
        }
    }

    if(args.size() == 3)
    {
        if(args[0] == "add" && args[1] == "GND")
        {setGround(args[2]); return true;}

        if(args[0] == "delete" && args[1] == "GND")
        {deleteGround(args[2]); return true;}
    }

    if(args.size() == 4)
    {
        if(args[0] == ".rename" && args[1] == "node")
        {
            Node *node = Node::findNode(args[2]);
            if(node == nullptr)
            {
                throw NodeNotExistNameException(args[2]);
                return true;
            }

            if(Node::findNode(args[3]) != nullptr)
            {
                throw NodeAlreadyExistNameException(args[3]);
                return true;
            }

            node->rename(args[3]);

            cout << "SUCCESS: Node renamed from " << args[2] << " to " << args[3] << endl;
            return true;
        }
    }

    if(args.size() == 5)
    {
        if(args[0] == "add" && args[1][0] == 'R')
        {
            float value;
            if(isdigit(args[4][0])) value = stof(args[4]);
            else if(args[4].back() == 'k') value = stof(args[4]) * 1000;
            else if(args[4].back() == 'M') value = stof(args[4]) * 100000;
            else if(args[4].find('e') != string::npos)
            {
                value = stof(args[4].substr(0,args[4].find('e'))) *
                powf(10, stof(args[4].substr(args[4].find('e') + 1)));
            }
            else return true;
            Resistor::addResistor(args[1].substr(1), args[2], args[3], value);
            return true;
        }
        if(args[0] == "add" && args[1][0] == 'C')
        {
            float value;
            if(isdigit(args[4][0])) value = stof(args[4]);
            else if(args[4].back() == 'u') value = stof(args[4]) / 1000000;
            else if(args[4].back() == 'n') value = stof(args[4]) / 1000000000;
            else if(args[4].find('e') != string::npos)
            {
                value = stof(args[4].substr(0,args[4].find('e'))) *
                powf(10, stof(args[4].substr(args[4].find('e') + 1)));
            }
            else return true;
            Capacitor::addCapacitor(args[1].substr(1), args[2], args[3], value);
            return true;
        }
        if(args[0] == "add" && args[1][0] == 'L')
        {
            float value;
            if(isdigit(args[4][0])) value = stof(args[4]);
            else if(args[4].back() == 'u') value = stof(args[4]) / 1000000;
            else if(args[4].back() == 'm') value = stof(args[4]) / 1000;
            else if(args[4].find('e') != string::npos)
            {
                value = stof(args[4].substr(0,args[4].find('e'))) *
                powf(10, stof(args[4].substr(args[4].find('e') + 1)));
            }
            else return true;
            Inductor::addInductor(args[1].substr(1), args[2], args[3], value);
            return true;
        }
        if(args[0] == "add" && args[1][0] == 'D')
        {
            Diode::addDiode(args[1].substr(1), args[2], args[3], args[4][0]);
            return true;
        }
    }

    throw SyntaxException();
    return true;
}

