#include "SparseMatrix.hpp"


csr_matrix coo_to_csr(coo_matrix coo_matrix, csr_matrix csr_matrix)
{
  csr_matrix.row = 0;

  for (auto i = coo_matrix.rows.begin(); i != coo_matrix.rows.end(); i++) {
    if (*i > (*i - 1)) csr_matrix.row = *i;
    csr_matrix.arr_size++;
  }

  csr_matrix.row += 1;
  csr_matrix.value = new double[csr_matrix.arr_size];
  csr_matrix.col_index = new int[csr_matrix.arr_size];
  csr_matrix.row_indexing = new int[csr_matrix.row + 1];
  csr_matrix.row_indexing[0] = 0;

  int k = 0;
  for (auto i = coo_matrix.value.begin(); i != coo_matrix.value.end(); i++) {
    csr_matrix.value[k] = *i;
    k++;
  }

  k = 0;
  for (auto i = coo_matrix.cols.begin(); i != coo_matrix.cols.end(); i++) {
    csr_matrix.col_index[k] = *i;
    k++;
  }

  int nonzero_counter = 0;
  int index = 1;
  int c = 0;
  int coo_rows_temp[csr_matrix.arr_size];
  bool empty_row = false;
  int empty_row_qt = 0;

  for (auto i = coo_matrix.rows.begin(); i != coo_matrix.rows.end(); i++) {
    coo_rows_temp[c] = *i; c++;
  }

  for (int i = 0; i < csr_matrix.arr_size; i++)
  {
    if (i == 0 && coo_rows_temp[i] != 0) {
      for (int j = 0; j < coo_rows_temp[i]; j++) {
        csr_matrix.row_indexing[index] = nonzero_counter;
        index++;
      }
    }

    if (coo_rows_temp[i] == coo_rows_temp[i + 1]) {
      nonzero_counter++;
      continue;
    }

    if (empty_row == false) nonzero_counter++;

    if (coo_rows_temp[i + 1] != coo_rows_temp[i] + 1
      && i != csr_matrix.arr_size - 1 && empty_row == false) {
      empty_row_qt = (coo_rows_temp[i + 1] - 1) - coo_rows_temp[i];
      for (int j = 0; j < empty_row_qt; j++) {
        csr_matrix.row_indexing[index] = nonzero_counter;
        index++;
      }
      empty_row = true;
      i--;
      continue;
    }

    csr_matrix.row_indexing[index] = nonzero_counter;
    index++;
    empty_row = false;
  }

  return csr_matrix;
}


coo_matrix csr_to_coo(csr_matrix csr_matrix, coo_matrix coo_matrix)
{
  for (int i = 0; i < csr_matrix.arr_size; i++) {
    coo_matrix.value.push_back(csr_matrix.value[i]);
    coo_matrix.cols.push_back(csr_matrix.col_index[i]);
  }

  int rows_count = 0;

  for (int i = 0; i < csr_matrix.row; i++) {
    rows_count = csr_matrix.row_indexing[i + 1] - csr_matrix.row_indexing[i];
    for (int j = 0; j < rows_count; j++)
      coo_matrix.rows.push_back(i);
  }

  return coo_matrix;
}


csc_matrix csr_to_csc(csr_matrix csr_matrix, csc_matrix csc_matrix)
{
  csc_matrix.arr_size = csr_matrix.arr_size;
  csc_matrix.row = csr_matrix.row;
  csc_matrix.col = csr_matrix.col;

  csc_matrix.value = new double[csc_matrix.arr_size];
  csc_matrix.row_index = new int[csc_matrix.arr_size];
  csc_matrix.col_indexing = new int[csc_matrix.col + 1];
  csc_matrix.csc_matrix = new double* [csc_matrix.row];

  for (int i = 0; i < csc_matrix.row; i++)
    csc_matrix.csc_matrix[i] = new double[csc_matrix.col];

  int index = 0;

  for (int i = 1; i < csr_matrix.row + 1; i++) {
    int items_per_row = csr_matrix.row_indexing[i] - csr_matrix.row_indexing[i - 1];
    for (int k = 0, j = 0; k < items_per_row; k++) {
      j = csr_matrix.col_index[index];
      csc_matrix.csc_matrix[i - 1][j] = csr_matrix.value[index];
      index++;
    }
  }

  csc_matrix = simpleM_to_csc(csc_matrix);

  return csc_matrix;
}


csr_matrix csc_to_csr(csc_matrix csc_matrix, csr_matrix csr_matrix)
{
  csr_matrix.arr_size = csc_matrix.arr_size;
  csr_matrix.row = csc_matrix.row;
  csr_matrix.col = csc_matrix.col;

  csr_matrix.value = new double[csr_matrix.arr_size];
  csr_matrix.col_index = new int[csr_matrix.arr_size];
  csr_matrix.row_indexing = new int[csr_matrix.row + 1];
  csr_matrix.csr_matrix = new double* [csr_matrix.row];

  for (int i = 0; i < csr_matrix.row; i++)
    csr_matrix.csr_matrix[i] = new double[csr_matrix.col];

  int index = 0;

  for (int j = 1; j < csc_matrix.col + 1; j++) {
    int items_per_col = csc_matrix.col_indexing[j] - csc_matrix.col_indexing[j - 1];
    for (int k = 0, i = 0; k < items_per_col; k++) {
      i = csc_matrix.row_index[index];
      csr_matrix.csr_matrix[i][j - 1] = csc_matrix.value[index];
      index++;
    }
  }

  csr_matrix = simpleM_to_csr(csr_matrix);

  return csr_matrix;
}


dia_matrix csr_to_dia(csr_matrix csr_matrix, dia_matrix dia_matrix)
{
  int index = 0;
  dia_matrix.row = csr_matrix.row;
  dia_matrix.col = csr_matrix.col;

  for (int i = 1; i < csr_matrix.row + 1; i++) {
    while (index < csr_matrix.row_indexing[i]) {
      if (csr_matrix.col_index[index] == 0 || i == 1)
        dia_matrix.arr_size++;
      index++;
    }
  }

  dia_matrix.offsets = new int[dia_matrix.arr_size];
  dia_matrix.value = new double[dia_matrix.arr_size * dia_matrix.col];
  dia_matrix.dia_matrix = new double* [dia_matrix.row];

  for (int i = 0; i < dia_matrix.row; i++)
    dia_matrix.dia_matrix[i] = new double[dia_matrix.col];

  index = 0;

  for (int i = 1; i < csr_matrix.row + 1; i++) {
    int items_per_row = csr_matrix.row_indexing[i] - csr_matrix.row_indexing[i - 1];
    for (int k = 0, j = 0; k < items_per_row; k++) {
      j = csr_matrix.col_index[index];
      dia_matrix.dia_matrix[i - 1][j] = csr_matrix.value[index];
      index++;
    }
  }

  dia_matrix = simpleM_to_dia(dia_matrix);

  return dia_matrix;
}


csr_matrix dia_to_csr(dia_matrix dia_matrix, csr_matrix csr_matrix)
{
  csr_matrix.row = dia_matrix.row;
  csr_matrix.col = dia_matrix.col;

  for (int i = 0; i < dia_matrix.arr_size * dia_matrix.col; i++)
    if (dia_matrix.value[i] != 0) csr_matrix.arr_size++;

  csr_matrix.value = new double[csr_matrix.arr_size];
  csr_matrix.col_index = new int[csr_matrix.arr_size];
  csr_matrix.row_indexing = new int[csr_matrix.row + 1];
  csr_matrix.csr_matrix = new double* [csr_matrix.row];

  for (int i = 0; i < csr_matrix.row; i++)
    csr_matrix.csr_matrix[i] = new double[csr_matrix.col];

  int index = 0;
  int k = 0;

  for (k = 0; dia_matrix.offsets[k] >= 0 && k < dia_matrix.arr_size; k++)
  {
    int j = dia_matrix.offsets[k];
    for (int i = 0; i < dia_matrix.col - dia_matrix.offsets[k]; i++) {
      if (dia_matrix.value[index] == 0) {
        index++;
        i--;
        continue;
      }
      csr_matrix.csr_matrix[i][j] = dia_matrix.value[index];
      j++;
      index++;
    }
  }

  for (; k < dia_matrix.arr_size; k++)
  {
    for (int i = -dia_matrix.offsets[k], j = 0; i < dia_matrix.row; i++, j++) {
      if (dia_matrix.value[index] == 0) {
        index++;
        i--;
        j--;
        continue;
      }
      csr_matrix.csr_matrix[i][j] = dia_matrix.value[index];
      index++;
    }
  }

  csr_matrix = simpleM_to_csr(csr_matrix);

  return csr_matrix;
}
