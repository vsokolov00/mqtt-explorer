
#================================================================================================
# File:        Makefile
# Case:        VUT, FIT, ICP, project
# Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
# Date:        summer semester 2021
# Description: Makefile used for building a static client library used by other parts
#			   of the project.
#================================================================================================

CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -MMD
LDFLAGS = -fPIC -pthread  -lpthread
BUILD_DIR = ../build/client
LIBS_DIR = ../libs/client
SRC = $(wildcard *.cpp)
OBJ = ${SRC:.cpp=.o}
DEPS = ${ALL_OBJ:.o=.d}
DIR_OBJ = $(addprefix $(BUILD_DIR)/, $(OBJ))
DIR_DEPS = $(addprefix $(BUILD_DIR)/, $(DEPS))
STATIC_LIB = libclient.a
LIB = $(STATIC_LIB)

.PHONY: all clean static_lib dynamic_lib

all: $(LIB)

-include $(DIR_DEPS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $< $(CFLAGS) -fPIC -c -o $@

libclient.a: $(DIR_OBJ)
	@mkdir -p $(LIBS_DIR)
	ar rcs $(LIBS_DIR)/libclient.a $(DIR_OBJ)

clean:
	@rm -r $(LIBS_DIR) $(BUILD_DIR)
