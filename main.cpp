#include <bits/stdc++.h>

using namespace std;

class Node
{
    private:
    string name;
    bool isGround = false;

    public:
    Node(string name)
    {
        this->name = name;
    }

    string getName() {return name;}
    void setGround(bool mode) {isGround = mode;}
    void rename(string name) {this->name = name;}

    static vector<Node*> nodes;
    static Node* getNode(string node)
    {
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->getName() == node)
            return nodes[i];
        }

        Node *newnode = new Node(node);
        nodes.push_back(newnode);

        return newnode;
    }

    static Node* findNode(string node)
    {
        for(int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i]->getName() == node)
            return nodes[i];
        }
        return nullptr;
    }

    static void printAll()
    {
        cout << "Available nodes:" << endl;
        for(int i = 0; i < nodes.size(); i++)
        {
            cout << nodes[i]->getName();
            if(i != nodes.size() - 1) cout << ", ";
        }
        cout << endl;
    }
};

vector<Node*> Node::nodes;

class Element
{
    protected:
    string name;
    Node *n1, *n2;
    float value;
    string type;

    public:
    Element(string name, string node1, string node2, float value)
    {
        this->name = name;
        n1 = Node::getNode(node1);
        n2 = Node::getNode(node2);
        this->value = value;
    }

    string getName() {return name;}
    pair<Node*, Node*> getNodes() {return {n1, n2};}
    float getValue() {return value;}
    string getType() {return type;}

    static vector<Element*> elements;

    static void printAll()
    {
        cout << "All Elements:" << endl;
        for(auto e: elements)
        {
            cout << e->getName() << endl;
        }
    }
};

vector<Element*> Element::elements;

class Resistor: public Element
{
    public:
    Resistor(string name, string node1, string node2, float value):
    Element(name, node1, node2, value) {this->type = "resistor";}

    static void addResistor(string name, string node1, string node2, float value)
    {
        if(value <= 0)
        {cout << "Error: Resistance cannot be zero or negative" << endl; return;}

        for(auto e: elements)
        {
            if(e->getName() == name)
            {cout << "Error: Resistor " << name << " already exists in the circuit" << endl; return;}
        }

        elements.push_back((Element*) new Resistor(name, node1, node2, value));
    }

    static void deleteResistor(string name)
    {
        for(int i = 0; i < elements.size(); i++)
        {
            if(elements[i]->getName() == name)
            {delete elements[i]; elements.erase(elements.begin() + i); return;}
        }

        cout << "Cannot delete resistor; component not found" << endl;
    }

    static void printAll()
    {
        cout << "Resistors:" << endl;
        for(auto e: elements)
        {
            if(e->getType() == "resistor") cout << e->getName() << endl;
        }
    }
};

class Capacitor: public Element
{
    public:
    Capacitor(string name, string node1, string node2, float value):
    Element(name, node1, node2, value) {this->type = "capacitor";}

    static void addCapacitor(string name, string node1, string node2, float value)
    {
        if(value == 0)
        {cout << "Error: Capacitance cannot be zero or negative" << endl; return;}

        for(auto e: elements)
        {
            if(e->getName() == name)
            {cout << "Error: Capacitor " << name << " already exists in the circuit" << endl; return;}
        }

        elements.push_back((Element*) new Capacitor(name, node1, node2, value));
    }

    static void deleteCapacitor(string name)
    {
        for(int i = 0; i < elements.size(); i++)
        {
            if(elements[i]->getName() == name)
            {delete elements[i]; elements.erase(elements.begin() + i); return;}
        }

        cout << "Error: Cannot delete capacitor; component not found" << endl;
    }

    static void printAll()
    {
        cout << "Capacitors:" << endl;
        for(auto e: elements)
        {
            if(e->getType() == "capacitor") cout << e->getName() << endl;
        }
    }
};

class Inductor: public Element
{
    public:
    Inductor(string name, string node1, string node2, float value):
    Element(name, node1, node2, value) {this->type = "inductor";}

    static void addInductor(string name, string node1, string node2, float value)
    {
        if(value == 0)
        {cout << "Error: Inductance cannot be zero or negative" << endl; return;}

        for(auto e: elements)
        {
            if(e->getName() == name)
            {cout << "Error: inductor " << name << " already exists in the circuit" << endl; return;}
        }

        elements.push_back(new Inductor(name, node1, node2, value));
    }

    static void deleteInductor(string name)
    {
        for(int i = 0; i < elements.size(); i++)
        {
            if(elements[i]->getName() == name)
            {delete elements[i]; elements.erase(elements.begin() + i); return;}
        }

        cout << "Error: Cannot delete inductor; component not found" << endl;
    }

    static void printAll()
    {
        cout << "Inductors:" << endl;
        for(auto e: elements)
        {
            if(e->getType() == "inductor") cout << e->getName() << endl;
        }
    }
};

class Diode: public Element
{
    char model;

    public:
    Diode(string name, string node1, string node2, char model):
    Element(name, node1, node2, 0)
    {
        this->type = "diode"; 
        this->model = model;

        if(model == 'Z') this->value = 0.7;
        else this->value = 0;
    }

    static void addDiode(string name, string node1, string node2, char model)
    {
        if(model != 'Z' && model != 'D')
        {cout << "Error: Model " << model << " not found in library" << endl; return;}

        for(auto e: elements)
        {
            if(e->getName() == name)
            {cout << "Error: diode " << name << " already exists in the circuit" << endl; return;}
        }

        elements.push_back(new Diode(name, node1, node2, model));
    }

    static void deleteDiode(string name)
    {
        for(int i = 0; i < elements.size(); i++)
        {
            if(elements[i]->getName() == name)
            {delete elements[i]; elements.erase(elements.begin() + i); return;}
        }

        cout << "Error: Cannot delete diode; component not found" << endl;
    }

    static void printAll()
    {
        cout << "Diodes:" << endl;
        for(auto e: elements)
        {
            if(e->getType() == "diode") cout << e->getName() << endl;
        }
    }
};

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

void parseCommands(vector<string> args)
{
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

    else
    {cout << "Error: Syntax error" << endl;}
}

int main()
{

}
