#include <iostream>
#include <iomanip>

int main() {
  for (int i=1; i<=2; ++i) {
    for (int j=10; j<=12; ++j) {
      std::cout << "i = " << std::setw(1) << i << ", j = " << std::setw(2) << j << std::endl;
    }
  }
}
