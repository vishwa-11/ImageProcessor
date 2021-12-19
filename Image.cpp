//
// Created by Vishweshwar Ramanakumar on 3/30/21.
//

#include "Image.h"
#include <string>
#include "fstream"
#include "iostream"
#include <cmath>
using namespace std;



Pixel Image::getPixel(int i) {
    return im[i];
}

Image Image::multiply(Image B) {
    
        Image Image;
        Image.header = this->header;
        Pixel Pixel;
        for (unsigned int i = 0; i < this->im.size(); i++) {
            Pixel.blue = (unsigned char)round((float)this->im[i].blue * B.im[i].blue / 255);
            Pixel.green = (unsigned char)round((float)this->im[i].green * B.im[i].green / 255);
            Pixel.red = (unsigned char)round((float)this->im[i].red * B.im[i].red / 255);
            Image.im.push_back(Pixel);
        }
        return Image;
    
}

Image Image::subtract(Image B) {
    Image Image;
    Image.header = this->header;
    Pixel Pixel;
    for (unsigned int i = 0; i < this->im.size(); i++) {
        if (this->im[i].blue - B.im[i].blue < 0) {
            Pixel.blue = 0;
        }
        else {
            Pixel.blue = this->im[i].blue - B.im[i].blue;
        }
        if (this->im[i].green - B.im[i].green < 0) {
            Pixel.green = 0;
        }
        else {
            Pixel.green = this->im[i].green - B.im[i].green;
        }
        if (this->im[i].red - B.im[i].red < 0) {
            Pixel.red = 0;
        }
        else {
            Pixel.red = this->im[i].red - B.im[i].red;
        }
        Image.im.push_back(Pixel);
    }
    return Image;
}

Image Image::Screen(Image B) {
    Image Image;
    Image.header = this->header;
    Pixel Pixel;
    for (unsigned int i = 0; i < this->im.size(); i++) {
        Pixel.blue = (unsigned char)round(255 - (float)((255 - this->im[i].blue) * (255 - B.im[i].blue)) / 255);
        Pixel.green = (unsigned char)round(255 - (float)((255 - this->im[i].green) * (255 - B.im[i].green)) / 255);
        Pixel.red = (unsigned char)round(255 - (float)((255 - this->im[i].red) * (255 - B.im[i].red)) / 255);
        Image.im.push_back(Pixel);
    }
    return Image;
}

Image Image::Overlay(Image B) {
    Image Image;
    Image.header = this->header;
    Pixel Pixel;
    for (unsigned int i = 0; i < this->im.size(); i++) {
        if ((float)B.im[i].blue / (float)255 <= 0.5f) {
            Pixel.blue = (unsigned char)round(2 * (float)(this->im[i].blue * B.im[i].blue) / 255);
        }
        else {
            Pixel.blue = (unsigned char)round(255 - 2 * (float)((255 - this->im[i].blue) * (255 - B.im[i].blue)) / 255);
        }
        if ((float)B.im[i].green / (float)255 <= 0.5f) {
            Pixel.green = (unsigned char)round(2 * (float)(this->im[i].green * B.im[i].green) / 255);
        }
        else {
            Pixel.green = (unsigned char)round(255 - 2 * (float)((255 - this->im[i].green) * (255 - B.im[i].green)) / 255);
        }
        if ((float)B.im[i].red / (float)255 <= 0.5f) {
            Pixel.red = (unsigned char)round(2 * (float)(this->im[i].red * B.im[i].red) / 255);
        }
        else {
            Pixel.red = (unsigned char)round(255 - 2 * (float)((255 - this->im[i].red) * (255 - B.im[i].red)) / 255);
        }
        Image.im.push_back(Pixel);
    }
    return Image;
}

void Image::addPixel(Pixel pixel) {
    im.push_back(pixel);
}

const void Image::Read(string string1) {
    ifstream file(string1, ios::in | ios::binary);

    file.read(&header.idLength, sizeof(header.idLength));
    file.read(&header.colorMapType, sizeof(header.colorMapType));
    file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
    file.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    file.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
    file.read((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));
    file.read((char*)&header.xOrigin, sizeof(header.xOrigin));
    file.read((char*)&header.yOrigin, sizeof(header. yOrigin));
    file.read((char*)&header.width, sizeof(header.width));
    file.read((char*)&header.height, sizeof(header.height));
    file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.read(&header.ImageDescriptor, sizeof(header.ImageDescriptor));



    this->setSize();

    for (int i = 0; i < header.width * header.height; i++) {

        file.read((char*)&im[i].blue, 1);
        file.read((char*)&im[i].green, 1);
        file.read((char*)&im[i].red, 1);
    }

    file.close();
}

void Image::setSize() {
    im.resize(header.width * header.height);
}

const void Image::Write(Image A, string string1) {
    ofstream file1_2(string1, ios::out | ios::binary);

    file1_2.write((char *)&this->header.idLength, sizeof(this->header.idLength));
    file1_2.write((char *)&this->header.colorMapType, sizeof(this->header.colorMapType));
    file1_2.write((char *)&this->header.dataTypeCode, sizeof(this->header.dataTypeCode));
    file1_2.write((char *)&this->header.colorMapOrigin, sizeof(this->header.colorMapOrigin));
    file1_2.write((char *)&this->header.colorMapLength, sizeof(this->header.colorMapLength));
    file1_2.write((char *)&this->header.colorMapDepth, sizeof(this->header.colorMapDepth));
    file1_2.write((char *)&this->header.xOrigin, sizeof(this->header.xOrigin));
    file1_2.write((char *)&this->header.yOrigin, sizeof(this->header.yOrigin));
    file1_2.write((char *)&this->header.width, sizeof(this->header.width));
    file1_2.write((char *)&this->header.height, sizeof(this->header.height));
    file1_2.write((char *)&this->header.bitsPerPixel, sizeof(this->header.bitsPerPixel));
    file1_2.write((char *)&this->header.ImageDescriptor, sizeof(this->header.ImageDescriptor));


    for (int i = 0; i < header.width * header.height; i++) {
        file1_2.write((char*)&A.im[i].blue, 1);
        file1_2.write((char*)&A.im[i].green, 1);
        file1_2.write((char*)&A.im[i].red, 1);
    }
}

void Image::Scale(int B, int G, int R) {
    for (int i = 0; i < this->header.width * this->header.height; i++) {
        if (this->im[i].blue * B < 255) {
            this->im[i].blue *= B;
        }
        else {
            this->im[i].blue = 255;
        }
        if (this->im[i].green * G < 255) {
            this->im[i].green *= G;
        }
        else {
            this->im[i].green = 255;
        }
        if (this->im[i].red * R < 255) {
            this->im[i].red *= R;
        }
        else {
            this->im[i].red = 255;
        }
    }
}

const void Image::Write_B(Image A, string string1) {
    ofstream file1_2(string1, ios::out | ios::binary);

    file1_2.write((char *)&this->header.idLength, sizeof(this->header.idLength));
    file1_2.write((char *)&this->header.colorMapType, sizeof(this->header.colorMapType));
    file1_2.write((char *)&this->header.dataTypeCode, sizeof(this->header.dataTypeCode));
    file1_2.write((char *)&this->header.colorMapOrigin, sizeof(this->header.colorMapOrigin));
    file1_2.write((char *)&this->header.colorMapLength, sizeof(this->header.colorMapLength));
    file1_2.write((char *)&this->header.colorMapDepth, sizeof(this->header.colorMapDepth));
    file1_2.write((char *)&this->header.xOrigin, sizeof(this->header.xOrigin));
    file1_2.write((char *)&this->header.yOrigin, sizeof(this->header.yOrigin));
    file1_2.write((char *)&this->header.width, sizeof(this->header.width));
    file1_2.write((char *)&this->header.height, sizeof(this->header.height));
    file1_2.write((char *)&this->header.bitsPerPixel, sizeof(this->header.bitsPerPixel));
    file1_2.write((char *)&this->header.ImageDescriptor, sizeof(this->header.ImageDescriptor));


    char s = 0;
    char t = 0;
    for (int i = 0; i < header.width * header.height; i++) {
        file1_2.write((char*)&A.im[i].blue, 1);
        file1_2.write((char*)&A.im[i].blue, 1);
        file1_2.write((char*)&A.im[i].blue, 1);
    }
}

const void Image::Write_G(Image A, string string1) {
    ofstream file1_2(string1, ios::out | ios::binary);

    file1_2.write((char *)&this->header.idLength, sizeof(this->header.idLength));
    file1_2.write((char *)&this->header.colorMapType, sizeof(this->header.colorMapType));
    file1_2.write((char *)&this->header.dataTypeCode, sizeof(this->header.dataTypeCode));
    file1_2.write((char *)&this->header.colorMapOrigin, sizeof(this->header.colorMapOrigin));
    file1_2.write((char *)&this->header.colorMapLength, sizeof(this->header.colorMapLength));
    file1_2.write((char *)&this->header.colorMapDepth, sizeof(this->header.colorMapDepth));
    file1_2.write((char *)&this->header.xOrigin, sizeof(this->header.xOrigin));
    file1_2.write((char *)&this->header.yOrigin, sizeof(this->header.yOrigin));
    file1_2.write((char *)&this->header.width, sizeof(this->header.width));
    file1_2.write((char *)&this->header.height, sizeof(this->header.height));
    file1_2.write((char *)&this->header.bitsPerPixel, sizeof(this->header.bitsPerPixel));
    file1_2.write((char *)&this->header.ImageDescriptor, sizeof(this->header.ImageDescriptor));


    char s = 0;
    char t = 0;
    for (int i = 0; i < header.width * header.height; i++) {
        file1_2.write((char*)&A.im[i].green, 1);
        file1_2.write((char*)&A.im[i].green, 1);
        file1_2.write((char*)&A.im[i].green, 1);
    }
}

const void Image::Write_R(Image A, string string1) {
    ofstream file1_2(string1, ios::out | ios::binary);

    file1_2.write((char *)&this->header.idLength, sizeof(this->header.idLength));
    file1_2.write((char *)&this->header.colorMapType, sizeof(this->header.colorMapType));
    file1_2.write((char *)&this->header.dataTypeCode, sizeof(this->header.dataTypeCode));
    file1_2.write((char *)&this->header.colorMapOrigin, sizeof(this->header.colorMapOrigin));
    file1_2.write((char *)&this->header.colorMapLength, sizeof(this->header.colorMapLength));
    file1_2.write((char *)&this->header.colorMapDepth, sizeof(this->header.colorMapDepth));
    file1_2.write((char *)&this->header.xOrigin, sizeof(this->header.xOrigin));
    file1_2.write((char *)&this->header.yOrigin, sizeof(this->header.yOrigin));
    file1_2.write((char *)&this->header.width, sizeof(this->header.width));
    file1_2.write((char *)&this->header.height, sizeof(this->header.height));
    file1_2.write((char *)&this->header.bitsPerPixel, sizeof(this->header.bitsPerPixel));
    file1_2.write((char *)&this->header.ImageDescriptor, sizeof(this->header.ImageDescriptor));


    char s = 0;
    char t = 0;
    for (int i = 0; i < header.width * header.height; i++) {
        file1_2.write((char*)&A.im[i].red, 1);
        file1_2.write((char*)&A.im[i].red, 1);
        file1_2.write((char*)&A.im[i].red, 1);
    }
}

Image Image::combination(string G, string R) {
    Image g;
    g.Read(G);
    Image r;
    r.Read(R);

    Image image = *this;

    for (int i = 0; i < header.width * header.height; i++) {
        image.im[i].blue = this->im[i].blue;
        image.im[i].green = g.im[i].green;
        image.im[i].red = r.im[i].red;
    }

    return image;
}

const void Image::inverseWrite(Image A, string string1) {
    ofstream file1_2(string1, ios::out | ios::binary);

    file1_2.write((char *)&this->header.idLength, sizeof(this->header.idLength));
    file1_2.write((char *)&this->header.colorMapType, sizeof(this->header.colorMapType));
    file1_2.write((char *)&this->header.dataTypeCode, sizeof(this->header.dataTypeCode));
    file1_2.write((char *)&this->header.colorMapOrigin, sizeof(this->header.colorMapOrigin));
    file1_2.write((char *)&this->header.colorMapLength, sizeof(this->header.colorMapLength));
    file1_2.write((char *)&this->header.colorMapDepth, sizeof(this->header.colorMapDepth));
    file1_2.write((char *)&this->header.xOrigin, sizeof(this->header.xOrigin));
    file1_2.write((char *)&this->header.yOrigin, sizeof(this->header.yOrigin));
    file1_2.write((char *)&this->header.width, sizeof(this->header.width));
    file1_2.write((char *)&this->header.height, sizeof(this->header.height));
    file1_2.write((char *)&this->header.bitsPerPixel, sizeof(this->header.bitsPerPixel));
    file1_2.write((char *)&this->header.ImageDescriptor, sizeof(this->header.ImageDescriptor));


    for (int i = header.width * header.height - 1; i >= 0; i--) {
        file1_2.write((char*)&A.im[i].blue, 1);
        file1_2.write((char*)&A.im[i].green, 1);
        file1_2.write((char*)&A.im[i].red, 1);
    }
}

const void Image::extraCreditRead(string string1) const {
    ifstream file(string1, ios::in | ios::binary);

    file.read((char*)&header.idLength, sizeof(header.idLength));
    file.read((char*)&header.colorMapType, sizeof(header.colorMapType));
    file.read((char*)&header.dataTypeCode, sizeof(header.dataTypeCode));
    file.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    file.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
    file.read((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));
    file.read((char*)&header.xOrigin, sizeof(header.xOrigin));
    file.read((char*)&header.yOrigin, sizeof(header. yOrigin));
    file.read((char*)&header.width, sizeof(header.width));
    file.read((char*)&header.height, sizeof(header.height));
    file.read((char*)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.read((char*)&header.ImageDescriptor, sizeof(header.ImageDescriptor));

    for (int i = 0; i < header.height; i++) {
        for (int j = 0; j < header.width; j++) {
            file.read((char*)&extraCredit[i][j].blue, 1);
            file.read((char*)&extraCredit[i][j].green, 1);
            file.read((char*)&extraCredit[i][j].red, 1);
        }
    }
}




