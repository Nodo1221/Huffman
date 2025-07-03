CXX = g++
CXXFLAGS_DEBUG = -std=gnu++17 -Wall -Wpedantic -Wextra -g
CXXFLAGS_RELEASE = -std=gnu++17 -Wall -O2

CXXFLAGS = $(CXXFLAGS_DEBUG)

.PHONY: debug release clean

all: debug

debug: main
release: CXXFLAGS = $(CXXFLAGS_RELEASE)
release: main

main: main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f main main.o

# debug:
# 	$(CXX) $(CXXFLAGS_DEBUG) -o main main.cpp

# release:
# 	$(CXX) $(CXXFLAGS_RELEASE) -o main main.cpp

# clean:
# 	rm main
