CC = g++
NAME = tpsa
VERSION = $(shell python3-config --extension-suffix)
TARGET_LIB = $(NAME)$(VERSION)

INCDIR = tpsa/include
PYTHON_INC = $(shell python3 -m pybind11 --includes)
CFLAGS = -O3 -Wall -shared -std=c++11 -fPIC $(PYTHON_INC) -I$(INCDIR)

LIBS = -lm

SRC = $(wildcard src/*.cc)
SRC += $(wildcard tpsa/src/*.cc)
OBJ = $(SRC:.cc=.o)
DEPS = $(wildcard $(INCDIR)/*.h)

#$(info $$SRC is [${SRC}])
#$(info $$OBJ is [${OBJ}])
#$(info $$CFLAGS is [${CFLAGS}])

.PHONE: all
all = $(TARGET_LIB)

$(TARGET_LIB): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ)
