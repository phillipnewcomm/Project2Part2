build:
	g++ -std=c++11 -o project2.out src/*.cpp

clean:
	rm -f output/*

run:
	./project2.out

tasks:
	output/part11.tga multiply input/circles.tga input/layer1.tga ; \
	output/part12.tga flip input/layer1.tga ; \
	output/part13.tga subtract input/layer1.tga input/layer2.tga
