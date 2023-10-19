build:
	g++ -std=c++11 -o project2.out src/*.cpp

clean:
	rm -f output/*

run:
	./project2.out
