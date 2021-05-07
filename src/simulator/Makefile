
#================================================================================================
# File:        Makefile
# Case:        VUT, FIT, ICP, project
# Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
# Date:        summer semester 2021
# Description: Makefile used for building the simulator application.
#================================================================================================

CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -MMD
LDFLAGS = -pthread -lpthread -L. -lclient
MQTT_LIB = -lpaho-mqttpp3 -lpaho-mqtt3a
BUILD_DIR = ../build/simulator
EXE = ../bin/simulator
SRC = $(wildcard *.cpp)
OBJ = ${SRC:.cpp=.o}
DEPS = ${OBJ:.o=.d}
DIR_OBJ = $(addprefix $(BUILD_DIR)/, $(OBJ))
DIR_DEPS = $(addprefix $(BUILD_DIR)/, $(DEPS))
JSON_LIB = ../libs/json/libjson.a
CLIENT_LIB = ../libs/client/libclient.a
CLIENT = -L../libs/client -lclient
JSON = -L../libs/json -ljson
BIN_DIR = ../bin

.PHONY: all clean run

all: $(EXE)

-include $(DIR_DEPS)

$(EXE): $(DIR_OBJ) $(JSON_LIB) $(CLIENT_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(DIR_OBJ) $(CFLAGS) $(LDFLAGS) $(MQTT_LIB) $(JSON) $(CLIENT) -o $(EXE)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $< $(CFLAGS) -fPIC -c -o $@

$(JSON_LIB):
	cd ../json && make -j

$(CLIENT_LIB):
	cd ../client && make -j

clean:
	@rm -r $(EXE) $(BUILD_DIR)

run: $(EXE)
	../bin/simulator
