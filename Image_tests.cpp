#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.


TEST(empty_set) {
  Image img;
  
  ostringstream s;
  Image_print(&img, s);

  ostringstream correct;
  correct << "P3\n0 0\n255\n";
  ASSERT_EQUAL(s.str(), correct.str());

}

TEST(Image_init_to_zero) {
  Image img;
  int width = 3;
  int height = 2;

  Image_init(&img, width, height);

  ostringstream s;
  Image_print(&img, s);

  ostringstream correct;
  correct << "P3\n3 2\n255\n";
  correct << "0 0 0 0 0 0 0 0 0 " << endl;
  correct << "0 0 0 0 0 0 0 0 0 " << endl;

  ASSERT_EQUAL(s.str(), correct.str());
}

TEST(Image_dims) {
  Image img;
  Image_init(&img, 10, 20);

  ASSERT_EQUAL(img.width, Image_width(&img));
  ASSERT_EQUAL(img.height, Image_height(&img));
}

TEST(Image_fill) {
  Image img;
  Image_init(&img, 3, 4);

  Pixel p = {255, 0, 120};

  Image_fill(&img, p);

  ostringstream s;
  Image_print(&img, s);

  ostringstream correct;
  correct << "P3\n3 4\n255\n";
  correct << "255 0 120 255 0 120 255 0 120 " << endl;
  correct << "255 0 120 255 0 120 255 0 120 " << endl;
  correct << "255 0 120 255 0 120 255 0 120 " << endl;
  correct << "255 0 120 255 0 120 255 0 120 " << endl;

  ASSERT_EQUAL(s.str(), correct.str());
}


TEST_MAIN() // Do NOT put a semicolon here
