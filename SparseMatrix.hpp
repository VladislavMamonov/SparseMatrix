#pragma once

#include <iostream>
#include <list>

using namespace std;


struct coo_matrix
{
  list<int> rows;
  list<int> cols;
  list<double> value;
};

struct csr_matrix
{
  int row, col, arr_size = 0;
  double **csr_matrix;
  double *value;
  int *col_index;
  int *row_indexing;
};

struct csc_matrix
{
  int row, col, arr_size = 0;
  double **csc_matrix;
  double *value;
  int *row_index;
  int *col_indexing;
};


struct dia_matrix
{
  int row, col, arr_size = 0;
  double **dia_matrix;
  double *value;
  int *offsets;
};

coo_matrix init_coo(coo_matrix coo_matrix, int row, int col);
csr_matrix init_csr(csr_matrix csr_matrix);
csc_matrix init_csc(csc_matrix csc_matrix);
dia_matrix init_dia(dia_matrix dia_matrix);

csr_matrix coo_to_csr(coo_matrix coo_matrix, csr_matrix csr_matrix);
coo_matrix csr_to_coo(csr_matrix csr_matrix, coo_matrix coo_matrix);
csr_matrix csc_to_csr(csc_matrix csc_matrix, csr_matrix csr_matrix);
dia_matrix csr_to_dia(csr_matrix csr_matrix, dia_matrix dia_matrix);
csr_matrix dia_to_csr(dia_matrix dia_matrix, csr_matrix csr_matrix);

void print_coo_matrix(coo_matrix coo_matrix);
void print_csr_matrix(csr_matrix csr_matrix);
void print_csc_matrix(csc_matrix csc_matrix);
void print_dia_matrix(dia_matrix dia_matrix);

int coo_sparse_check(coo_matrix coo_matrix, int row, int col);
int csr_sparse_check(csr_matrix csr_matrix);
int dia_sparse_check(dia_matrix dia_matrix);
