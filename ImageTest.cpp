#include <iostream>
#include <vector>
#include "Image.hpp"
#include <sstream>
#include <string>
#include "Matrix.cpp"

using namespace std;


void Image_init(Image* img, int width, int height) {

  img->width = width;
  img->height = height;
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);
  Matrix_init(&img->green_channel, width, height);

}

void Image_init(Image* img, std::istream& is) {

    vector<string> inputs;

    string str;

    while (is >> str) {
        // cout << str << endl;
        inputs.push_back(str);
    }

    assert(inputs[0] == "P3");
    
    // for (int i = 0; i < inputs.size(); ++i) {
    //     cout << inputs[i] << " ";
    // }

    int width = stoi(inputs[1]);
    int height = stoi(inputs[2]);

    img->width = width;
    img->height = height;

    Matrix_init(&img->red_channel, width, height);
    Matrix_init(&img->blue_channel, width, height);
    Matrix_init(&img->green_channel, width, height);

    int max = stoi(inputs[3]);


    vector<int> reds;
    vector<int> blues;
    vector<int> greens;

    for (int i = 4; i < inputs.size(); ++i) {
        
        if (i % 3 == 1) {
            reds.push_back(stoi(inputs[i]));
        }
        else if (i % 3 == 2) {
            blues.push_back(stoi(inputs[i]));
        }
        else if (i % 3 == 0) {
            greens.push_back(stoi(inputs[i]));
        }

    }

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int idx = i * height + j;
            *Matrix_at(&img->red_channel, i, j) = reds[idx];
            *Matrix_at(&img->blue_channel, i, j) = blues[idx];
            *Matrix_at(&img->green_channel, i, j)= greens[idx];
        }
    }


}

void Image_print(const Image* img, std::ostream& os) {

    os << "P3" << endl;
    os << img->width << " " << img->height << endl;
    os << "255" << endl;

    for (int i = 0; i < img->width; ++i) {
        for (int j = 0; j < img->height; ++j) {
            os << *Matrix_at(&img->red_channel, i, j) << ' ';
            os << *Matrix_at(&img->blue_channel, i, j) << ' ';
            os << *Matrix_at(&img->green_channel, i, j) << ' ';
        }
        os << endl;

    }

}

int Image_width(const Image* img) {
  return img->width;
}

int Image_height(const Image* img) {
  return img->height;
}

Pixel Image_get_pixel(const Image * img, int row, int column) {

    int red = *Matrix_at(&img->red_channel, row, column);
    int blue = *Matrix_at(&img->blue_channel, row, column);
    int green = *Matrix_at(&img->green_channel, row, column);
    Pixel p = {red, blue, green};

    return p;
}

void Image_set_pixel(Image* img, int row, int column, Pixel color) {
    
    *Matrix_at(&img->red_channel, row, column) = color.r;
    *Matrix_at(&img->blue_channel, row, column) = color.g;
    *Matrix_at(&img->green_channel, row, column) = color.b;

}

void Image_fill(Image* img, Pixel color) {
    for (int i = 0; i < img->width; ++i) {
        for (int j = 0; j < img->height; ++j) {
                cout << j << endl;
                *Matrix_at(&img->red_channel, j, i) = color.r;
                *Matrix_at(&img->blue_channel, j, i) = color.g;
                *Matrix_at(&img->green_channel, j, i) = color.b;
        }
    }
}

int main() {
 
    Image img;

//   // A very poorly behaved input PPM.
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image_init(&img, ss_input);



  Image_print(&img, cout);
//   Pixel red = {255, 0, 0};
//   Pixel green = {0, 255, 0};
//   Image img;
//   Image_init(&img, 3, 4);

//   cout << (Image_width(&img)) << endl;;
//   cout << Image_height(&img) << endl;;

//   Image_fill(&img, red);
//   cout << Image_get_pixel(&img, 2, 2) << endl;;

//   Image_set_pixel(&img, 0, 0, green);
//   cout << Image_get_pixel(&img, 0, 0) << endl;;

}

