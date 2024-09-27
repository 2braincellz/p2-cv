#include <iostream>
#include "Image.hpp"
#include "processing.hpp"
#include "Matrix.hpp"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char * argv[]) {

    Image img;

    string input_file = argv[1];
    string output_file = argv[2];

    ifstream fin;
    fin.open(input_file);

    if (!fin.is_open()) {
        cout << "Error opening file: " << input_file << endl;
    }

    ostringstream os;

    string word;
    while (fin >> word) {
        os << word << " ";
    }

    istringstream ss_input(os.str());
    Image_init(&img, ss_input);
    
    cout << "arguments: " << argc << endl;

    int Resized_width = stoi(argv[3]);
    
    int Resized_height = Image_height(&img);

    if (argc >= 5) {
        Resized_height = stoi(argv[4]);
    }

    cout << Resized_width << endl;
    cout << Resized_height << endl;

    //Check Errors
    if (argc != 4 && argc != 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 100;
    }
    if (Resized_width <= 0 || Resized_width > Image_width(&img)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 100;
    }
    if (Resized_height <= 0 || Resized_height > Image_height(&img)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 100;
    }

    Image_print(&img, cout);

    // seam_carve(&img, Resized_width, Resized_height);


}