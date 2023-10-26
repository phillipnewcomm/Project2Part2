build:
	g++ -std=c++11 -o project2.out src/*.cpp

clean:
	rm -f output/*

run:
	./project2.out

tasks: $(EXE)
   	./$(EXE) output/output11.tga src/circles.tga multiply src/layer1.tga
	./$(EXE) output/output12.tga flip src/layer1.tga
	./$(EXE) output/output13.tga subtract src/layer1.tga src/layer2.tga
