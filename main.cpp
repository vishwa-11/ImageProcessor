#include <iostream>
#include <vector>
#include "Image.h"
using namespace std;

int main() {

    //part 1
    Image layer1;
    layer1.Read("input/layer1.tga");

    Image pattern1;
    pattern1.Read("input/pattern1.tga");

    Image part1 = layer1.multiply(pattern1);

    layer1.Write(part1, "output/part1.tga");

    //part2
    Image layer2;
    layer2.Read("input/layer2.tga");

    Image car;
    car.Read("input/car.tga");

    Image part2 = car.subtract(layer2);

    car.Write(part2, "output/part2.tga");

    //part3
    Image pattern2;
    pattern2.Read("input/pattern2.tga");

    Image part3_1 = layer1.multiply(pattern2);

    Image text;
    text.Read("input/text.tga");

    Image part3 = text.Screen(part3_1);

    part3_1.Write(part3, "output/part3.tga");

    //part4
    Image circles;
    circles.Read("input/circles.tga");

    Image part4_1 = layer2.multiply(circles);

    Image part4 = part4_1.subtract(pattern2);

    part4_1.Write(part4, "output/part4.tga");

    //part5
    Image part5 = layer1.Overlay(pattern1);

    layer1.Write(part5, "output/part5.tga");

    //part6
    car.Read("input/car.tga");
    Image part6 = car;
    
    for (int i = 0; i < part6.header.width * part6.header.height; i++) {
        if (part6.im[i].green + 200 < 255) {
            part6.im[i].green += 200;
        }
        else {
            part6.im[i].green = 255;
        }
    }
    
    part6.Write(part6, "output/part6.tga");

    //part7
    car.Scale(0, 1, 4);
    car.Write(car, "output/part7.tga");

    //part8
    car.Read("input/car.tga");
    car.Write_R(car, "output/part8_r.tga");
    car.Read("input/car.tga");
    car.Write_G(car, "output/part8_g.tga");
    car.Read("input/car.tga");
    car.Write_B(car, "output/part8_b.tga");

    //part9
    Image blue;
    blue.Read("input/layer_blue.tga");

    Image part9 = blue.combination("input/layer_green.tga", "input/layer_red.tga");
    part9.Write(part9, "output/part9.tga");

    //part10
    Image text2;
    text2.Read("input/text2.tga");

    text2.inverseWrite(text2, "output/part10.tga");

    //Extra Credit
    ofstream extra("output/extracredit.tga", ios::out | ios::binary);

    car.Read("input/car.tga");
    circles.Read("input/circles.tga");
    pattern1.Read("input/pattern1.tga");
    text.Read("input/text.tga");

    int Width = 2 * 512;
    int Height = 2 * 512;

    extra.write((char *)&car.header.idLength, sizeof(car.header.idLength));
    extra.write((char *)&car.header.colorMapType, sizeof(car.header.colorMapType));
    extra.write((char *)&car.header.dataTypeCode, sizeof(car.header.dataTypeCode));
    extra.write((char *)&car.header.colorMapOrigin, sizeof(car.header.colorMapOrigin));
    extra.write((char *)&car.header.colorMapLength, sizeof(car.header.colorMapLength));
    extra.write((char *)&car.header.colorMapDepth, sizeof(car.header.colorMapDepth));
    extra.write((char *)&car.header.xOrigin, sizeof(car.header.xOrigin));
    extra.write((char *)&car.header.yOrigin, sizeof(car.header.yOrigin));
    extra.write((char *)&Width, sizeof(car.header.width));
    extra.write((char *)&Height, sizeof(car.header.height));
    extra.write((char *)&car.header.bitsPerPixel, sizeof(car.header.bitsPerPixel));
    extra.write((char *)&car.header.ImageDescriptor, sizeof(car.header.ImageDescriptor));




    for (int k = 0; k < car.header.height; k++) {
        for (int l = k * car.header.width; l < (k + 1) * car.header.width; l++) {
            extra.write((char*)&text.im[l].blue, 1);
            extra.write((char*)&text.im[l].green, 1);
            extra.write((char*)&text.im[l].red, 1);
        }
        for (int b = k * car.header.width; b < (k + 1) * car.header.width; b++) {
            extra.write((char*)&pattern1.im[b].blue, 1);
            extra.write((char*)&pattern1.im[b].green, 1);
            extra.write((char*)&pattern1.im[b].red, 1);
        }
    }

    for (int i = 0; i < car.header.height; i++) {

        for (int j = i * car.header.width; j < (i + 1) * car.header.width; j++) {
            extra.write((char*)&car.im[j].blue, 1);
            extra.write((char*)&car.im[j].green, 1);
            extra.write((char*)&car.im[j].red, 1);
        }
        for (int a = i * car.header.width; a < (i + 1) * car.header.width; a++) {
            extra.write((char*)&circles.im[a].blue, 1);
            extra.write((char*)&circles.im[a].green, 1);
            extra.write((char*)&circles.im[a].red, 1);
        }
    }

    extra.close();

    return 0;
}
