#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <bits/stdc++.h>
using namespace std;

class CRangeException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Capacitance cannot be zero or negative";
    }
};

class CDuplicateNameException : public exception {
private:
    string name; 
    mutable string message; 
public:
    explicit CDuplicateNameException(const string& name) : name(name) {}
    
    const char* what() const noexcept override {
        message = "Error: Capacitor " + name + " already exists in the circuit";
        return message.c_str();
    }
};

class C404Exception : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Cannot delete capacitor; component not found";
    }
};

class NodeNotExistException : public exception {
public:
    const char* what() const noexcept override {
        return "Node does not exist";
    }
};

class NodeNotExistNameException : public exception {
private:
    string name; 
    mutable string message; 
public:
    explicit NodeNotExistNameException(const string& name) : name(name) {}
    
    const char* what() const noexcept override {
        message = "ERROR: Node " + name + " does not exist in the circuit";
        return message.c_str();
    }
};

class NodeAlreadyExistNameException : public exception {
private:
    string name; 
    mutable string message; 
public:
    explicit NodeAlreadyExistNameException(const string& name) : name(name) {}
    
    const char* what() const noexcept override {
        message = "ERROR: Node " + name + " already exists";
        return message.c_str();
    }
};

class SyntaxException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Syntax error";
    }
};

class DiodeModel404Exception : public exception {
private:
    string name; 
    mutable string message; 
public:
    explicit DiodeModel404Exception(const string& name) : name(name) {}
    
    const char* what() const noexcept override {
        message = "Error: Model " + name + " not found in library";
        return message.c_str();
    }
};

class DiodeAlreadyExistNameException : public exception {
private:
    string name; 
    mutable string message; 
public:
    explicit DiodeAlreadyExistNameException(const string& name) : name(name) {}
    
    const char* what() const noexcept override {
        message = "ERROR: diode " + name + " already exists in the circuit";
        return message.c_str();
    }
};

class D404Exception : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Cannot delete diode; component not found";
    }
};

class LRangeException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Inductance cannot be zero or negative";
    }
};

class LDuplicateNameException : public exception {
private:
    string name; 
    mutable string message; 
public:
    explicit LDuplicateNameException(const string& name) : name(name) {}
    
    const char* what() const noexcept override {
        message = "Error: Inductor " + name + " already exists in the circuit";
        return message.c_str();
    }
};

class L404Exception : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Cannot delete inductor; component not found";
    }
};

class RRangeException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Resistance cannot be zero or negative";
    }
};

class RDuplicateNameException : public exception {
private:
    string name; 
    mutable string message; 
public:
    explicit RDuplicateNameException(const string& name) : name(name) {}
    
    const char* what() const noexcept override {
        message = "Error: Resistor " + name + " already exists in the circuit";
        return message.c_str();
    }
};

class R404Exception : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Cannot delete resistor; component not found";
    }
};

class InvalidInputException : public exception {
public:
    const char* what() const noexcept override {
        return "-Error : Inappropriate input";
    }
};

//class Component404Exception : public exception {
class ComponentNotExistException : public exception {
private:
    string name; 
    mutable string message; 
public:
    explicit ComponentNotExistException(const string& name) : name(name) {}
    
    const char* what() const noexcept override {
        message = "ERROR: Component " + name + " does not exist in the circuit";
        return message.c_str();
    }
};


#endif