#include "../include/InputHandling.h"

#include <bits/stdc++.h>
using namespace std;

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

    if(regex_match(input, match, regex("(\\s*)(add)(\\s+)(VoltageSource)(\\S+)(\\s+)(\\S+)(\\s+)(\\S+)(\\s+)(\\-*\\d+\\.*\\d*)(\\s*)")))
    {
        string name = match[5].str();
        string node1 = match[7].str();
        string node2 = match[9].str();
        float value = stof(match[11].str());
        VoltageSource::addVoltageSource(name, node1, node2, value, 0, 1);
        return true;
    }

    if(regex_match(input, match, regex("(\\s*)(add)(\\s+)(CurrentSource)(\\S+)(\\s+)(\\S+)(\\s+)(\\S+)(\\s+)(\\-*\\d+\\.*\\d*)(\\s*)")))
    {
        string name = match[5].str();
        string node1 = match[7].str();
        string node2 = match[9].str();        
        float value = stof(match[11].str());
        CurrentSource::addCurrentSource(name, node1,  node2, value, 0, 1);
        return true;
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

    if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(TRAN)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)((((I\\()([RCL].+?)(\\))(\\s*?))|((V\\()(.+?)(\\)(\\s*)))){2,})(\\s*)")))
    {
        float tstep = stof(match[6].str());
        float tstop = stof(match[8].str());
        float tstart = stof(match[10].str());
        stringstream ss(match[12].str());
        string word;
        while (ss>>word){
            if (regex_match(word, match, regex("(I\\()([RCL].+?)(\\))"))){
                transCurrent(tstart, tstop, tstep, match[2].str());
            }
            if (regex_match(word, match, regex("(V\\()(.+?)(\\))"))){
                transVoltage(tstart, tstop, tstep, match[2].str());
            }
        }
        return true;
    }

    if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(TRAN)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(V\\()(.+?)(\\))(\\s*)")))
    {
        float tstep = stof(match[6].str());
        float tstop = stof(match[8].str());
        float tstart = stof(match[10].str());
        string node = match[13].str();
        transVoltage(tstart, tstop, tstep, node);
        return true;
    }

    if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(TRAN)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(I\\()([RCL].+?)(\\))(\\s*)")))
    {
        float tstep = stof(match[6].str());
        float tstop = stof(match[8].str());
        float tstart = stof(match[10].str());
        string element = match[13].str();
        transCurrent(tstart, tstop, tstep, element);
        return true;
    }

    if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(DC)(\\s+)(\\S+)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)((((I\\()([RCL].+?)(\\))(\\s*?))|((V\\()(.+?)(\\)(\\s*)))){2,})(\\s*)")))
    {
        string source = match[6].str();
        float start = stof(match[8].str());
        float end = stof(match[10].str());
        float increment = stof(match[12].str());
        stringstream ss(match[14].str());
        string word;
        while (ss>>word){
            if (regex_match(word, match, regex("(I\\()([RCL].+?)(\\))"))){
                DCCurrent(source, start, end, increment, match[2].str());
            }
            if (regex_match(word, match, regex("(V\\()(.+?)(\\))"))){
                DCVoltage(source, start, end, increment, match[2].str());
            }
        }
        return true;
    }
   
    if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(DC)(\\s+)(\\S+)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(V\\()(.+?)(\\))(\\s*)")))
    {
        string source = match[6].str();
        float start = stof(match[8].str());
        float end = stof(match[10].str());
        float increment = stof(match[12].str());
        string node = match[15].str();
        DCVoltage(source, start, end, increment, node);
        return true;
    }

    if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(DC)(\\s+)(\\S+)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(\\-*\\d+\\.*\\d*)(\\s+)(I\\()([RCL]\\S+?)(\\))(\\s*)")))
    {
        string source = match[6].str();
        float start = stof(match[8].str());
        float end = stof(match[10].str());
        float increment = stof(match[12].str());
        string element = match[15].str();
        DCCurrent(source, start, end, increment, element);
        return true;
    }

    // if(regex_match(input, match, regex("(\\s*)(-show)(\\s+)(existing)(\\s+)(schematics)(\\s*)")))
    // {
    //     Schematic::showAll();
    //     return true;
    // }

    // if(regex_match(input, match, regex("(\\s*)(NewFile)(\\s+)(\\S+\\.txt)(\\s*)")))
    // {
    //     string address;
    //     string name;
    //     Schematic* s = new Schematic(name, address);
    //     return true;
    // }

    if(args.size() == 1)
    {
        if(args[0] == ".nodes") {Node::printAll(); return true;}
        else if(args[0] == ".list") {Element::printAll(); return true;}
    }

    if(args.size() == 2)
    {
        if(args[0] == "delete" && args[1][0] == 'R')
        {
            //Resistor::deleteResistor(args[1].substr(1));
            Resistor::deleteResistor(args[1]);
            return true;
        }
        if(args[0] == "delete" && args[1][0] == 'C')
        {
            //Capacitor::deleteCapacitor(args[1].substr(1));
            Capacitor::deleteCapacitor(args[1]);
            return true;
        }
        if(args[0] == "delete" && args[1][0] == 'L')
        {
            //Inductor::deleteInductor(args[1].substr(1));
            Inductor::deleteInductor(args[1]);
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
            //Resistor::addResistor(args[1].substr(1), args[2], args[3], value);
            Resistor::addResistor(args[1], args[2], args[3], value);
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
            //Capacitor::addCapacitor(args[1].substr(1), args[2], args[3], value);
            Capacitor::addCapacitor(args[1], args[2], args[3], value);
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
            //Inductor::addInductor(args[1].substr(1), args[2], args[3], value);
            Inductor::addInductor(args[1], args[2], args[3], value);
            return true;
        }
        if(args[0] == "add" && args[1][0] == 'D')
        {
            //Diode::addDiode(args[1].substr(1), args[2], args[3], args[4][0]);
            Diode::addDiode(args[1], args[2], args[3], args[4][0]);
            return true;
        }
    }

    throw SyntaxException();
    return true;
}