CXX ?= g++
CC  ?= gcc

CCFLAGS += -O2 -Wall
CXXFLAGS += -O2 -Wall

.PHONY: all
all: build/main build/test

build/main: build/main.o build/truss.o
	${CXX} -o $@ $^ ${CXXFLAGS} ${LDFLAGS}

build/test: build/test_runner
	./build/test_runner

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

.PHONE: clean
clean:
	rm -rf build/*.o build/main build/test_runner
