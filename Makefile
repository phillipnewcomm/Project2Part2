build:
	g++ -std=c++11 -o project2.out src/*.cpp

clean:
	rm -f output/*

run:
	./project2.out

tasks: 
	output/output1.tga multiply src/circles.tga src/layer1.tga
	output/output2.tga flip src/layer1.tga
	output/output3.tga subtract src/layer1.tga src/layer2.tga
