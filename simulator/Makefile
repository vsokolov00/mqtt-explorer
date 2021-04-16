
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -MMD
LDFLAGS = -pthread -lpthread -L. -lclient
LIBS = -fPIC -lpaho-mqttpp3 -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs
LIB_DIR = ../mqtt_paho/libs/
BUILD_DIR = build
EXE = simulator
SRC = $(wildcard *.cpp)
OBJ = ${SRC:.cpp=.o}
DEPS = ${OBJ:.o=.d}
DIR_OBJ = $(addprefix $(BUILD_DIR)/, $(OBJ))
DIR_DEPS = $(addprefix $(BUILD_DIR)/, $(DEPS))

all: $(EXE)

-include $(DIR_DEPS)

$(EXE): $(DIR_OBJ) 
	$(CC) $(DIR_OBJ) $(CFLAGS) $(LDFLAGS) -L$(LIB_DIR) $(LIBS) -o $(EXE)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $< $(CFLAGS) -fPIC -c -o $@

clean:
	@rm -r $(EXE) $(BUILD_DIR)
