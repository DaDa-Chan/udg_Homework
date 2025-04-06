CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g -O2

LDFLAGS = 

TARGETS = pdadd pdlist pdshow pdremove

SHARED_SRC = diary.cpp

SHARED_OBJ = $(SHARED_SRC:.cpp=.o)

HDR = diary.h

.PHONY: all
all: $(TARGETS)

pdadd: pdadd.o $(SHARED_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Built pdadd"


pdlist: pdlist.o $(SHARED_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Built pdlist"


pdshow: pdshow.o $(SHARED_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Built pdshow"


pdremove: pdremove.o $(SHARED_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Built pdremove"

pdadd.o pdlist.o pdshow.o pdremove.o $(SHARED_OBJ): $(HDR)

.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -f $(TARGETS) *.o $(DIARY_FILENAME) core.* *~
	@echo "Done."