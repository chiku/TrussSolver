CXX ?= g++
CC  ?= gcc

CCFLAGS += -O2 -Wall
CXXFLAGS += -O2 -Wall

SOURCE_INCLUDE_PATHS += -Ivendor/matrix
TEST_INCLUDE_PATHS += -Isrc -Ivendor/matrix -Ivendor/qunit

.PHONY: all
all: main test

main: src/main.cpp src/truss.cpp
	${CXX} -o $@ $< ${SOURCE_INCLUDE_PATHS} ${CXXFLAGS} ${LDFLAGS}
	# ${CXX} -o $@ $^ ${SOURCE_INCLUDE_PATHS} ${CXXFLAGS} ${LDFLAGS}

test: test_runner
	./test_runner

test_runner: tests/test_suite.cpp tests/truss_one.cpp tests/truss_two.cpp tests/truss_three.cpp src/truss.cpp
	${CXX} -o $@ $< tests/truss_one.cpp tests/truss_two.cpp tests/truss_three.cpp ${TEST_INCLUDE_PATHS} ${CXXFLAGS} ${LDFLAGS}
	# ${CXX} -o $@ $^ ${SOURCE_INCLUDE_PATHS} ${CXXFLAGS} ${LDFLAGS}

.PHONE: clean
clean:
	rm -rf main *.o
