#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}
TEST(test_fill_border) {
  Matrix mat;
  const int value = 42;
  const int border_value = 17;
  Matrix_init(&mat, 3, 4);
  Matrix_fill(&mat, value);
  Matrix_fill_border(&mat, border_value);
  ostringstream expected;
  expected << "3 4\n"
           << "17 17 17 \n"
           << "17 42 17 \n"
           << "17 42 17 \n"
           << "17 17 17 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}
TEST(test_Matrix_column) {
  Matrix mat;
  const int value = 42;
  const int border_value = 17;
  Matrix_init(&mat, 5, 4);
  Matrix_fill(&mat, value);
  Matrix_fill_border(&mat, border_value);
  ostringstream expected;
  expected << "5 4\n"
           << "17 17 17 17 17 \n"
           << "17 42 42 42 17\n"
           << "17 42 42 42 17 \n"
           << "17 17 17 17 17\n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1,1,5), 4);
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST(test_Matrix_init) {
  Matrix mat1;
  Matrix mat2;

  Matrix_init(&mat1, 2, 3);
  vector<int> test_data(6);

  mat2.width = 2;
  mat2.height = 3;
  mat2.data = test_data;

  Matrix_equal(&mat1, &mat2);

}


TEST(test_print) {
  Matrix mat;

  Matrix_init(&mat, 5, 6);

  *Matrix_at(&mat, 0, 2) = 10;

  ostringstream os;
  
  Matrix_print(&mat, os);

  ostringstream expected;

  expected << "5 6" << endl;
  expected << "0 0 10 0 0 " << endl;
  expected << "0 0 0 0 0 " << endl;
  expected << "0 0 0 0 0 " << endl;
  expected << "0 0 0 0 0 " << endl;
  expected << "0 0 0 0 0 " << endl;
  expected << "0 0 0 0 0 " << endl;


  ASSERT_EQUAL(os.str(), expected.str());

}


TEST_MAIN() // Do NOT put a semicolon here
