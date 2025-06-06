CXX = g++
CXXFLAGS = -Iinclude -std=c++17 
SOURCES = main.cpp src/Node.cpp src/Element.cpp src/Resistor.cpp src/Capacitor.cpp src/Inductor.cpp src/Diode.cpp src/Schematic.cpp src/CircuitUtils.cpp src/SchematicManager.cpp src/Sinusoidal.cpp src/Source.cpp src/VoltageSource.cpp src/CurrentSource.cpp
EXECUTABLE = program

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

run: all
	./$(EXECUTABLE)