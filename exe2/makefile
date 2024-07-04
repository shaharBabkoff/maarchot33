# Makefile for compiling and testing Kosaraju algorithm implementations

CXX = g++
CXXFLAGS = -std=c++17 -Wall
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = kosaraju_linkedList.c kosaraju_matrix.c kosaraju_stack.c
OBJECTS = $(SOURCES:.c=.o)

# Targets


stack: kosaraju_stack.o
	$(CXX) $(CXXFLAGS) $^ -o stack

link: kosaraju_linkedList.o
	$(CXX) $(CXXFLAGS) $^ -o link

matrix: kosaraju_matrix.o
	$(CXX) $(CXXFLAGS) $^ -o matrix

test_mat: test_matrix.o kosaraju_matrix.o
	$(CXX) $(CXXFLAGS) $^ -o test_mat

test_stack: test_stack.o kosaraju_stack.o
	$(CXX) $(CXXFLAGS) $^ -o test_stack

test_link: test_linkedList.o kosaraju_linkedList.o
	$(CXX) $(CXXFLAGS) $^ -o test_link

# Phony targets
.PHONY: tidy valgrind clean

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: test_mat test_stack test_link
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test_mat 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test_stack 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test_link 2>&1 | { egrep "lost| at " || true; }

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o matrix test_link test_mat test_stack link stack
