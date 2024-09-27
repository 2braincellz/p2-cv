#include <cassert>
#include "Image.hpp"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// REQUIRES: img points to an Image
//           0 < width && 0 < height
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height, with
//           all pixels initialized to RGB values of 0.
void Image_init(Image* img, int width, int height) {

  assert(img != nullptr);
  assert(0 < width && 0 < height);

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

    assert(img != nullptr);

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

    for (size_t i = 4; i < inputs.size(); i+=3) {

        reds.push_back(stoi(inputs[i]));
        greens.push_back(stoi(inputs[i+1]));
        blues.push_back(stoi(inputs[i+2])); 
       
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int idx = i * height + j;
            *Matrix_at(&img->red_channel, i, j) = reds[idx];
            *Matrix_at(&img->blue_channel, i, j) = blues[idx];
            *Matrix_at(&img->green_channel, i, j)= greens[idx];
        }
    }

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

    assert(img != nullptr);

    os << "P3" << endl;
    os << img->width << " " << img->height << endl;
    os << "255" << endl;

    for (int i = 0; i < img->height; ++i) {
        for (int j = 0; j < img->width; ++j) {
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

  assert(img != nullptr);  
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {

  assert(img != nullptr);  
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {

    // assert(img != nullptr);
    // assert(0 <= row && row < Image_height(img));
    // assert(0 <= column && column < Image_width(img));


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

    // assert(img != nullptr);
    // assert(0 <= row && row < Image_height(img));
    // assert(0 <= column && column < Image_width(img));

    *Matrix_at(&img->red_channel, row, column) = color.r;
    *Matrix_at(&img->green_channel, row, column) = color.g;
    *Matrix_at(&img->blue_channel, row, column) = color.b;


}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {

    assert(img != nullptr);

    for (int i = 0; i < img->height; ++i) {
        for (int j = 0; j < img->width; ++j) {
            //Switched height and width and i and j positions
                *Matrix_at(&img->red_channel, i, j) = color.r;
                *Matrix_at(&img->green_channel, i, j) = color.g;
                *Matrix_at(&img->blue_channel, i, j) = color.b;
        }
    }
}