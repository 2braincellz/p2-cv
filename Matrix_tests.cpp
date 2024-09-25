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

TEST_MAIN() // Do NOT put a semicolon here
