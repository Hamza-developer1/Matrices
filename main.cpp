#include "mymatrix.h"
#include <iostream>

using namespace std;

// This function tests if the at() function works. at() should allow to edit the
// contents inside the matrix
bool at_testing() {
  mymatrix<int> M(2, 2);

  M.at(0, 0) = 1;
  M.at(0, 1) = 1;
  M.at(1, 0) = 1;
  M.at(1, 1) = 1;
  if (M.at(0, 0) != 1 || M.at(0, 1) != 1 || M.at(1, 0) != 1 ||
      M.at(1, 1) != 1) {
    cout << "The at() function fails" << endl;
    return false;
  } else {
    return true;
  }
}
// This function checks to see if the values are parametrized correctly for both
// the int and doubble matrix I set the value to the the 2x2 matrix
bool param() {
  mymatrix<int> M(2, 2);
  mymatrix<double> S(2, 2);
  // values for int
  M.at(0, 0) = 1;
  M.at(0, 1) = 1;
  M.at(1, 0) = 1;
  M.at(1, 1) = 1;
  // values for double
  S.at(0, 0) = 1;
  S.at(0, 1) = 1;
  S.at(1, 0) = 1;
  S.at(1, 1) = 1;
  if (S.at(0, 0) != 1.0 || S.at(0, 1) != 1.0 || S.at(1, 0) != 1.0 ||
      S.at(1, 1) != 1.0) {
    cout << "Matrix did not paramatrize correctly" << endl;
    return false;
  }

  if (M.at(0, 0) != 1 || M.at(0, 1) != 1 || M.at(1, 0) != 1 ||
      M.at(1, 1) != 1) {
    cout << "Matrix did not paramatrize correctly" << endl;
    return false;
  } else {
    return true;
  }
}

// To test the scalar multiplication I tested on a 2x2 matrix and testing both
// int and double data types. I multiply by 2 to each matrix and if it gives the
// correct answer the function returns true
//  if it gives the wrong answer the function returns false
bool scalar_test() {
  mymatrix<int> M(2, 2);
  M.at(0, 0) = 1;
  M.at(0, 1) = 1;
  M.at(1, 0) = 1;
  M.at(1, 1) = 1;
  mymatrix<int> B = M * 2;
  mymatrix<double> A(2, 2);
  A.at(0, 0) = 1.0;
  A.at(0, 1) = 1.0;
  A.at(1, 0) = 1.0;
  A.at(1, 1) = 1.0;
  mymatrix<double> X = A * 2.0;
  // testing int
  if (B.at(0, 0) != 2 || B.at(0, 1) != 2 || B.at(1, 0) != 2 ||
      B.at(1, 1) != 2) {
    cout << "Scaler Multiplacation is wrong" << endl;
    return false;
  }
  // testing double
  if (X.at(0, 0) != 2.0 || X.at(0, 1) != 2.0 || X.at(1, 0) != 2.0 ||
      X.at(1, 1) != 2.0) {
    cout << "Scaler Multiplacation is wrong" << endl;
    return false;
  } else {
    return true;
  }
}
// This function tests to see if the contents of a matrix was succesfully copied
// on to
// another matrix
bool copyTest() {
  mymatrix<int> M;
  mymatrix<int> S(M);
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      if (M.at(r, c) != S.at(r, c))
        return false;
    }
  }
  return true;
}

// This function checks to see if the dulat 4x4 matrix was created succesfully
// If it is then the # of elements should be 16
bool defaultTest() {
  // creates 4x4 matrix
  mymatrix<int> M;

  if (M.size() == 16)
    return true;
  else
    return false;
}

// This function test to see if the number of rows is the same as the default
// number of rows 4
bool test_numRows() {
  mymatrix<int> M;

  if (M.numrows() == 4)
    return true;
  else
    return false;
}

// This function test to see if the number of columns is the same as the default
// number of columns 4
bool test_NumCols(int row) {
  mymatrix<int> M;

  if (M.numcols(row) == 4)
    return true;
  else
    return false;
}

// This function tests to see if the number of columns changed to 4, if it did
// change to 4 from
//  2 then returns true if not returns false
bool growCols_test() {
  mymatrix<int> M;
  M.growcols(2, 4);
  if (M.numcols(2) == 4)
    return true;
  else
    return false;
}

// This function grows the matrix and makes sure it can grow that size. You cna
// either grow the columns or rows
bool growingMatrix() {
  mymatrix<int> M(2, 2);

  M.at(0, 0) = 1;
  M.at(0, 1) = 1;
  M.at(1, 0) = 1;
  M.at(1, 1) = 1;

  M.grow(3, 4);

  // check the new size
  if (M.size() != 3 * 4) {
    cout << "failed to grow matrix" << endl;
    return false;
  } else {
    return true;
  }
}

// This function checks to see if the grow function shouldn't be used in this
// circumstance
//  because the # of rows and columns should never be reduced
bool grow_invlid() {
  mymatrix<int> M(2, 2);

  M.at(0, 0) = 1;
  M.at(0, 1) = 1;
  M.at(1, 0) = 1;
  M.at(1, 1) = 1;

  M.grow(1, 1);

  // check the new size
  if (M.size() == 1 * 1) {
    cout << "failed to grow matrix" << endl;
    return false;
  } else {
    return true;
  }
}
// This function tests to see if the #of elements inside a matrix is correct or
// not
bool test_size() {
  mymatrix<int> M(2, 2);

  M.at(0, 0) = 1;
  M.at(0, 1) = 1;
  M.at(1, 0) = 1;
  M.at(1, 1) = 1;
  if (M.size() == 4)
    return true;
  else
    return false;
}

// This functions checks to see if jeggaed matrices are being multiplied if it
// is then it returns false if not thne it returns true. Also means the first
// matrix is jagged
bool jagged_Multiply1() {
  try {
    mymatrix<int> M1;
    mymatrix<int> M2;

    M1.growcols(3, 16);

    mymatrix<int> result;

    result = M1 * M2;
    // matrix multiply should throw an exception

    // if we get here
    // no exception was thrown --- error
    cout << "matrix multiply test failed: "
         << "jagged matrix did not throw exception" << endl;
    return false;
  } catch (...) {
    return true;
    // if we get here,
    // exception was thrown --- correct
  }
}

// This functions checks to see if jeggaed matrices are being multiplied if it
// is then it returns false if not thne it returns true. Also means the second
// matrix is jagged
bool jagged_Multiply2() {
  try {
    mymatrix<int> M1;
    mymatrix<int> M2;

    M2.growcols(3, 16);

    mymatrix<int> result;

    result = M1 * M2;
    // matrix multiply should throw an exception

    // if we get here
    // no exception was thrown --- error
    cout << "matrix multiply test failed: "
         << "jagged matrix did not throw exception" << endl;
    return false;
  } catch (...) {
    return true;
    // if we get here,
    // exception was thrown --- correct
  }
}

// This function allows for the valid matrix multiplcation to take place only
// when the opposing columns
//  match with the opposing rows of both matrix. For example 1x1 times 2x1 works
bool correctMultiply() {
  mymatrix<int> M(1, 1);

  M.at(0, 0) = 1;

  mymatrix<int> S(1, 2);

  // set values
  S.at(0, 0) = 5;
  S.at(0, 1) = 6;

  // perform matrix multiplication
  mymatrix<int> X = M * S;

  // check result
  if (X.size() != 1 * 2) {
    cout << "Matrix multiplication test failed: wrong size" << endl;
    return false;
  } else {
    return true;
  }
}
// This function doesn't allow invalid matrix multiplcation to take place only
// when the opposing columns
//  match with the opposing rows of both matrix. For example 1x2 times 1x1  does
//  not work
bool incorrectMultiply() {
  try {

    mymatrix<int> M(1, 1);

    M.at(0, 0) = 1;

    mymatrix<int> S(1, 2);

    // set values
    S.at(0, 0) = 5;
    S.at(0, 1) = 6;

    // perform matrix multiplication
    mymatrix<int> X = S * M;

    // check result
    if (X.size() != 1 * 2) {
      cout << "cannot multiply" << endl;
      return false;
    }
  } catch (...) {
    return true;
  }
}

int main() {
  int passed = 0;
  int failed = 0;

  if (defaultTest())
    passed++;
  else {
    cout << "default failed" << endl;
    failed++;
  }

  if (test_NumCols(0))
    passed++;
  else {
    cout << "numcols failed" << endl;
    failed++;
  }

  if (param())
    passed++;
  else {
    cout << "parmatrize failed" << endl;
    failed++;
  }
  if (test_numRows())
    passed++;
  else {
    cout << "numrows failed" << endl;
    failed++;
  }

  if (copyTest())
    passed++;
  else {
    cout << "copy failed" << endl;
    failed++;
  }

  if (growCols_test())
    passed++;
  else {
    cout << "growcols failed" << endl;
    failed++;
  }

  if (growingMatrix())
    passed++;
  else {
    cout << "growingMatrix failed" << endl;
    failed++;
  }

  if (scalar_test())
    passed++;

  else {
    cout << "scalar failed" << endl;
    failed++;
  }
  if (at_testing())
    passed++;

  else {
    cout << "The at() function fails" << endl;
    failed++;
  }
  if (grow_invlid())
    passed++;

  else {
    cout << "growInvalid fails" << endl;
    failed++;
  }
  if (test_size())
    passed++;

  else {
    cout << "growInvalid fails" << endl;
    failed++;
  }
  if (jagged_Multiply1())
    passed++;

  else {
    cout << "jagged matrix" << endl;
    failed++;
  }
  if (jagged_Multiply2())
    passed++;

  else {
    cout << "jagged matrix" << endl;
    failed++;
  }
  if (correctMultiply())
    passed++;

  else {
    cout << "cannot multiply" << endl;
    failed++;
  }
  if (incorrectMultiply())
    passed++;

  else {
    cout << "can multiply" << endl;
    failed++;
  }

  cout << "Tests passed: " << passed << endl;
  cout << "Tests failed: " << failed << endl;
  return 0;
}