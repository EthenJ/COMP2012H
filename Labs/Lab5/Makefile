OUT := Lab5
SRCS := Main.cpp Planet.cpp Simulation.cpp
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude

ifeq (Windows_NT, $(OS))
RM := del
else
RM := rm -f
endif

.PHONY: all
all: $(OUT)


$(OUT): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(OUT) $(OBJS)
