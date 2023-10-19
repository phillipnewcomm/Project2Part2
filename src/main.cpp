#include "HelperMethods.h"
#include "Image.h"
#include <iostream>

int main() {
    // Task 1: Use the Multiply blending mode to combine layer1.tga (top layer) with pattern1.tga (bottom layer)
    Image layer1 = HelperMethods::readFile("input/layer1.tga");
    Image pattern1 = HelperMethods::readFile("input/pattern1.tga");
    Image result1 = HelperMethods::Multiply(layer1, pattern1);
    HelperMethods::writeFile("output/part1.tga", result1);

    // Task 2: Use the Subtract blending mode to combine layer2.tga (bottom layer) with car.tga (top layer)
    Image layer2 = HelperMethods::readFile("input/layer2.tga");
    Image car1 = HelperMethods::readFile("input/car.tga");
    Image result2 = HelperMethods::Subtract(layer2, car1);
    HelperMethods::writeFile("output/part2.tga", result2);

    // Task 3: Use the Multiply blending mode to combine layer1.tga with pattern2.tga
Image pattern2 = HelperMethods::readFile("input/pattern2.tga");
Image tempResult3 = HelperMethods::Multiply(layer1, pattern2);

// Load text.tga and combine it with the previous results using Screen blending mode
Image text = HelperMethods::readFile("input/text.tga");
Image result3 = HelperMethods::Screen(layer1, pattern2, text); // Combine pattern2 and text using Screen blending mode
HelperMethods::writeFile("output/part3.tga", result3);


    // Task 4: Multiply layer2.tga with circles.tga, and store it
    Image circles = HelperMethods::readFile("input/circles.tga");
    Image tempResult4 = HelperMethods::Multiply(layer2, circles);

    // Load pattern2.tga as the bottom layer and combine it with the previous result using Subtract blending mode
    Image result4 = HelperMethods::Subtract(pattern2, tempResult4);
    HelperMethods::writeFile("output/part4.tga", result4);

    // Task 5: Combine layer1.tga (top layer) with pattern1.tga using the Overlay blending mode
    Image result5 = HelperMethods::Overlay(layer1, pattern1);
    HelperMethods::writeFile("output/part5.tga", result5);

    // Task 6: Load car.tga and add 200 to the green channel
Image car2 = HelperMethods::readFile("input/car.tga");
Image result6 = HelperMethods::AddRGB(car2, 0, 200, 0);
HelperMethods::writeFile("output/part6.tga", result6);


    // Task 7: Load car.tga and scale the red channel by 4, and the blue channel by 0
    Image car3 = HelperMethods::readFile("input/car.tga");
    HelperMethods::Scale(car3, true, 4.0, false, 0.0, true, 0.0);
    HelperMethods::writeFile("output/part7.tga", car3);

    // Task 8: Load car.tga and write each channel to separate files
    Image car4 = HelperMethods::readFile("input/car.tga");
    vector<Image> rgbChannels = HelperMethods::SepRGB(car4);
    Image redChannel = rgbChannels[0];
    Image greenChannel = rgbChannels[1];
    Image blueChannel = rgbChannels[2];

    HelperMethods::writeFile("output/part8_r.tga", redChannel);
    HelperMethods::writeFile("output/part8_g.tga", greenChannel);
    HelperMethods::writeFile("output/part8_b.tga", blueChannel);

    // Task 9: Load layer_red.tga, layer_green.tga, and layer_blue.tga, and combine them into one image
    Image layerRed = HelperMethods::readFile("input/layer_red.tga");
    Image layerGreen = HelperMethods::readFile("input/layer_green.tga");
    Image layerBlue = HelperMethods::readFile("input/layer_blue.tga");
    Image result9 = HelperMethods::Combine(layerRed, layerGreen, layerBlue);
    HelperMethods::writeFile("output/part9.tga", result9);

    // Task 10: Load text2.tga and rotate it 180 degrees
    Image text2 = HelperMethods::readFile("input/text2.tga");
    Image result10 = HelperMethods::Rotate180(text2);
    HelperMethods::writeFile("output/part10.tga", result10);

    return 0;
}
