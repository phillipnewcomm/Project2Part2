build:
    g++ -std=c++11 -o project2.out src/*.cpp

clean:
    rm -f output/*

run:
    ./project2.out

tasks: 
    ./project2.out output/part11.tga multiply input/circles.tga input/layer1.tga
    ./project2.out output/part12.tga flip input/layer1.tga
    ./project2.out output/part13.tga input/layer1.tga subtract input/layer2.tga
