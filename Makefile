CC=g++
CFLAGS=-c -Wall -fpic -std=c++0x -Iinclude
LDFLAGS=-shared
SOURCES=src/XMLParser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=expat11

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf src/*.o expat11

tests:
	$(CC) $(CFLAGS) $< -o tests
