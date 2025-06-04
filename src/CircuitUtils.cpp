#include "../include/Exceptions.h"
#include "../include/Node.h"
#include "../include/Element.h"
#include "../include/Resistor.h"
#include "../include/Capacitor.h"
#include "../include/Inductor.h"
#include "../include/Diode.h"
#include "../include/Schematic.h"
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
    {cout << "Node does not exist" << endl; return;}

    gnd->setGround(false);
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

    if(args.size() == 1)
    {
        if(args[0] == ".nodes") Node::printAll();
        else if(args[0] == ".list") Element::printAll();
    }

    else if(args.size() == 2)
    {
        if(args[0] == "delete" && args[1][0] == 'R')
        {
            Resistor::deleteResistor(args[1].substr(1));
        }
        else if(args[0] == "delete" && args[1][0] == 'C')
        {
            Capacitor::deleteCapacitor(args[1].substr(1));
        }
        else if(args[0] == "delete" && args[1][0] == 'L')
        {
            Inductor::deleteInductor(args[1].substr(1));
        }
        else if(args[0] == ".list")
        {
            cout << args[1] << "s: " << endl;
            for(auto element: Element::elements)
            {
                if(element->getType() == args[1])
                {
                    cout << element->getName() << endl;
                }
            }
        }
    }

    else if(args.size() == 3)
    {
        if(args[0] == "add" && args[1] == "GND")
        {setGround(args[2]);}

        else if(args[0] == "delete" && args[1] == "GND")
        {deleteGround(args[2]);}
    }

    else if(args.size() == 4)
    {
        if(args[0] == ".rename" && args[1] == "node")
        {
            Node *node = Node::findNode(args[2]);
            if(node == nullptr)
            {
                cout << "ERROR: Node " << args[2] << "  does not exist in the circuit" << endl;
                return;
            }

            if(Node::findNode(args[3]) != nullptr)
            {
                cout << "ERROR: Node name " << args[3] << " already exists" << endl;
                return;
            }

            node->rename(args[3]);

            cout << "SUCCESS: Node renamed from " << args[2] << " to " << args[3] << endl;
        }
    }

    else if(args.size() == 5)
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
            else return;
            Resistor::addResistor(args[1].substr(1), args[2], args[3], value);
        }
        else if(args[0] == "add" && args[1][0] == 'C')
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
            else return;
            Capacitor::addCapacitor(args[1].substr(1), args[2], args[3], value);
        }
        else if(args[0] == "add" && args[1][0] == 'L')
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
            else return;
            Inductor::addInductor(args[1].substr(1), args[2], args[3], value);
        }
        else if(args[0] == "add" && args[1][0] == 'D')
        {
            Diode::addDiode(args[1].substr(1), args[2], args[3], args[4][0]);
        }
    }

    else if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(TRAN)(\\s+)(.+?)(\\s+)(V\\(n\\d{3}\\))(\\s*)")))
    {

    }

    else if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(DC)(\\s+)(.+?)(\\s+)(V\\(n\\d{3}\\))(\\s*)")))
    {

    }

    else if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(TRAN)(\\s+)(.+?)(\\s+)(I\\([RCD]\\S+\\))(\\s*)")))
    {

    }

    else if(regex_match(input, match, regex("(\\s*)(\\.print)(\\s+)(DC)(\\s+)(.+?)(\\s+)(I\\([RCD]\\S+\\))(\\s*)")))
    {

    }

    //multiple variables

    else if(regex_match(input, match, regex("(\\s*)(-show)(\\s+)(existing)(\\s+)(schematics)(\\s*)")))
    {
        Schematic::showAll();
    }

    else if(regex_match(input, match, regex("(\\s*)(NewFile)(\\s+)((\\S+\\.txt)(\\s*)")))
    {
        //auto address;
        string address;
        string name;
        Schematic* s = new Schematic(name, address);
    }

    else
    {cout << "Error: Syntax error" << endl;}
}
