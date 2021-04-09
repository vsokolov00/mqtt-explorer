
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
LIBS = -fPIC -lpaho-mqttpp3 -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs
LIB_DIR = mqtt_paho/libs/
CLIENT_EXE = client
EXAMPLE_CLIENT_EXE = example_client
OBJ = main.o client.o clientAPI.o

all: $(CLIENT_EXE)

$(CLIENT_EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -L$(LIB_DIR) $(LIBS) -o $(CLIENT_EXE)

%.o: %.cpp %.h
	$(CC) $< $(CFLAGS) -fPIC -c -o $@

#client: client.cpp client.h
#	$(CC) client.cpp $(CFLAGS) -L$(LIB_DIR) $(LIBS) -o $(CLIENT_EXE)

example: example_client.cpp client.h
	$(CC) example_client.cpp $(CFLAGS) -L$(LIB_DIR) $(LIBS) -o $(EXAMPLE_CLIENT_EXE)

clean:
	@rm $(OBJ) client example_client
