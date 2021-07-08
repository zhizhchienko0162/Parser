CC=g++
CFLAGS=-I./lib/include/ -I./inc -c
LDFLAGS=-lPcap++ -lPacket++ -lCommon++ -lpcap -lpthread -L./lib
SOURCES= src/main.cpp \
		 src/PTPHeader.cpp \
		 src/PTPSync.cpp
OBJECTS=out/main.o \
		out/PTPHeader.o \
		out/PTPSync.o
EXECUTABLE=parser

all: $(SOOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

out/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

install: $(EXECUTABLE)
	cp $(EXECUTABLE) /usr/local/bin

uninstall:
	rm /usr/local/bin/$(EXECUTABLE) || /bin/true

clean:
	rm -rf out/*.o $(EXECUTABLE) || /bin/true
