#include "SparseMatrix.hpp"


int main()
{
  csc_matrix csc_matrix;
  csr_matrix csr_matrix;

  csc_matrix = init_csc(csc_matrix);
  print_csc_matrix(csc_matrix);

  csr_matrix = csc_to_csr(csc_matrix, csr_matrix);
  print_csr_matrix(csr_matrix);

  return 0;
}
