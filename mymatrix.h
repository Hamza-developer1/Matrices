
/*mymatrix.h*/

// Muhmmad Hamza Shaikh
// Program 3 My Matrix
// CS 251 10 am
// Wednesday 12pm Lab
// 2/28/23
//
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and
// cols).  Also, rows can be "jagged" --- i.e. rows can have
// different column sizes, and thus the matrix is not necessarily
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <exception>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T> class mymatrix {
private:
  struct ROW {
    T *Cols;     // dynamic array of column elements
    int NumCols; // total # of columns (0..NumCols-1)
  };

  ROW *Rows;   // dynamic array of ROWs
  int NumRows; // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All
  // elements are initialized to the default value of T.
  //
  mymatrix() {
    Rows = new ROW[4]; // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r) {
      Rows[r].Cols = new T[4]; // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c) {
        Rows[r].Cols[c] = T{}; // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows,
  // where each row has C columns. All elements are initialized to
  // the default value of T.
  //
  mymatrix(int R, int C) {
    if (R < 1)
      throw std::invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw std::invalid_argument("mymatrix::constructor: # of cols");

    Rows = new ROW[R]; // an array with any value ROW structs:
    NumRows = R;

    // initialize each row to have 4 columns:
    for (int row = 0; row < NumRows; ++row) {
      Rows[row].Cols = new T[C]; // an array with 4 elements of type T:
      Rows[row].NumCols = C;

      // initialize the elements to their default value:
      for (int col = 0; col < Rows[row].NumCols; ++col) {
        Rows[row].Cols[col] = T{}; // default value for type T:
      }
    }
  }

  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a
  // copy of an existing matrix.  Example: this occurs when passing
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T> &other) {

    Rows = new ROW[other.NumRows]; // array of # of Rows
    NumRows = other.NumRows;

    // The nested for loop copies the contents of the Row and Columns in the
    // matrix to another matrix
    for (int row = 0; row < NumRows; ++row) {
      Rows[row].Cols = new T[other.Rows[row].NumCols];
      Rows[row].NumCols = other.Rows[row].NumCols;

      for (int col = 0; col < Rows[row].NumCols; ++col) {
        Rows[row].Cols[col] = other.Rows[row].Cols[col];
      }
    }
  }

  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const {

    return NumRows; // return # of rows
  }

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int row) const {
    if (row < 0 || row >= NumRows)
      throw std::invalid_argument("mymatrix::numcols: row");

    return Rows[row].NumCols; // Return the # of columns in row r
  }

  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int row, int C) {
    if (row < 0 || row >= NumRows)
      throw std::invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw std::invalid_argument("mymatrix::growcols: columns");

    // makes sure the row has at least 1 column
    if (numcols(row) >= C) {
      return;
    }

    T *newNumCols = new T[C]; // new array for ROW

    // the value gets initialized to the defualt value of T
    for (int col = 0; col < C; col++) {
      newNumCols[col] = T{};
    }

    // this copies the numCols to the new array which is a pointer
    for (int col = 0; col < Rows[row].NumCols; col++) {
      newNumCols[col] = Rows[row].Cols[col];
    }
    Rows[row].Cols = newNumCols;
    Rows[row].NumCols = C;
  }

  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  //
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  //
  void grow(int R, int C) {
    ROW *newR = new ROW[R]; // pointer of array
    if (R < 1)
      throw std::invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw std::invalid_argument("mymatrix::grow: # of cols");

    // checks to see if R is greater or equal than the numRows because we cannot
    // reduce a column or row
    if (R <= numrows()) {
      for (int row = 0; row < numrows(); ++row) {
        growcols(row, C);
      }
      return;
    }

    // assings the values for rows and columns to the new value
    for (int row = 0; row < R; ++row) {
      newR[row].Cols = new T[C];
      newR[row].NumCols = C;
      for (int col = 0; col < C; ++col) {
        newR[row].Cols[col] = T{};
      }
    }

    // places the values to the growed matrix
    for (int row = 0; row < NumRows; ++row) {
      for (int col = 0; col < Rows[row].NumCols; ++col)
        if (Rows[row].Cols[col] != 0) {
          newR[row].Cols[col] = Rows[row].Cols[col];
        }
    }
    Rows = newR;
    NumRows = R;
  }

  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const {

    int sum = 0;
    for (int row = 0; row < NumRows; ++row) {
      sum += Rows[row].NumCols; // Sum now stores all the elements in the matrix
    }

    return sum; // returns the # of element in the matrix
  }

  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T &at(int row, int col) const {
    if (row < 0 || row >= NumRows)
      throw std::invalid_argument("mymatrix::at: row");
    if (col < 0 || col >= Rows[row].NumCols)
      throw std::invalid_argument("mymatrix::at: col");

    return Rows[row].Cols[col]; // returns the location (rows,col)
  }

  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T &operator()(int row, int col) const {
    if (row < 0 || row >= NumRows)
      throw std::invalid_argument("mymatrix::(): row");
    if (col < 0 || col >= Rows[row].NumCols)
      throw std::invalid_argument("mymatrix::(): col");

    return at(row, col); // returns the element that is accesed
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar) {
    mymatrix<T> result;

    result.Rows = new ROW[NumRows];
    result.NumRows = NumRows;

    // iterates through the values in the row and column
    for (int row = 0; row < numrows(); ++row) {
      result.Rows[row].Cols = new T[Rows[row].NumCols];
      result.Rows[row].NumCols = Rows[row].NumCols;

      // multiplies the conctant number with the matrix
      for (int col = 0; col < numcols(row); ++col) {
        result.Rows[row].Cols[col] = Rows[row].Cols[col] * scalar;
      }
    }
    return result;
  }

  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  mymatrix<T> operator*(const mymatrix<T> &other) {

    // Checks to see if the columns are the same, shouldn't be different
    int num = -1;
    for (int row = 0; row < NumRows; ++row) {
      if (Rows[row].NumCols != Rows[0].NumCols) {
        num = 1;
      }
    }

    // Checks to see if the row are the same, shouldn't be different
    int num1 = -1;
    for (int row = 0; row < other.NumRows; ++row) {
      if (other.Rows[row].NumCols != other.Rows[0].NumCols) {
        num1 = 1;
      }
    }
    if (numcols(0) != other.numrows()) {
      throw std::runtime_error("mymatrix::*: size mismatch");
    }
    if (num > 0 || num1 > 0) {
      throw std::runtime_error("mymatrix::*: this not rectangular");
    }

    mymatrix<T> result(NumRows, other.Rows->NumCols);

    // Once the matrices are rectangular then the matricces get multiplied Rows
    // *Columns
    for (int row = 0; row < NumRows; ++row) {
      for (int i = 0; i < other.Rows[0].NumCols; i++) {
        for (int col = 0; col < Rows[row].NumCols; ++col) {
          result.Rows[row].Cols[i] +=
              Rows[row].Cols[col] * other.Rows[col].Cols[i];
        }
      }
    }

    return result;
  }

  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output() {
    for (int row = 0; row < this->NumRows; ++row) {
      for (int col = 0; col < this->Rows[row].NumCols; ++col) {
        cout << this->Rows[row].Cols[col] << " ";
      }
      cout << endl;
    }
  }
};