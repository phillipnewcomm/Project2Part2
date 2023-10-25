#include "HelperMethods.h"
using namespace HelperMethods;

// Max Min for RGB Pixels
const unsigned char global_max = 255;
const unsigned char global_min = 0;

// Read File
Image HelperMethods::readFile(string path) {
    ifstream file(path, ios_base::binary);
    if (file.is_open()) {

        // Read Header
        Image::Header h;
        file.read(&h.idLength, sizeof(h.idLength));
        file.read(&h.colorMapType, sizeof(h.colorMapType));
        file.read(&h.dataTypeCode, sizeof(h.dataTypeCode));
        file.read((char*)&h.colorMapOrigin, sizeof(h.colorMapOrigin));
        file.read((char*)&h.colorMapLength, sizeof(h.colorMapLength));
        file.read((char*)&h.colorMapDepth, sizeof(h.colorMapDepth));
        file.read((char*)&h.xOrigin, sizeof(h.xOrigin));
        file.read((char*)&h.yOrigin, sizeof(h.yOrigin));
        file.read((char*)&h.width, sizeof(h.width));
        file.read((char*)&h.height, sizeof(h.height));
        file.read(&h.bitsPerPixel, sizeof(h.bitsPerPixel));
        file.read(&h.imageDescriptor, sizeof(h.imageDescriptor));

        // Create Temp Image
        Image img = Image(h);

        // Add Pixels
        for (int i = 0; i < (h.height * h.width); ++i) {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            file.read((char*)&b, sizeof(b));
            file.read((char*)&g, sizeof(g));
            file.read((char*)&r, sizeof(r));
            Pixel p = Pixel(r, g, b);
            img.AddPixel(p);
        }

        // Return and close
        file.close();
        return img;
    }
    //
    cout << "Could not load: '" << path << "'. Sorry!" << endl; /////////////////////
    return Image();
}

// Write File
bool HelperMethods::writeFile(string path, Image& img) {
    ofstream file(path, ios_base::binary);
    if (file.is_open()) {

        // Write Header
        Image::Header h = img.GetHeader();
        file.write(&h.idLength, sizeof(h.idLength));
        file.write(&h.colorMapType, sizeof(h.colorMapType));
        file.write(&h.dataTypeCode, sizeof(h.dataTypeCode));
        file.write((char*)&h.colorMapOrigin, sizeof(h.colorMapOrigin));
        file.write((char*)&h.colorMapLength, sizeof(h.colorMapLength));
        file.write((char*)&h.colorMapDepth, sizeof(h.colorMapDepth));
        file.write((char*)&h.xOrigin, sizeof(h.xOrigin));
        file.write((char*)&h.yOrigin, sizeof(h.yOrigin));
        file.write((char*)&h.width, sizeof(h.width));
        file.write((char*)&h.height, sizeof(h.height));
        file.write(&h.bitsPerPixel, sizeof(h.bitsPerPixel));
        file.write(&h.imageDescriptor, sizeof(h.imageDescriptor));

        // Write Pixels
        for (int i = 0; i < img.GetPixelVectorCount(); ++i) {
            unsigned char rgb[3];
            Pixel p = img.GetIndPixel(i);
            for (int j = 0; j < 3; ++j)
                rgb[j] = p.GetRGB(j);
            // TGA file uses BGR instead of RGB:
            file.write((char*)&rgb[2], sizeof(rgb[2]));
            file.write((char*)&rgb[1], sizeof(rgb[1]));
            file.write((char*)&rgb[0], sizeof(rgb[0]));
        }

        // Close File and Return
        file.close();
        return true;
    }

    // Return False on Failure To Write
    return false;
}

// Compare Two Images:
bool HelperMethods::CompareImages(string first, string second) {
    Image FirstImage = readFile(first);
    Image SecondImage = readFile(second);
    int HeaderErrors = 0;
    int PixelErrors = 0;

    cout << "Comparing '" << first << "' - and - '" << second << "'." << endl;
    cout << "Pixels: " << FirstImage.GetPixelVectorCount() << " vs. " << SecondImage.GetPixelVectorCount() << endl;

    // Test HEADER
    if (FirstImage.GetHeader().idLength != SecondImage.GetHeader().idLength)
        HeaderErrors++;
    if (FirstImage.GetHeader().colorMapType != SecondImage.GetHeader().colorMapType)
        HeaderErrors++;
    if (FirstImage.GetHeader().dataTypeCode != SecondImage.GetHeader().dataTypeCode)
        HeaderErrors++;
    if (FirstImage.GetHeader().colorMapOrigin != SecondImage.GetHeader().colorMapOrigin)
        HeaderErrors++;
    if (FirstImage.GetHeader().colorMapLength != SecondImage.GetHeader().colorMapLength)
        HeaderErrors++;
    if (FirstImage.GetHeader().colorMapDepth != SecondImage.GetHeader().colorMapDepth)
        HeaderErrors++;
    if (FirstImage.GetHeader().xOrigin != SecondImage.GetHeader().xOrigin)
        HeaderErrors++;
    if (FirstImage.GetHeader().yOrigin != SecondImage.GetHeader().yOrigin)
        HeaderErrors++;
    if (FirstImage.GetHeader().width != SecondImage.GetHeader().width)
        HeaderErrors++;
    if (FirstImage.GetHeader().height != SecondImage.GetHeader().height)
        HeaderErrors++;
    if (FirstImage.GetHeader().bitsPerPixel != SecondImage.GetHeader().bitsPerPixel)
        HeaderErrors++;
    if (FirstImage.GetHeader().imageDescriptor != SecondImage.GetHeader().imageDescriptor)
        HeaderErrors++;

    // TEST ALL PIXELS
    for (int i = 0; i < FirstImage.GetPixelVectorCount(); ++i) {
        for (int j = 0; i < 3; ++i) {
            if (FirstImage.GetIndPixel(i).GetRGB(j) != SecondImage.GetIndPixel(i).GetRGB(j))
                PixelErrors++;
        }
    }

    if (PixelErrors == 0 && HeaderErrors == 0) {
        cout << "IMAGES MATCH. o.0 ----- Congrats." << endl;
        return true;
    }
    else {
        cout << "HEADER ERRORS: " << HeaderErrors << " PIXEL ERRORS: " << PixelErrors << endl;
        return false;
    }
}

// Print Header and Pixel Info for Comparison
void HelperMethods::PrintInfo(Image& img) {
    img.PrintHeader();
}

// Normalize Char from 0 to 1
float HelperMethods::NormChar(unsigned char c, unsigned char top, unsigned char bottom) {
    float temp = ((float)c / (float)(top - bottom));
    return temp;
}

// Multiply
Image HelperMethods::Multiply(const Image& top, const Image& bottom) {
    // Load Images, Create Temp
    Image img = Image(top.GetHeader());

    // MULTIPLY EACH PIXEL
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        Pixel pBot = bottom.GetIndPixel(i);
        float rgb[6];
        unsigned char rgbTemp[3];

        // Fill RGBs
        for (int j = 0; j < 6; ++j) {
            if (j < 3)
                rgb[j] = NormChar(pTop.GetRGB(j), global_max, global_min);
            else
                rgb[j] = NormChar(pBot.GetRGB(j - 3), global_max, global_min);
        }

        // Multiply RGBs
        for (int j = 0; j < 3; ++j) {
            if (rgb[j] * rgb[j + 3] > 1)
                rgbTemp[j] = global_max;
            else
                rgbTemp[j] = (unsigned char)((rgb[j] * rgb[j + 3]) * 255 + 0.5f);
        }

        // Add Pixel to Temp
        Pixel p = Pixel(rgbTemp[0], rgbTemp[1], rgbTemp[2]);
        img.AddPixel(p);
    }

    return img;
}


// Subtract
Image HelperMethods::Subtract(const Image& top, const Image& bottom) {
    // Load Images, Create Temp
    Image img = Image(top.GetHeader());

    // Subtract each pixel
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        Pixel pBot = bottom.GetIndPixel(i);
        unsigned char rgb[6];
        unsigned char rgbTemp[3];

        // Fill RGBs
        for (int j = 0; j < 6; ++j) {
            if (j < 3)
                rgb[j] = pTop.GetRGB(j);
            else
                rgb[j] = pBot.GetRGB(j - 3);
        }

        // Sub RGBs
        for (int j = 0; j < 3; ++j) {
            if (rgb[j+3] - rgb[j] < 0)
                rgbTemp[j] = global_min;
            else
                rgbTemp[j] = (rgb[j+3] - rgb[j]);
        }

        // Add Pixel to Temp
        Pixel p = Pixel(rgbTemp[0], rgbTemp[1], rgbTemp[2]);
        img.AddPixel(p);
    }

    return img;
}

Image HelperMethods::Screen(const Image& top, const Image& bottom) {
    // Load Images, Create Temp
    Image img = Image(top.GetHeader());

    // SCREEN EACH PIXEL
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        Pixel pBot = bottom.GetIndPixel(i);
        unsigned char rgb[6];
        unsigned char rgbTemp[3];

        // Fill RGBs
        for (int j = 0; j < 6; ++j) {
            if (j < 3)
                rgb[j] = pTop.GetRGB(j);
            else
                rgb[j] = pBot.GetRGB(j - 3);
        }

        // Screen blending mode formula
        for (int j = 0; j < 3; ++j) {
            unsigned char result = 255 - ((255 - rgb[j]) * (255 - rgb[j + 3])) / 255;
            rgbTemp[j] = result;
        }

        // Add Pixel to Temp
        Pixel p = Pixel(rgbTemp[0], rgbTemp[1], rgbTemp[2]);
        img.AddPixel(p);
    }

    return img;
}


Image HelperMethods::Overlay(const Image& top, const Image& bottom) {
    // Load Images, Create Temp
    Image img = Image(top.GetHeader());

    // Overlay each pixel
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        Pixel pBot = bottom.GetIndPixel(i);
        float rgb[6];
        unsigned char rgbTemp[3];

        // Fill RGBs
        for (int j = 0; j < 6; ++j) {
            if (j < 3)
                rgb[j] = NormChar(pTop.GetRGB(j), global_max, global_min);
            else
                rgb[j] = NormChar(pBot.GetRGB(j - 3), global_max, global_min);
        }

        // Multiply RGBs
        for (int j = 0; j < 3; ++j) {
            if (rgb[j + 3] <= 0.5) {
                float a = 2 * rgb[j] * rgb[j + 3];
                if (a > 1)
                    a = 1;
                rgbTemp[j] = (unsigned char)(a * 255 + 0.5f);
            }
            else {
                float a = 1 - 2 * (1 - rgb[j]) * (1 - rgb[j + 3]);
                if (a > 1)
                    a = 1;
                else if (a < 0)
                    a = 0;
                rgbTemp[j] = (unsigned char)(a * 255 + 0.5f);
            }
        }

        // Add Pixel to Temp
        Pixel p = Pixel(rgbTemp[0], rgbTemp[1], rgbTemp[2]);
        img.AddPixel(p);
    }

    return img;
}

Image HelperMethods::AddRGB(const Image& top, unsigned char red, unsigned char green, unsigned char blue) {
    // Load Images, Create Temp
    Image img = Image(top.GetHeader());

    // ADD RGB to Each Pixel
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        float rgb[3];
        unsigned char rgbTemp[3];

        // Fill RGBs
        for (int j = 0; j < 3; ++j)
            rgb[j] = NormChar(pTop.GetRGB(j), global_max, global_min);

        // Add RGBs
        float r = rgb[0] + NormChar(red, global_max, global_min);
        float g = rgb[1] + NormChar(green, global_max, global_min); // Update green channel
        float b = rgb[2] + NormChar(blue, global_max, global_min);

        // Clamp the values to [0, 1]
        if (r > 1.0) r = 1.0;
        if (g > 1.0) g = 1.0;
        if (b > 1.0) b = 1.0;

        // Map the values back to [0, 255] and update the pixel
        rgbTemp[0] = static_cast<unsigned char>(r * 255 + 0.5f);
        rgbTemp[1] = static_cast<unsigned char>(g * 255 + 0.5f);
        rgbTemp[2] = static_cast<unsigned char>(b * 255 + 0.5f);

        // Add Pixel to Temp
        Pixel p = Pixel(rgbTemp[0], rgbTemp[1], rgbTemp[2]);
        img.AddPixel(p);
    }

    return img;
}


Image HelperMethods::Scale(const Image& top, bool red, float x, bool green, float y, bool blue, float z) {
    // Load Images, Create Temp
    Image img = Image(top.GetHeader());

    // Scale EACH PIXEL
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        unsigned char rgb[3];
        unsigned char rgbTemp[3];

        // Fill RGBs
        for (int j = 0; j < 3; ++j)
            rgb[j] = pTop.GetRGB(j);

        // Scale Selected Colors (Char, not Floats)
        if (red == 1) {
            if (rgb[0] * x > global_max)
                rgbTemp[0] = global_max;
            else
                rgbTemp[0] = (unsigned char)(rgb[0] * x);
        }
        else
            rgbTemp[0] = rgb[0];
        if (green == 1) {
            if (rgb[1] * y > global_max)
                rgbTemp[1] = global_max;
            else
                rgbTemp[1] = (unsigned char)(rgb[1] * y);
        }
        else
            rgbTemp[1] = rgb[1];
        if (blue == 1) {
            if (rgb[2] * z > global_max)
                rgbTemp[2] = global_max;
            else
                rgbTemp[2] = (unsigned char)(rgb[2] * z);
        }
        else
            rgbTemp[2] = rgb[2];

        // Add Pixel to Temp
        Pixel p = Pixel(rgbTemp[0], rgbTemp[1], rgbTemp[2]);
        img.AddPixel(p);
    }

    return img;
}


vector<Image> HelperMethods::SepRGB(const Image& top) {
    // Load Images, Create Temp
    vector<Image> temp;
    temp.push_back(Image(top.GetHeader())); // RED
    temp.push_back(Image(top.GetHeader())); // GREEN
    temp.push_back(Image(top.GetHeader())); // BLUE

    // SEP EACH LAYER
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        unsigned char red = pTop.GetRGB(0);
        unsigned char green = pTop.GetRGB(1);
        unsigned char blue = pTop.GetRGB(2);
        Pixel redP = Pixel(red, red, red);
        Pixel greenP = Pixel(green, green, green);
        Pixel blueP = Pixel(blue, blue, blue);

        // PUSH LAYERS
        temp.at(0).AddPixel(redP);
        temp.at(1).AddPixel(greenP);
        temp.at(2).AddPixel(blueP);
    }

    return temp;
}

Image HelperMethods::Combine(const Image& red, const Image& green, const Image& blue) {
    // Load Images, Create Temp
    Image img = Image(red.GetHeader());

    // Combine Each Pixel
    for (int i = 0; i < red.GetPixelVectorCount(); ++i) {
        unsigned char rgb[3];
        // Fill RGBs
        rgb[0] = red.GetIndPixel(i).GetRGB(0);
        rgb[1] = green.GetIndPixel(i).GetRGB(0);
        rgb[2] = blue.GetIndPixel(i).GetRGB(0);

        // Add Pixel to Temp
        Pixel p = Pixel(rgb[0], rgb[1], rgb[2]);
        img.AddPixel(p);
    }

    return img;
}


Image HelperMethods::Rotate180(const Image& top) {
    // Load Images, Create Temp
    Image img = Image(top.GetHeader());

    // Rotate Image 180 degrees
    int i = (top.GetHeight() * top.GetWidth()) - 1;
    for (i; i > -1; --i) {
        Pixel p = top.GetIndPixel(i);
        img.AddPixel(p);
    }

    return img;
}

#include "HelperMethods.h"
using namespace HelperMethods;

// ... (previous implementations)

// Flip the image
Image HelperMethods::Flip(const Image& top) {
    // Load Image, Create Temp
    Image img = Image(top.GetHeader());

    // Flip EACH PIXEL horizontally
    for (int i = 0; i < top.GetHeight(); ++i) {
        for (int j = top.GetWidth() - 1; j >= 0; --j) {
            Pixel p = top.GetIndPixel(i * top.GetWidth() + j);
            img.AddPixel(p);
        }
    }

    return img;
}

// Extract only the red channel
Image HelperMethods::OnlyRed(const Image& top) {
    // Load Image, Create Temp
    Image img = Image(top.GetHeader());

    // Extract the red channel
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        unsigned char red = top.GetIndPixel(i).GetRGB(0);
        Pixel p = Pixel(red, red, red);
        img.AddPixel(p);
    }

    return img;
}

// Extract only the green channel
Image HelperMethods::OnlyGreen(const Image& top) {
    // Load Image, Create Temp
    Image img = Image(top.GetHeader());

    // Extract the green channel
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        unsigned char green = top.GetIndPixel(i).GetRGB(1);
        Pixel p = Pixel(green, green, green);
        img.AddPixel(p);
    }

    return img;
}

// Extract only the blue channel
Image HelperMethods::OnlyBlue(const Image& top) {
    // Load Image, Create Temp
    Image img = Image(top.GetHeader());

    // Extract the blue channel
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        unsigned char blue = top.GetIndPixel(i).GetRGB(2);
        Pixel p = Pixel(blue, blue, blue);
        img.AddPixel(p);
    }

    return img;
}

// Add a certain value to the red channel
Image HelperMethods::AddRed(const Image& top, int value) {
    // Load Image, Create Temp
    Image img = Image(top.GetHeader());

    // Add the specified value to the red channel of each pixel
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        unsigned char red = pTop.GetRGB(0) + value;

        // Clamp the red channel value within [0, 255]
        if (red > global_max)
            red = global_max;
        else if (red < global_min)
            red = global_min;

        Pixel p = Pixel(red, pTop.GetRGB(1), pTop.GetRGB(2));
        img.AddPixel(p);
    }

    return img;
}

// Add a certain value to the green channel
Image HelperMethods::AddGreen(const Image& top, int value) {
    // Load Image, Create Temp
    Image img = Image(top.GetHeader());

    // Add the specified value to the green channel of each pixel
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        unsigned char green = pTop.GetRGB(1) + value;

        // Clamp the green channel value within [0, 255]
        if (green > global_max)
            green = global_max;
        else if (green < global_min)
            green = global_min;

        Pixel p = Pixel(pTop.GetRGB(0), green, pTop.GetRGB(2));
        img.AddPixel(p);
    }

    return img;
}

// Add a certain value to the blue channel
Image HelperMethods::AddBlue(const Image& top, int value) {
    // Load Image, Create Temp
    Image img = Image(top.GetHeader());

    // Add the specified value to the blue channel of each pixel
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        unsigned char blue = pTop.GetRGB(2) + value;

        // Clamp the blue channel value within [0, 255]
        if (blue > global_max)
            blue = global_max;
        else if (blue < global_min)
            blue = global_min;

        Pixel p = Pixel(pTop.GetRGB(0), pTop.GetRGB(1), blue);
        img.AddPixel(p);
    }

    return img;
}

// Scale the red channel
Image HelperMethods::ScaleRed(const Image& top, int value) {
    // Load Image, Create Temp
    Image img = Image(top.GetHeader());

    // Scale the red channel of each pixel by the specified value
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        unsigned char red = static_cast<unsigned char>(pTop.GetRGB(0) * value);

        // Clamp the red channel value within [0, 255]
        if (red > global_max)
            red = global_max;
        else if (red < global_min)
            red = global_min;

        Pixel p = Pixel(red, pTop.GetRGB(1), pTop.GetRGB(2));
        img.AddPixel(p);
    }

    return img;
}

// Scale the green channel
Image HelperMethods::ScaleGreen(const Image& top, int value) {
    // Load Image, Create Temp
    Image img = Image(top.GetHeader());

    // Scale the green channel of each pixel by the specified value
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        unsigned char green = static_cast<unsigned char>(pTop.GetRGB(1) * value);

        // Clamp the green channel value within [0, 255]
        if (green > global_max)
            green = global_max;
        else if (green < global_min)
            green = global_min;

        Pixel p = Pixel(pTop.GetRGB(0), green, pTop.GetRGB(2));
        img.AddPixel(p);
    }

    return img;
}

// Scale the blue channel
Image HelperMethods::ScaleBlue(const Image& top, int value) {
    // Load Image, Create Temp
    Image img = Image(top.GetHeader());

    // Scale the blue channel of each pixel by the specified value
    for (int i = 0; i < top.GetPixelVectorCount(); ++i) {
        Pixel pTop = top.GetIndPixel(i);
        unsigned char blue = static_cast<unsigned char>(pTop.GetRGB(2) * value);

        // Clamp the blue channel value within [0, 255]
        if (blue > global_max)
            blue = global_max;
        else if (blue < global_min)
            blue = global_min;

        Pixel p = Pixel(pTop.GetRGB(0), pTop.GetRGB(1), blue);
        img.AddPixel(p);
    }

    return img;
}


Image HelperMethods::Quadrant(const Image& first, const Image& second, const Image& third, const Image& fourth) {
    // Load Images, Create Temp
    int heights[4] = { first.GetHeight(), second.GetHeight(), third.GetHeight(), fourth.GetHeight() };
    int widths[4] = { first.GetWidth(), second.GetWidth(), third.GetWidth(), fourth.GetWidth() };
    Image::Header h = first.GetHeader();
    h.width = widths[0] + widths[1];
    h.height = heights[0] + heights[2];
    Image img = Image(h);

    // Counters
    int count1 = 0;
    int count2 = 0;

    // Fill Pixels 1 & 2
    for (int i = 0; i < heights[0]; ++i) {
        for (int j = 0, k = 0 + count1; j < widths[0]; ++j) {
            Pixel p = first.GetIndPixel(k);
            img.AddPixel(p);
            count1++;
            k++;
        }
        for (int j = 0, k = 0 + count2; j < widths[1]; ++j) {
            Pixel p = second.GetIndPixel(k);
            img.AddPixel(p);
            count2++;
            k++;
        }
    }

    // Reset counters
    count1 = 0;
    count2 = 0;

    // Fill Pixels 3 & 4
    for (int i = 0; i < heights[2]; ++i) {
        for (int j = 0, k = 0 + count1; j < widths[2]; ++j) {
            Pixel p = third.GetIndPixel(k);
            img.AddPixel(p);
            count1++;
            k++;
        }
        for (int j = 0, k = 0 + count2; j < widths[3]; ++j) {
            Pixel p = fourth.GetIndPixel(k);
            img.AddPixel(p);
            count2++;
            k++;
        }
    }

    return img;
}
