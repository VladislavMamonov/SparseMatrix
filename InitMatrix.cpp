#include "SparseMatrix.hpp"


void print_coo_matrix(coo_matrix coo_matrix)
{
  cout << "List of rows: { ";
  for (auto i = coo_matrix.rows.begin(); i != coo_matrix.rows.end(); i++) {
    cout << *i << " ";
  }
  cout << "}" << endl;

  cout << "List of column: { ";
  for (auto i = coo_matrix.cols.begin(); i != coo_matrix.cols.end(); i++) {
    cout << *i << " ";
  }
  cout << "}" << endl;

  cout << "List of values: { ";
  for (auto i = coo_matrix.value.begin(); i != coo_matrix.value.end(); i++) {
    cout << *i << " ";
  }
  cout << "}" << endl;
}


void print_csr_matrix(csr_matrix csr_matrix)
{
  cout << "Array of values: { ";
  for (int i = 0; i < csr_matrix.arr_size; i++) {
    cout << csr_matrix.value[i] << " ";
  }
  cout << "}" << endl;

  cout << "Array of column indexes: { ";
  for (int i = 0; i < csr_matrix.arr_size; i++) {
    cout << csr_matrix.col_index[i] << " ";
  }
  cout << "}" << endl;

  cout << "Row indexing array: { ";
  for (int i = 0; i < csr_matrix.row + 1; i++) {
    cout << csr_matrix.row_indexing[i] << " ";
  }
  cout << "}" << endl;
}


void print_csc_matrix(csc_matrix csc_matrix)
{
  cout << "Array of values: { ";
  for (int i = 0; i < csc_matrix.arr_size; i++) {
    cout << csc_matrix.value[i] << " ";
  }
  cout << "}" << endl;

  cout << "Array of row indexes: { ";
  for (int i = 0; i < csc_matrix.arr_size; i++) {
    cout << csc_matrix.row_index[i] << " ";
  }
  cout << "}" << endl;

  cout << "Col indexing array: { ";
  for (int i = 0; i < csc_matrix.col + 1; i++) {
    cout << csc_matrix.col_indexing[i] << " ";
  }
  cout << "}" << endl;
}


void print_dia_matrix(dia_matrix dia_matrix)
{
  cout << "Array of offsets: { ";
  for (int i = 0; i < dia_matrix.arr_size; i++) {
    cout << dia_matrix.offsets[i] << " ";
  }
  cout << "}" << endl;

  cout << "Array of values: { ";
  for (int i = 0; i < dia_matrix.arr_size * dia_matrix.col; i++) {
    cout << dia_matrix.value[i] << " ";
  }
  cout << "}" << endl;
}


int coo_sparse_check(coo_matrix coo_matrix)
{
  auto val = coo_matrix.value.begin();
  int zero_counter = 0;

  for (auto i = coo_matrix.rows.begin(); i != coo_matrix.rows.end(); i++) {
    int c = 0;
    for (auto j = coo_matrix.cols.begin(); c < coo_matrix.col; j++, c++) {
      if (*val == 0) zero_counter++;
      val++;
    }
  }

  if (zero_counter < (coo_matrix.row * coo_matrix.col / 2))
    return 1;

  return 0;
}


int csr_sparse_check(csr_matrix csr_matrix)
{
  int zero_counter = 0;

  for (int i = 0; i < csr_matrix.row; i++)
    for (int j = 0; j < csr_matrix.col; j++)
      if (csr_matrix.csr_matrix[i][j] == 0) zero_counter++;

  if (zero_counter < (csr_matrix.row * csr_matrix.col / 2))
    return 1;

  return 0;
}


int csc_sparse_check(csc_matrix csc_matrix)
{
  int zero_counter = 0;

  for (int i = 0; i < csc_matrix.row; i++)
    for (int j = 0; j < csc_matrix.col; j++)
      if (csc_matrix.csc_matrix[i][j] == 0) zero_counter++;

  if (zero_counter < (csc_matrix.row * csc_matrix.col / 2))
    return 1;

  return 0;
}


int dia_sparse_check(dia_matrix dia_matrix)
{
  int zero_counter = 0;

  for (int i = 0; i < dia_matrix.row; i++)
    for (int j = 0; j < dia_matrix.col; j++)
      if (dia_matrix.dia_matrix[i][j] == 0) zero_counter++;

  if (zero_counter < (dia_matrix.row * dia_matrix.col / 2))
    return 1;

  return 0;
}


coo_matrix init_coo(coo_matrix coo_matrix)
{
  double val;

  cout << "matrix rows: ";
  cin >> coo_matrix.row;
  cout << "matrix cols: ";
  cin >> coo_matrix.col;
  cout << endl;

  cout << "number of nonzero elements: ";
  cin >> coo_matrix.arr_size;
  cout << endl;

  for (int i = 0; i < coo_matrix.arr_size; i++) {
    cout << "row index[" << i << "]: ";
    cin >> val;
    coo_matrix.rows.push_back(val);
  }

  cout << endl;

  for (int i = 0; i < coo_matrix.arr_size; i++) {
    cout << "col index[" << i << "]: ";
    cin >> val;
    coo_matrix.cols.push_back(val);
  }

  cout << endl;

  for (int i = 0; i < coo_matrix.arr_size; i++) {
    cout << "values[" << i << "]: ";
    cin >> val;
    coo_matrix.value.push_back(val);
  }

  cout << endl;

  return coo_matrix;
}


csr_matrix init_csr(csr_matrix csr_matrix)
{
  cout << "matrix rows: ";
  cin >> csr_matrix.row;
  cout << "matrix cols: ";
  cin >> csr_matrix.col;
  cout << endl;

  cout << "number of nonzero elements: ";
  cin >> csr_matrix.arr_size;
  cout << endl;

  csr_matrix.value = new double[csr_matrix.arr_size];
  csr_matrix.col_index = new int[csr_matrix.arr_size];
  csr_matrix.row_indexing = new int[csr_matrix.row + 1];
  csr_matrix.row_indexing[0] = 0;

  for (int i = 0; i < csr_matrix.arr_size; i++) {
    cout << "values[" << i << "]: ";
    cin >> csr_matrix.value[i];
  }

  cout << endl;

  for (int i = 0; i < csr_matrix.arr_size; i++) {
    cout << "cols indexes[" << i << "]: ";
    cin >> csr_matrix.col_index[i];
  }

  cout << endl;

  for (int i = 1; i < csr_matrix.row + 1; i++) {
    cout << "rows indexing[" << i << "]: ";
    cin >> csr_matrix.row_indexing[i];
  }

  cout << endl;

  return csr_matrix;
}


csc_matrix init_csc(csc_matrix csc_matrix)
{
  cout << "matrix rows: ";
  cin >> csc_matrix.row;
  cout << "matrix cols: ";
  cin >> csc_matrix.col;
  cout << endl;

  cout << "number of nonzero elements: ";
  cin >> csc_matrix.arr_size;
  cout << endl;

  csc_matrix.value = new double[csc_matrix.arr_size];
  csc_matrix.row_index = new int[csc_matrix.arr_size];
  csc_matrix.col_indexing = new int[csc_matrix.col + 1];
  csc_matrix.col_indexing[0] = 0;

  for (int i = 0; i < csc_matrix.arr_size; i++) {
    cout << "values[" << i << "]: ";
    cin >> csc_matrix.value[i];
  }

  cout << endl;

  for (int i = 0; i < csc_matrix.arr_size; i++) {
    cout << "rows indexes[" << i << "]: ";
    cin >> csc_matrix.row_index[i];
  }

  cout << endl;

  for (int i = 1; i < csc_matrix.col + 1; i++) {
    cout << "cols indexing[" << i << "]: ";
    cin >> csc_matrix.col_indexing[i];
  }

  cout << endl;

  return csc_matrix;
}


dia_matrix init_dia(dia_matrix dia_matrix)
{
  cout << "matrix rows: ";
  cin >> dia_matrix.row;
  cout << "matrix cols: ";
  cin >> dia_matrix.col;
  cout << endl;

  cout << "number of offsets: ";
  cin >> dia_matrix.arr_size;
  cout << endl;

  dia_matrix.value = new double[dia_matrix.arr_size * dia_matrix.col];
  dia_matrix.offsets = new int[dia_matrix.arr_size];

  for (int i = 0; i < dia_matrix.arr_size; i++) {
    cout << "offsets[" << i << "]: ";
    cin >> dia_matrix.offsets[i];
  }

  cout << endl;

  for (int i = 0; i < dia_matrix.arr_size * dia_matrix.col; i++) {
    cout << "values[" << i << "]: ";
    cin >> dia_matrix.value[i];
  }

  cout << endl;

  return dia_matrix;
}


csr_matrix simpleM_to_csr(csr_matrix csr_matrix)
{
  if (csr_sparse_check(csr_matrix) == 1)
    cout << "matrix is ​​not sparse" << endl << endl;   //Проверка на разреженность

  csr_matrix.row_indexing = new int[csr_matrix.row + 1];
  csr_matrix.row_indexing[0] = 0;

  for (int i = 0, n = 0; i < csr_matrix.row; i++) {
    for (int j = 0; j < csr_matrix.col; j++) {
      if (csr_matrix.csr_matrix[i][j] != 0) {
        csr_matrix.value[n] = csr_matrix.csr_matrix[i][j];
        csr_matrix.col_index[n] = j;
        n++;
      }
    }
    csr_matrix.row_indexing[i + 1] = n;
  }

  return csr_matrix;
}


csc_matrix simpleM_to_csc(csc_matrix csc_matrix)
{
  if (csc_sparse_check(csc_matrix) == 1)
    cout << "matrix is ​​not sparse" << endl << endl;   //Проверка на разреженность

  csc_matrix.col_indexing = new int[csc_matrix.col + 1];
  csc_matrix.col_indexing[0] = 0;

  for (int j = 0, n = 0; j < csc_matrix.col; j++) {
    for (int i = 0; i < csc_matrix.row; i++) {
      if (csc_matrix.csc_matrix[i][j] != 0) {
        csc_matrix.value[n] = csc_matrix.csc_matrix[i][j];
        csc_matrix.row_index[n] = i;
        n++;
      }
    }
    csc_matrix.col_indexing[j + 1] = n;
  }

  return csc_matrix;
}


dia_matrix simpleM_to_dia(dia_matrix dia_matrix)
{
  int offset = 0;
  int value_counter = 0;

  if (dia_sparse_check(dia_matrix) == 1)
    cout << "matrix is ​​not sparse" << endl << endl;   //Проверка на разреженность

  for (int i = 0; i < dia_matrix.col; i++)
  {
    if (dia_matrix.dia_matrix[0][i] != 0)
    {
      if (i != 0) {
        for (int k = 0; k < i; k++) {
          dia_matrix.value[value_counter] = 0;   //заполнение обрезанной диагонали
          value_counter++;
        }
      }

      for (int j = i, row = 0; j < dia_matrix.col; j++, row++) {
        dia_matrix.value[value_counter] = dia_matrix.dia_matrix[row][j];
        value_counter++;
      }

      dia_matrix.offsets[offset] = i;
      offset++;
    }
  }

  for (int i = 1, j = -1; i < dia_matrix.row; i++, j--)
  {
    if (dia_matrix.dia_matrix[i][0] != 0)
    {
      if (i > dia_matrix.row - dia_matrix.col) {
        for (int k = 0; k < i - (dia_matrix.row - dia_matrix.col); k++) {
          dia_matrix.value[value_counter] = 0;
          value_counter++;
        }
      }

      for (int k = i, col = 0; k < dia_matrix.row; k++, col++) {
        dia_matrix.value[value_counter] = dia_matrix.dia_matrix[k][col];
        value_counter++;
      }

      dia_matrix.offsets[offset] = j;
      offset++;
    }
  }

  return dia_matrix;
}
