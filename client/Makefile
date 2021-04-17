
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -MMD
LDFLAGS = -fPIC -lpaho-mqttpp3 -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs -pthread  -lpthread
LIB_DIR = ../mqtt_paho/libs/
EXE = client
BUILD_DIR = build
LIBS_DIR = libs
SRC = $(wildcard *.cpp)
ALL_OBJ = ${SRC:.cpp=.o}
OBJ = $(filter-out main.o, $(ALL_OBJ))
DEPS = ${ALL_OBJ:.o=.d}
DIR_OBJ = $(addprefix $(BUILD_DIR)/, $(OBJ))
DIR_ALL_OBJ = $(addprefix $(BUILD_DIR)/, $(ALL_OBJ))
DIR_DEPS = $(addprefix $(BUILD_DIR)/, $(DEPS))
STATIC_LIB = libclient.a
DYNAMIC_LIB = libclient.so
LIBS = $(STATIC_LIB) $(DYNAMIC_LIB)
HEADER_DIR = header
HEADER = client.h
HEADER_FILES = listener.h callback.h client.h

.PHONY: all libs clean static_lib dynamic_lib header clean_header

all: $(EXE)

$(EXE): $(DIR_ALL_OBJ)
	$(CC) $(DIR_ALL_OBJ) $(CFLAGS) -L$(LIB_DIR) $(LDFLAGS) -o $(EXE)

$(BUILD_DIR)/%.o: %.cpp %.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $< $(CFLAGS) -fPIC -c -o $@

libs: $(LIBS)

static_lib: $(STATIC_LIB)

dynamic_lib: $(DYNAMIC_LIB)

libclient.a: $(DIR_OBJ)
	@mkdir -p $(LIBS_DIR)
	ar rcs $(LIBS_DIR)/libclient.a $(DIR_OBJ)

libclient.so: $(DIR_OBJ)
	@mkdir -p $(LIBS_DIR)
	$(CC) $(DIR_OBJ) -shared -o $(LIBS_DIR)/libclient.so

header:
	@mkdir -p $(HEADER_DIR)
	cat header_includes.txt > $(HEADER_DIR)/$(HEADER)
	tail -q -n +6 $(HEADER_FILES) >> $(HEADER_DIR)/$(HEADER)

clean_header:
	@rm -r $(HEADER_DIR)

clean_obj:
	@rm -r $(BUILD_DIR)

clean:
	@rm -r $(EXE) $(HEADER_DIR) $(BUILD_DIR) $(LIBS_DIR)
