CXX = g++
CXXFLAGS = -std=c++11

SRC_DIR = src
OUTPUT_DIR = output

EXE = project2.out

.PHONY: all clean run tasks

all: $(EXE)

$(EXE): $(wildcard $(SRC_DIR)/*.cpp)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OUTPUT_DIR)/*

run: $(EXE)
	./$(EXE)

tasks: $(EXE)
	# Task 11: Multiply circles.tga with layer1.tga
	./$(EXE) $(OUTPUT_DIR)/output11.tga $(SRC_DIR)/circles.tga multiply $(SRC_DIR)/layer1.tga

	# Task 12: Flip layer1.tga
	./$(EXE) $(OUTPUT_DIR)/output12.tga flip $(SRC_DIR)/layer1.tga

	# Task 13: Subtract layer2.tga from layer1.tga
	./$(EXE) $(OUTPUT_DIR)/output13.tga subtract $(SRC_DIR)/layer1.tga $(SRC_DIR)/layer2.tga
