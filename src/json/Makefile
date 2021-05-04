
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
BUILD_DIR = ../build/json
OBJ = ../build/json/json.o
LIBS_DIR = ../libs/json
LIB = libjson.a

all: $(LIB)

$(OBJ): jsoncpp.cpp json/json.h json/json-forwards.h
	@mkdir -p $(BUILD_DIR)
	$(CC) jsoncpp.cpp $(CFLAGS) -fPIC -c -o $@

libjson.a: $(OBJ)
	@mkdir -p $(LIBS_DIR)
	ar rcs $(LIBS_DIR)/libjson.a $(OBJ)

clean:
	@rm -r $(OBJ) $(LIBS_DIR)
