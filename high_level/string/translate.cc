#include <iostream>
#include <string>

std::string translate_ones(int n) {
  switch (n) {
    case 1: return "one";
    case 2: return "two";
    case 3: return "three";
    case 4: return "four";
    case 5: return "five";
    case 6: return "six";
    case 7: return "seven";
    case 8: return "eight";
    case 9: return "nine";
    default: return "???";
  }
}

std::string translate_teens(int n) {
  switch (n) {
    case 11: return "eleven";
    case 12: return "twelve";
    case 13: return "thirteen";
    case 14: return "fourteen";
    case 15: return "fifteen";
    case 16: return "sixteen";
    case 17: return "seventeen";
    case 18: return "eighteen";
    case 19: return "nineteen";
    default: return "???";
  }
}

std::string translate_tens(int n) {
  switch (n) {
    case 0: return "";
    case 1: return "ten";
    case 2: return "twenty";
    case 3: return "thirty";
    case 4: return "fourty";
    case 5: return "fifty";
    case 6: return "sixty";
    case 7: return "seventy";
    case 8: return "eighty";
    case 9: return "ninety";
    default: return "???";
  }
}

std::string translate_hundreds(int n) {
  return translate_ones(n) + " hundred ";
}

std::string translate(int n) {
  std::string words = "";
  int hundreds = n/100;

  if (hundreds > 9) {
    return "??? number too big";
  }

  if (hundreds > 0) {
    words += translate_hundreds(hundreds);
    n %= 100;
  }

  if ((n >= 11) && (n <= 19)) {
    words += translate_teens(n);
  } else {
    int tens = n/10;
    words += translate_tens(tens);
    n %= 10;
    if (n > 0)
      words += " " + translate_ones(n);
  }

  return words;
}

int main() {
  int number;

  do {
    std::cout << "Number? " << std::endl;
    std::cin >> number;

    if (number > 0) {
      std::cout << number << " : " << translate(number) << std::endl;
    }
  } while (number > 0);

  std::cout << "Done!!" << std::endl;
}
