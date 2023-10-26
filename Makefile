CXX = g++
CXXFLAGS = -std=c++11

SRC_DIR = src
OUTPUT_DIR = output

EXE = project2.out

.PHONY: all clean run tests

all: $(EXE)

$(EXE): $(wildcard $(SRC_DIR)/*.cpp)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OUTPUT_DIR)/*
	rm -f $(EXE)

run: $(EXE)
	./$(EXE)

tasks: $(EXE)
	./$(EXE) output/tracking_output.tga multiply $(SRC_DIR)/circles.tga $(SRC_DIR)/layer1.tga
	./$(EXE) output/flip_output.tga flip $(SRC_DIR)/layer1.tga
	./$(EXE) output/subtract_output.tga subtract $(SRC_DIR)/layer1.tga $(SRC_DIR)/layer2.tga

tests: all tasks
