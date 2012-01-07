CC=g++
CFLAGS=-c -Wall -std=c++0x -Iinclude
LDFLAGS=
SOURCES=src/XMLParser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=expat11

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o expat11

