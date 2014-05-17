CXX ?= g++
CC  ?= gcc

CCFLAGS += -O2 -Wall
CXXFLAGS += -O2 -Wall

CXXFLAGS += -Iinclude

OBJDIR := build

all: compile

compile: $(OBJDIR)/main

test: $(OBJDIR)/test_runner
	./$(OBJDIR)/test_runner

$(OBJDIR)/%.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

$(OBJDIR)/%: $(OBJDIR)/%.o
	${CXX} ${CXXFLAGS} ${LDFLAGS} -c -o $@ $<

$(OBJDIR)/main: $(OBJDIR)/src/main.o $(OBJDIR)/src/truss.o
	${CXX} ${CXXFLAGS} ${LDFLAGS} -o $@ $^

$(OBJDIR)/test_runner: $(OBJDIR)/tests/test_suite.o $(OBJDIR)/src/truss.o $(OBJDIR)/tests/truss_one_test.o $(OBJDIR)/tests/truss_two_test.o $(OBJDIR)/tests/truss_three_test.o
	${CXX} ${CXXFLAGS} ${LDFLAGS} -o $@ $^

$(OBJDIR)/src/main.o: src/main.cpp include/truss.h
$(OBJDIR)/src/truss.o: src/truss.cpp include/truss.h
$(OBJDIR)/tests/test_suite.o: tests/test_suite.cpp tests/truss_test.h
$(OBJDIR)/tests/truss_one_test.o: tests/truss_one_test.cpp tests/truss_test.h
$(OBJDIR)/tests/truss_two_test.o: tests/truss_two_test.cpp tests/truss_test.h
$(OBJDIR)/tests/truss_three_test.o: tests/truss_three_test.cpp tests/truss_test.h

clean:
	rm -rf $(OBJDIR)/*/*.o $(OBJDIR)/main $(OBJDIR)/test_runner

.PHONY: all compile test clean
