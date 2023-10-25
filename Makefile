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
	./$(EXE) multiply $(SRC_DIR)/circles.tga $(SRC_DIR)/layer1.tga $(OUTPUT_DIR)/output1.tga
	./$(EXE) rotate 180 $(SRC_DIR)/layer1.tga $(OUTPUT_DIR)/output2.tga
	./$(EXE) subtract $(SRC_DIR)/layer1.tga $(SRC_DIR)/layer2.tga $(OUTPUT_DIR)/output3.tga
