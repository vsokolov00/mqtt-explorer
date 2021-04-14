
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
LIBS = -fPIC -lpaho-mqttpp3 -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs
LIB_DIR = ../mqtt_paho/libs/
EXE = simulator
OBJ = main.o thermometer.o parser.o runner.o
JSON = jsoncpp.o
LDFLAGS= -pthread  -lpthread

all: $(EXE)

$(EXE): $(OBJ) $(JSON)
	$(CC) $(OBJ) $(JSON) $(CFLAGS) $(LDFLAGS) -L$(LIB_DIR) $(LIBS) -o $(EXE)

%.o: %.cpp %.h
	$(CC) $< $(CFLAGS) -fPIC -c -o $@

$(JSON): jsoncpp.cpp json/json-forwards.h json/json.h
	$(CC) jsoncpp.cpp $(CFLAGS) -c -o $(JSON)

clean:
	@rm $(OBJ) $(JSON) simulator
