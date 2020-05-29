#include "SparseMatrix.hpp"


void interface_print()
{
  cout << "1. COO to CSR" << endl;
  cout << "2. CSR to COO" << endl;
  cout << "3. CSR to CSC" << endl;
  cout << "4. CSC to CSR" << endl;
  cout << "5. CSR to DIA" << endl;
  cout << "6. DIA to CSR" << endl;
  cout << "Any key to exit" << endl << endl;
  cout << "Selection: ";
}


int main()
{
  bool isExit = false;
  int selection;

  cout << "------------------------------" << endl;
  cout << "Sparse matrix format converter" << endl;
  cout << "------------------------------" << endl << endl;

  while (isExit == false)
  {
    interface_print();
    cin >> selection;

    if (selection < 1 || selection > 6)
      isExit = true;

    if (selection == 1) {
      coo_matrix coo_matrix;
      csr_matrix csr_matrix;

      coo_matrix = init_coo(coo_matrix);
      cout << "SOURCE MATRIX: " << endl;
      print_coo_matrix(coo_matrix);
      cout << endl << endl;

      csr_matrix = coo_to_csr(coo_matrix, csr_matrix);
      cout << "CONVERTED MATRIX:" << endl;
      print_csr_matrix(csr_matrix);
      cout << endl << endl;
    }

    if (selection == 2) {
      coo_matrix coo_matrix;
      csr_matrix csr_matrix;

      csr_matrix = init_csr(csr_matrix);
      cout << "SOURCE MATRIX: " << endl;
      print_csr_matrix(csr_matrix);
      cout << endl << endl;

      coo_matrix = csr_to_coo(csr_matrix, coo_matrix);
      cout << "CONVERTED MATRIX:" << endl;
      print_coo_matrix(coo_matrix);
      cout << endl << endl;
    }

    if (selection == 3) {
      csc_matrix csc_matrix;
      csr_matrix csr_matrix;

      csr_matrix = init_csr(csr_matrix);
      cout << "SOURCE MATRIX: " << endl;
      print_csr_matrix(csr_matrix);
      cout << endl << endl;

      csc_matrix = csr_to_csc(csr_matrix, csc_matrix);
      cout << "CONVERTED MATRIX:" << endl;
      print_csc_matrix(csc_matrix);
      cout << endl << endl;
    }

    if (selection == 4) {
      csc_matrix csc_matrix;
      csr_matrix csr_matrix;

      csc_matrix = init_csc(csc_matrix);
      cout << "SOURCE MATRIX: " << endl;
      print_csc_matrix(csc_matrix);
      cout << endl << endl;

      csr_matrix = csc_to_csr(csc_matrix, csr_matrix);
      cout << "CONVERTED MATRIX:" << endl;
      print_csr_matrix(csr_matrix);
      cout << endl << endl;
    }

    if (selection == 5) {
      dia_matrix dia_matrix;
      csr_matrix csr_matrix;

      csr_matrix = init_csr(csr_matrix);
      cout << "SOURCE MATRIX: " << endl;
      print_csr_matrix(csr_matrix);
      cout << endl << endl;

      dia_matrix = csr_to_dia(csr_matrix, dia_matrix);
      cout << "CONVERTED MATRIX:" << endl;
      print_dia_matrix(dia_matrix);
      cout << endl << endl;
    }

    if (selection == 6) {
      dia_matrix dia_matrix;
      csr_matrix csr_matrix;

      cout << endl << "!!! Excess elements assume value 0 !!!" << endl;
      cout << "!!! First positive offsets and then negative !!!" << endl << endl;

      dia_matrix = init_dia(dia_matrix);
      cout << "SOURCE MATRIX: " << endl;
      print_dia_matrix(dia_matrix);
      cout << endl << endl;

      csr_matrix = dia_to_csr(dia_matrix, csr_matrix);
      cout << "CONVERTED MATRIX:" << endl;
      print_csr_matrix(csr_matrix);
      cout << endl << endl;
    }
  }

  return 0;
}
