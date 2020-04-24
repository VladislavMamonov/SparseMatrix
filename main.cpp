#include "SparseMatrix.hpp"


int main()
{
  dia_matrix dia_matrix;
  csr_matrix csr_matrix;

  csr_matrix = init_csr(csr_matrix);
  print_csr_matrix(csr_matrix);

  dia_matrix = csr_to_dia(csr_matrix, dia_matrix);
  print_dia_matrix(dia_matrix);

  return 0;
}
