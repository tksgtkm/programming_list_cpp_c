#include <iostream>

void swap_by_value(int a, int b) {
  int temp = a;
  a = b;
  b = temp;
}

void swap_by_reference(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  int i = 1, j = 5;
  std::cout << "Before swap_by_value: i = " << i << ", j = " << j << std::endl;
  swap_by_value(i, j);
  std::cout << "After swap_by_value: i = " << i << ", j = " << j << std::endl;
  std::cout << std::endl;
  std::cout << "Before swap_by_reference: i = " << i << ", j = " << j << std::endl;
  swap_by_reference(i, j);
  std::cout << "After swap_by_reference: i = " << i << ", j = " << j << std::endl;
}
