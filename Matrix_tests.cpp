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
  *Matrix_at(&mat, 4, 3) = 23;

  ostringstream os;
  
  Matrix_print(&mat, os);

  ostringstream expected;

  expected << "5 6" << endl;
  expected << "0 0 10 0 0 " << endl;
  expected << "0 0 0 0 0 " << endl;
  expected << "0 0 0 0 0 " << endl;
  expected << "0 0 0 0 0 " << endl;
  expected << "0 0 0 23 0 " << endl;
  expected << "0 0 0 0 0 " << endl;

  ASSERT_EQUAL(os.str(), expected.str());

}

TEST(test_matrix_width) {
  
  Matrix mat;
  Matrix_init(&mat, 10000, 3);

  ASSERT_EQUAL(10000, Matrix_width(&mat));
}

TEST(test_matrix_height) {
  Matrix mat;
  Matrix_init(&mat, 20, 3323);

  ASSERT_EQUAL(3323, Matrix_height(&mat));
}

TEST(test_Matrix_column_of_min_value_in_row) {
  Matrix mat;
  Matrix_init(&mat, 23, 33);
  
  int min_col = Matrix_column_of_min_value_in_row(&mat, 3, 2, 10);
  ASSERT_EQUAL(2, min_col);

  Matrix_fill(&mat, 20);
  min_col = Matrix_column_of_min_value_in_row(&mat, 2, 5, 22);
  ASSERT_EQUAL(5, min_col);

  *Matrix_at(&mat, 3, 9) = 2;
  min_col = Matrix_column_of_min_value_in_row(&mat, 3, 0, 20);
  ASSERT_EQUAL(9, min_col);
}

TEST(test_Matrix_min_value_in_row) {
  Matrix mat;
  Matrix_init(&mat, 23, 33);

  int min_value = Matrix_min_value_in_row(&mat, 3, 2, 10);
  ASSERT_EQUAL(0, min_value);

  Matrix_fill(&mat, 50);
  min_value = Matrix_min_value_in_row(&mat, 2, 5, 22);
  ASSERT_EQUAL(50, min_value);

  *Matrix_at(&mat, 3, 20) = 1;
  min_value = Matrix_min_value_in_row(&mat, 3, 18, 21);
  ASSERT_EQUAL(1, min_value);

}

TEST(test_Matrix_fill_border_small_matrix) {
  Matrix mat;
  Matrix_init(&mat, 1, 1);

  Matrix_fill_border(&mat,100);

  ostringstream os;
  Matrix_print(&mat, os);
  ostringstream expected;
  expected << "1 1\n";
  expected << "100 \n";

  ASSERT_EQUAL(os.str(), expected.str());

}


TEST_MAIN() // Do NOT put a semicolon here
