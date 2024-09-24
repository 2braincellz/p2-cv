#include <iostream>
#include <vector>
#include "Image.hpp"
#include <sstream>
#include <string>
#include "Matrix.cpp"

using namespace std;


void Image_init(Image* img, std::istream& is) {

    vector<string> inputs;

    string str;

    while (is >> str) {
        cout << str << endl;
        inputs.push_back(str);
    }

    assert(inputs[0] == "P3");
    
    for (int i = 0; i < inputs.size(); ++i) {
        cout << inputs[i] << " ";
    }

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


int main() {
 
    Image img;

  // A very poorly behaved input PPM.
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image_init(&img, ss_input);
}

