#include "HelperMethods.h"
#include "Image.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <tracking_image> <operation1> [arguments1] [operation2] [arguments2] ..." << std::endl;
        return 1;
    }

    // Load the tracking image from the command-line argument
    std::string trackingImagePath = argv[1];
    Image trackingImage = HelperMethods::readFile(trackingImagePath);

    // Iterate through command-line arguments starting from the third argument
    for (int i = 2; i < argc; i++) {
        std::string operation = argv[i];

        // Multiplication
        if (operation == "multiply" && i + 1 < argc) {
            std::string imagePath = argv[i + 1];
            Image image = HelperMethods::readFile(imagePath);
            trackingImage = HelperMethods::Multiply(trackingImage, image);
            i++;
        }
            // Subtraction
        else if (operation == "subtract" && i + 1 < argc) {
            std::string imagePath = argv[i + 1];
            Image image = HelperMethods::readFile(imagePath);
            trackingImage = HelperMethods::Subtract(trackingImage, image);
            i++;
        }
            // Overlay
        else if (operation == "overlay" && i + 1 < argc) {
            std::string imagePath = argv[i + 1];
            Image image = HelperMethods::readFile(imagePath);
            trackingImage = HelperMethods::Overlay(trackingImage, image);
            i++;
        }
            // Screen
        else if (operation == "screen" && i + 1 < argc) {
            std::string imagePath = argv[i + 1];
            Image image = HelperMethods::readFile(imagePath);
            trackingImage = HelperMethods::Screen(trackingImage, image);  // Corrected order of arguments
            i++;
        }
            // Combine
        else if (operation == "combine" && i + 2 < argc) {
            std::string greenPath = argv[i + 1];
            std::string bluePath = argv[i + 2];
            Image greenImage = HelperMethods::readFile(greenPath);
            Image blueImage = HelperMethods::readFile(bluePath);
            trackingImage = HelperMethods::Combine(trackingImage, greenImage, blueImage);
            i += 2;
        }
            // Flip
        else if (operation == "flip") {
            trackingImage = HelperMethods::Flip(trackingImage);
        }
            // Only Red
        else if (operation == "onlyred") {
            trackingImage = HelperMethods::OnlyRed(trackingImage);
        }
            // Only Green
        else if (operation == "onlygreen") {
            trackingImage = HelperMethods::OnlyGreen(trackingImage);
        }
            // Only Blue
        else if (operation == "onlyblue") {
            trackingImage = HelperMethods::OnlyBlue(trackingImage);
        }
            // Add Red
        else if (operation == "addred" && i + 1 < argc) {
            int value = std::stoi(argv[i + 1]);
            trackingImage = HelperMethods::AddRed(trackingImage, value);
            i++;
        }
            // Add Green
        else if (operation == "addgreen" && i + 1 < argc) {
            int value = std::stoi(argv[i + 1]);
            trackingImage = HelperMethods::AddGreen(trackingImage, value);
            i++;
        }
            // Add Blue
        else if (operation == "addblue" && i + 1 < argc) {
            int value = std::stoi(argv[i + 1]);
            trackingImage = HelperMethods::AddBlue(trackingImage, value);
            i++;
        }
            // Scale Red
        else if (operation == "scalered" && i + 1 < argc) {
            int value = std::stoi(argv[i + 1]);
            trackingImage = HelperMethods::ScaleRed(trackingImage, value);
            i++;
        }
            // Scale Green
        else if (operation == "scalegreen" && i + 1 < argc) {
            int value = std::stoi(argv[i + 1]);
            trackingImage = HelperMethods::ScaleGreen(trackingImage, value);
            i++;
        }
            // Scale Blue
        else if (operation == "scaleblue" && i + 1 < argc) {
            int value = std::stoi(argv[i + 1]);
            trackingImage = HelperMethods::ScaleBlue(trackingImage, value);
            i++;
        }
            // Unknown operation
        else {
            std::cerr << "Unknown operation: " << operation << std::endl;
            return 1;
        }
    }

    // Save the final tracking image to an output file
    HelperMethods::writeFile("output/tracking_output.tga", trackingImage);

    return 0;
}

    // Save the final tracking image to an output file
    HelperMethods::writeFile("output/tracking_output.tga", trackingImage);

    return 0;
}
