//
// Created by Vishweshwar Ramanakumar on 3/30/21.
//

#include "Pixel.h"
#include <vector>
#include "fstream"
#include "iostream"
using namespace std;
#ifndef MAIN_CPP_IMAGE_H
#define MAIN_CPP_IMAGE_H


class Image {
public:
    struct Header {
        char idLength = 0;
        char colorMapType = 0;
        char dataTypeCode = 0;
        short colorMapOrigin = 0;
        short colorMapLength = 0;
        char colorMapDepth = 0;
        short xOrigin = 0;
        short yOrigin = 0;
        short width = 0;
        short height = 0;
        char bitsPerPixel = 0;
        char ImageDescriptor = 0;
    };
    vector<Pixel> im;
    vector<vector<Pixel>> extraCredit;
    Header header;
    void Scale(int B, int G, int R);
    void setSize();
    Pixel getPixel(int i);
    Image multiply(Image B);
    Image subtract(Image B);
    Image Screen(Image B);
    Image Overlay(Image B);
    void addPixel(Pixel pixel);
    const void Read(string string1);
    const void Write_B(Image A, string string1);
    const void Write_G(Image A, string string1);
    const void Write_R(Image A, string string1);
    const void Write(Image A, string string1);
    const void inverseWrite(Image A, string string1);
    Image combination(string G, string R);

    const void extraCreditRead(string string1) const;
};


#endif //MAIN_CPP_IMAGE_H
