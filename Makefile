# Written by     : Chirantan Mitra

CC ?= gcc
CXX ?= g++

CFLAGS += -O2
CXXFLAGS += -O2

INCLUDES += -Iinclude -Ivendor

HEADER_FILES = $(shell find include -name *.h)
SOURCE_FILES = $(shell find src -name *.cpp)
TEST_FILES = $(shell find tests -name *.cpp)

SOURCE_OBJ_FILES = $(shell echo ${SOURCE_FILES} | sed 's/src/build/g' | sed 's/\.cpp/\.o/g')
TEST_OBJ_FILES = $(shell echo ${TEST_FILES} | sed 's/tests/build\/tests/g' | sed 's/\.cpp/\.o/g')

all: test compile demo
.PHONY: all

compile: build/truss_solver
.PHONY: compile

demo: compile
	./build/truss_solver
.PHONY: demo

test: build/tests/truss_test
	./build/tests/truss_test
.PHONY: test

clean:
	rm -rf build/
.PHONY: clean

build/truss_solver: $(SOURCE_FILES)
	mkdir -pv $(@D)
	$(CXX) $^ $(LDFLAGS) $(INCLUDES) -o $@

build/tests/truss_test: build/truss.o $(TEST_OBJ_FILES)
	@mkdir -pv $(@D)
	$(CXX) $^ $(LDFLAGS) -o $@

build/%.o: src/%.cpp $(HEADER_FILES)
	@mkdir -pv $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

build/tests/%.o: tests/%.cpp $(HEADER_FILES)
	@mkdir -pv $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
