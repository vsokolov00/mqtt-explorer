
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -fPIC -lpaho-mqttpp3 -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs -pthread  -lpthread
LIB_DIR = ../mqtt_paho/libs/
EXE = client
EXAMPLE_EXE = example_client
OBJ = client.o listener.o callback.o
ALL_OBJ = $(OBJ) main.o
STATIC_LIB = libclient.a
DYNAMIC_LIB = libclient.so
LIBS = $(STATIC_LIB) $(DYNAMIC_LIB)
HEADER_DIR = header
HEADER = client.h
HEADER_FILES = listener.h callback.h client.h

.PHONY: all libs clean static_lib dynamic_lib header clean_header

all: $(EXE)

$(EXE): $(ALL_OBJ)
	$(CC) $(ALL_OBJ) $(CFLAGS) -L$(LIB_DIR) $(LDFLAGS) -o $(EXE)

%.o: %.cpp %.h
	$(CC) $< $(CFLAGS) -fPIC -c -o $@

libs: $(LIBS)

static_lib: $(STATIC_LIB)

dynamic_lib: $(DYNAMIC_LIB)

libclient.a: $(OBJ)
	ar rcs libclient.a $(OBJ)

libclient.so: $(OBJ)
	$(CC) $(OBJ) -shared -o libclient.so

header:
	mkdir $(HEADER_DIR)
	cat header_includes.txt > $(HEADER_DIR)/$(HEADER)
	tail -q -n +6 $(HEADER_FILES) >> $(HEADER_DIR)/$(HEADER)

clean_header:
	@rm -r $(HEADER_DIR)

clean:
	@rm -r $(ALL_OBJ) $(EXE) $(LIBS) $(HEADER_DIR)
