#include <iostream>
#include <iomanip>

typedef int *TableRow;
typedef TableRow *RowArray;

RowArray make_mult_table(const int row_count, const int col_count) {
  RowArray rows = new TableRow[row_count];

  for (int r=0; r<row_count; ++r) {
    rows[r] = new int[col_count];
    for (int c=0; c<col_count; ++c) {
      rows[r][c] = (r+1)*(c+1);
    }
  }

  return rows;
}

void print_table(RowArray& rows, const int row_count, const int col_count) {
  for (int r=0; r<row_count; ++r) {
    TableRow row = rows[r];
    for (int c=0; c<col_count; ++c) {
      std::cout << std::setw(3) << row[c];
    }
    std::cout << std::endl;
  }
}

void delete_table(RowArray& rows, const int row_count, const int col_count) {
  for (int r=0; r<row_count; ++r) {
    delete[] rows[r];
  }
  delete[] rows;
}

int main() {
  RowArray table = make_mult_table(3, 4);
  print_table(table, 3, 4);
  delete_table(table, 3, 4);
}
