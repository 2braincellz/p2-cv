#include <iostream>
#include <vector>
#include "Image.hpp"
#include <sstream>
#include <string>
#include "Matrix.cpp"
#include <cassert>

using namespace std;
void Image_init(Image* img, int width, int height) {

  img->width = width;
  img->height = height;
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);
 

}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img, is
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
void Image_init(Image* img, std::istream& is) {

    // string ppm;
    // is >> ppm;
    // assert(ppm == "P3");

    // string strWidth;
    // is >> strWidth;
    // int width = stoi(strWidth);

    // string strHeight;
    // is >> strHeight;
    // int height = stoi(strHeight);

    // Matrix_init(&img->red_channel, width, height);
    // Matrix_init(&img->green_channel, width, height);
    // Matrix_init(&img->blue_channel, width, height);
    

    // string img_str
    // Pixel p;
    // while (is >> img_str) {

    // }


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


    vector<int> reds;
    vector<int> blues;
    vector<int> greens;

    for (size_t i = 4; i < inputs.size(); ++i) {
        
        if (i % 3 == 1) {
            reds.push_back(stoi(inputs[i]));
        }
        else if (i % 3 == 2) {
            greens.push_back(stoi(inputs[i]));
        }
        else if (i % 3 == 0) {
            blues.push_back(stoi(inputs[i]));
        }


    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int idx = i * width + j;
            *Matrix_at(&img->red_channel, i, j) = reds[idx];
            *Matrix_at(&img->green_channel, i, j)= greens[idx];
            *Matrix_at(&img->blue_channel, i, j) = blues[idx];
        }
    }

    cout << *Matrix_at(&img->red_channel, 0, 1) << endl;
    cout << *Matrix_at(&img->green_channel, 0, 1) << endl;
    cout << *Matrix_at(&img->blue_channel, 0, 1) << endl;




}

// REQUIRES: img points to a valid Image
// MODIFIES: os
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
    os << "P3" << endl;
    os << Image_width(img) << " " << Image_height(img)<< endl;
    os << "255" << endl;

    for (int i = 0; i < Image_height(img); ++i) {
        for (int j = 0; j < Image_width(img); ++j) {
        //swapped img->width and img->height
            os << *Matrix_at(&img->red_channel, i, j) << ' ';
            os << *Matrix_at(&img->green_channel, i, j) << ' ';
            os << *Matrix_at(&img->blue_channel, i, j) << ' ';

        }
        os << endl;

    }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {

    int red = *Matrix_at(&img->red_channel, row, column);
    int green = *Matrix_at(&img->green_channel, row, column);
    int blue = *Matrix_at(&img->blue_channel, row, column);
    Pixel p = {red, green, blue};

    return p;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {

    *Matrix_at(&img->red_channel, row, column) = color.r;
    *Matrix_at(&img->green_channel, row, column) = color.g;
    *Matrix_at(&img->blue_channel, row, column) = color.b;


}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
    for (int i = 0; i < Image_height(img); ++i) {
        for (int j = 0; j < Image_width(img); ++j) {
            //Switched height and width and i and j positions
                *Matrix_at(&img->red_channel, i, j) = color.r;
                *Matrix_at(&img->green_channel, i, j) = color.g;
                *Matrix_at(&img->blue_channel, i, j) = color.b;

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

