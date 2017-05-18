CLASSDIR = 
INCLUDE = 
LIBS = #-lpthread -Wl,--no-as-needed

CC=g++
CFLAGS= -Wall -g -std=c++11 -pthread #-fmax-errors=0
LFLAGS= -Wall -g -std=c++11 -pthread
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= rlog_test

all: $(SOURCES) $(EXECUTABLE)


$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDE)-c $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $(OBJECTS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


.PHONY: clean
clean:
	rm -f $(EXECUTABLE) *.o

