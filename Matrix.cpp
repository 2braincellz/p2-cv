#include <cassert>
#include "Matrix.hpp"
#include <vector>

using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {

  assert(width > 0 && height > 0);
  
  mat -> width = width;
  mat -> height = height;

  int vector_size = width * height;
  
  vector<int> vec(vector_size);

  mat -> data = vec;

}



// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  //You could just call Matrix_width
    os << Matrix_width(mat) << " " << Matrix_height(mat) << endl;

    for (int i = 0; i < (Matrix_width(mat) * Matrix_height(mat)); ++i) {

        if (i != 0 && i % Matrix_width(mat) == 0) {
            os << "\n";
        }
        os << mat->data[i] << " ";
    }
    
    // ! Could be issue with how intialized vector values are random Example m.data[100]
    os << "\n";
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {

  return mat->width;

}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {

  return mat->height;

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(0 <= row && row < mat -> height);
  assert(0 <= column && column < mat -> width);
  
  int idx = (row * mat->width) + column;

  int * ptr = &mat -> data[idx];

  return ptr;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(0 <= row && row < mat -> height);
  assert(0 <= column && column < mat -> width);
  
  int idx = (row * mat->width) + column;

  const int * const ptr = &mat -> data[idx];

  return ptr;
  
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {

  int size = Matrix_height(mat) * Matrix_width(mat);

  for (int i = 0; i < size; ++i) {
    mat->data[i] = value;
  }

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {

  int size = Matrix_width(mat) * Matrix_height(mat);

  for (int i = 0; i < size; ++i) {
    if (i % mat->width == 0 || i % mat->width == mat->width - 1) {
      mat->data[i] = value;
    }
    if (i < mat->width || i > (size - mat->width)) {
      mat->data[i] = value;
    }

  } 

}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {

  int size = Matrix_width(mat) * Matrix_height(mat);

  int max = mat->data[0];

  for (int i = 0; i < size; ++i) {
    if (mat->data[i] > max) {
      max = mat->data[i];
    }
  }
  
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
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

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  
  int selected_row = row * Matrix_width(mat);

  return mat->data[selected_row + Matrix_column_of_min_value_in_row(mat, row, column_start, column_end)];


}
