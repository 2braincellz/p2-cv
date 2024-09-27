#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>


using namespace std;

using std::ostringstream;

struct Matrix {
  int width;
  int height;
  vector<int> data;
};

void Matrix_init(Matrix* mat, int width, int height) {
  
  
  mat -> width = width;
  mat -> height = height;

  int vector_size = width * height;
  
  vector<int> vec(vector_size);

  mat -> data = vec;


  // TODO Replace with your implementation!
}

void Matrix_print(const Matrix* mat, std::ostream& os) {
    
    int width = mat -> width;
    int height = mat -> height;
    int size = width * height;

    os << width << " " << height << endl;

    for (int i = 0; i < size ; ++i) {

        if (i != 0 && i % width == 0) {
            os << "\n";
        }
        os << mat->data[i] << " ";
    }
    
    // ! Could be issue with how intialized vector values are random Example m.data[100]
    os << "\n";
  
}

int Matrix_width(const Matrix* mat) {

  return mat->width;

}

int Matrix_height(const Matrix* mat) {

  return mat->height;

}

int* Matrix_at(Matrix* mat, int row, int column) {
  assert(0 <= row && row < mat -> height);
  assert(0 <= column && column < mat -> width);
  
  int idx = (row * mat->width) + column;

  int * ptr = &mat -> data[idx];

  return ptr;
  
}

const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(0 <= row && row < mat -> height);
  assert(0 <= column && column < mat -> width);
  
  int idx = (row * mat->width) + column;

  const int * const ptr = &mat -> data[idx];

  return ptr;
  
}

void Matrix_fill(Matrix* mat, int value) {

  int size = Matrix_height(mat) * Matrix_width(mat);

  for (int i = 0; i < size; ++i) {
    mat->data[i] = value;
  }

}

void Matrix_fill_border(Matrix* mat, int value) {

  int size = mat->height * mat->width;

  for (int i = 0; i < size; ++i) {
    if (i % mat->width == 0 || i % mat->width == mat->width - 1) {
      mat->data[i] = value;
    }
    if (i < mat->width || i > (size - mat->width)) {
      mat->data[i] = value;
    }

  } 
}

int Matrix_max(const Matrix* mat) {

  int size = mat->width * mat->height;

  int max = mat->data[0];

  for (int i = 0; i < size; ++i) {
    if (mat->data[i] > max) {
      max = mat->data[i];
    }
  }
  
  return max;
}

int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
    int min_col = column_start;

    int selected_row = row * Matrix_width(mat);

    int min = mat->data[selected_row];

    for (int i = column_start ; i < column_end ; ++i) {

      int idx = selected_row + i;

      if (mat->data[idx] < min) {
        min = mat->data[idx];
        min_col = i;
      }
        

    }

    return min_col;

}

int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {

 assert(mat != nullptr);
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  int selected_row = row * Matrix_width(mat);

  // return mat->data[selected_row + Matrix_column_of_min_value_in_row(mat, row, column_start, column_end)];
  return *Matrix_at(mat, row, Matrix_column_of_min_value_in_row(mat, row, column_start, column_end));
}


int main() {

  Matrix mat;
  Matrix_init(&mat, 1, 1);

  Matrix_fill_border(&mat,100);

  ostringstream os;
  Matrix_print(&mat, os);
  ostringstream expected;
  expected << "1 1\n";
  expected << "100\n";

  cout << os.str() << endl;
  cout << expected.str() << endl;

  // ostringstream expected;
  // expected << "1 1\n"
  //          << "42 \n";
  // ostringstream actual;
  // Matrix_print(&mat, actual);
  // ASSERT_EQUAL(expected.str(), actual.str())

    // Matrix m;

    // Matrix_init(&m, 20, 20);

    // m.data[2] = 2;
    // m.data[100] = 10;
    // cout << m.data[100] << endl;

    // Matrix_fill(&m, 2);

    // Matrix_print(&m, cout);

    // cout << *Matrix_at(&m, 0, 1) << endl;

    // Matrix_fill_border(&m, 3);
    // Matrix_print(&m, cout);

    // cout << Matrix_max(&m) << endl;

    // cout << Matrix_column_of_min_value_in_row(&m, 2, 0,10) << endl;

    // cout << Matrix_min_value_in_row(&m, 2, 0, 10 ) << endl;

    
}