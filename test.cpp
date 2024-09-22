#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


struct Matrix {
  int width;
  int height;
  vector<int> data;
};

void Matrix_init(Matrix* mat, int width, int height) {
  
//   assert(width > 0 && height > 0);
  
  mat -> width = width;
  mat -> height = height;

  int vector_size = width * height;
  
  vector<int> vec(vector_size);

  mat -> data = vec;

//   cout << mat -> data << endl;

  // TODO Replace with your implementation!
}

void Matrix_print(const Matrix* mat, std::ostream& os) {
    
    int width = mat -> width;
    int height = mat -> height;
    int size = width * height;

    for (int i = 0; i < size ; ++i) {

        if (i != 0 && i % width == 0) {
            os << "\n";
        }
        os << mat->data[i] << " ";
    }
    
    // ! Could be issue with how intialized vector values are random Example m.data[100]
    cout << "\n";
  
}

// int* Matrix_at(Matrix* mat, int row, int column) {
//   assert(0 <= row && row < mat -> height);
//   assert(0 <= column && column < mat -> width);
  
//   int idx = (row * mat->width) + column;

//   int * ptr = &mat -> data[idx];

//   return ptr;
  
// }

const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(0 <= row && row < mat -> height);
  assert(0 <= column && column < mat -> width);
  
  int idx = (row * mat->width) + column;

  const int * const ptr = &mat -> data[idx];

  return ptr;
  
}



int main() {

    Matrix m;

    Matrix_init(&m, 5, 2);

    m.data[2] = 2;
    m.data[100] = 10;
    cout << m.data[100] << endl;
    Matrix_print(&m, cout);

    cout << *Matrix_at(&m, 0, 1) << endl;

    
}