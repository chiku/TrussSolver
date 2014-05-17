CXX ?= g++
CC  ?= gcc

CCFLAGS += -O2 -Wall
CXXFLAGS += -O2 -Wall

OBJDIR := build

all: compile

compile: $(OBJDIR)/main

test: $(OBJDIR)/test_runner
	./$(OBJDIR)/test_runner

$(OBJDIR)/main: $(OBJDIR)/src/main.o $(OBJDIR)/src/truss.o
	${CXX} -o $@ $^ ${CXXFLAGS} ${LDFLAGS}

$(OBJDIR)/test_runner: $(OBJDIR)/tests/test_suite.o $(OBJDIR)/src/truss.o $(OBJDIR)/tests/truss_one_test.o $(OBJDIR)/tests/truss_two_test.o $(OBJDIR)/tests/truss_three_test.o
	${CXX} -o $@ $^ ${CXXFLAGS} ${LDFLAGS}

$(OBJDIR)/src/main.o: src/main.cpp include/truss.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

$(OBJDIR)/src/truss.o: src/truss.cpp include/truss.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

$(OBJDIR)/tests/test_suite.o: tests/test_suite.cpp tests/truss_test.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

$(OBJDIR)/tests/truss_one_test.o: tests/truss_one_test.cpp tests/truss_test.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

$(OBJDIR)/tests/truss_two_test.o: tests/truss_two_test.cpp tests/truss_test.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

$(OBJDIR)/tests/truss_three_test.o: tests/truss_three_test.cpp tests/truss_test.h
	${CXX} -c -o $@ $< ${CXXFLAGS} ${LDFLAGS}

clean:
	rm -rf $(OBJDIR)/*.o $(OBJDIR)/*/*.o $(OBJDIR)/main $(OBJDIR)/test_runner

.PHONY: all compile test clean
