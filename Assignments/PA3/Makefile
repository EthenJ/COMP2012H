OUT := simplecity
ZIP_OUT := pa3.zip

ifeq (Windows_NT, $(OS))

RM := rm
SRCS := main_cli.cpp GameEngine.cpp City.cpp buildings\Building.cpp buildings\Health.cpp buildings\Revenue.cpp buildings\Residential.cpp buildings\Clinic.cpp buildings\Hospital.cpp buildings\SilverMine.cpp buildings\GoldMine.cpp buildings\House.cpp buildings\Apartment.cpp
SUBMISSION := City.cpp buildings\Building.cpp buildings\Health.cpp buildings\Revenue.cpp buildings\Residential.cpp buildings\Clinic.cpp buildings\Hospital.cpp buildings\SilverMine.cpp buildings\GoldMine.cpp buildings\House.cpp buildings\Apartment.cpp buildings\Health.h buildings\Revenue.h buildings\Residential.h buildings\Clinic.h buildings\Hospital.h buildings\SilverMine.h buildings\GoldMine.h buildings\House.h buildings\Apartment.h
ZIP := zip.exe
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -Iinclude
LDFLAGS :=

OBJS := $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: all
all: $(OUT)


$(OUT): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(ZIP_OUT): $(SUBMISSION)
	# $(RM) $(ZIP_OUT)
	$(ZIP) $@ $^

.PHONY: clean
clean:
	$(RM) $(OUT) $(OBJS) $(ZIP_OUT)

else

OUT := simplecity
SRCS := main_cli.cpp GameEngine.cpp City.cpp buildings/Building.cpp buildings/Health.cpp buildings/Revenue.cpp buildings/Residential.cpp buildings/Clinic.cpp buildings/Hospital.cpp buildings/SilverMine.cpp buildings/GoldMine.cpp buildings/House.cpp buildings/Apartment.cpp
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -Iinclude -fsanitize=address,leak,undefined -g
LDFLAGS := -fsanitize=address,leak,undefined -g


RM := rm -f


.PHONY: all
all: $(OUT)


$(OUT): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(OUT) $(OBJS)

endif


