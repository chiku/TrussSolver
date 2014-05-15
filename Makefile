CXX ?= g++
CC  ?= gcc

CCFLAGS += -O2 -Wall
CXXFLAGS += -O2 -Wall

all: compile

compile: build/main

test: build/test_runner
	./build/test_runner

build/main: build/main.o build/truss.o
	${CXX} -o $@ $^ ${CXXFLAGS} ${LDFLAGS}

build/test_runner: build/test_suite.o build/truss.o build/truss_one_test.o build/truss_two_test.o build/truss_three_test.o
	${CXX} -o $@ $^ ${CXXFLAGS} ${LDFLAGS}

build/main.o: src/main.cpp include/truss.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

build/truss.o: src/truss.cpp include/truss.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

build/test_suite.o: tests/test_suite.cpp tests/truss_test.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

build/truss_one_test.o: tests/truss_one_test.cpp tests/truss_test.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

build/truss_two_test.o: tests/truss_two_test.cpp tests/truss_test.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

build/truss_three_test.o: tests/truss_three_test.cpp tests/truss_test.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

clean:
	rm -rf build/*.o build/main build/test_runner

.PHONY: all compile test clean
