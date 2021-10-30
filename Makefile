OUT := a
SRCS := my_solution_0.cpp
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

CXX := g++10
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude -fsanitize=address,leak,undefined -g
LDFLAGS := -fsanitize=address,leak,undefined -g

ifeq (Windows_NT, $(OS))
RM := del
else
RM := rm -f
endif

.PHONY: all
all: $(OUT)


$(OUT): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(OUT) $(OBJS)
