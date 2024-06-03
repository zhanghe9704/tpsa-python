CC = g++
NAME = tpsa
ifeq ($(OS),Windows_NT)
    detected_os := Windows
else
    detected_os := $(shell uname)
endif
ifeq ($(detected_os),Windows)
	VERSION = $(shell python -c "from distutils import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))")
	TARGET_LIB = $(NAME)$(VERSION)
	INCDIR = tpsa/include
	PYTHON_INC = $(shell python -m pybind11 --includes)
	PYTHONLIB = $(shell python -c "import sysconfig; print(sysconfig.get_path('stdlib'))")
	PYTHONLIB := $(subst Lib,libs,$(PYTHONLIB))
	CFLAGS = -O3 -Wall -shared -DMS_WIN64 -std=c++11 -fPIC $(PYTHON_INC) -I$(INCDIR) -L$(PYTHONLIB)
	MAJOR_VER = $(shell python -c "import sys; print(sys.version_info.major)")
	MINOR_VER += $(shell python -c "import sys; print(sys.version_info.minor)")
	LIBS = -lm -lstdc++ -lpython$(MAJOR_VER)$(MINOR_VER)
else
	VERSION = $(shell python3-config --extension-suffix)
	TARGET_LIB = $(NAME)$(VERSION)
	INCDIR = tpsa/include
	PYTHON_INC = $(shell python -m pybind11 --includes)
	CFLAGS = -O3 -Wall -shared -std=c++11 -fPIC $(PYTHON_INC) -I$(INCDIR)	
	LIBS = -lm -lstdc++ 
endif

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
