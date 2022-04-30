#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

// Names to search for
const std::string ALEXEEVICH  = "Makar Alexeevich";
const std::string BAZDEEV     = "Joseph Bazdeev";
const std::string DRUBETSKOY  = "Boris Drubetskoy";

// The full names are listed in alphabetical order.
const std::vector<std::string> FULL_NAMES = {ALEXEEVICH, BAZDEEV, DRUBETSKOY};

const std::string INPUT_FILE_NAME = "WarAndPeace.txt";


void print_name(const int line_number, const int position, const std::string &name) {
  std::cout << std::setw(5) << line_number + 1 << std::setw(10) << position + 1
  << " " << name << std::endl;
}

/*
Split a full name into its first and last names
@param name the full name
@return the first and last names in a vector
*/
std::vector<std::string> split_name(const std::string &name) {
  std::vector<std::string> parts;
  int space_pos = name.find(' '); // position of the space
  parts.push_back(name.substr(0, space_pos)); // first name
  parts.push_back(name.substr(space_pos + 1, name.length())); // last name

  return parts;
}

/*
Search each line of the input file for the names. A name can be split across two lines.
Print the line number and position of each found name.
If there are multiple names in a line, print them in alphabetical order.
@param input the input stream
@param full_names the first and last names
@param first_names the fitst names
@param last_names the last names
@param prev_line_indexes indexes of the first names on the previous line
*/
void search_lines(std::ifstream& input, const std::vector<std::string> &full_names,
  std::vector<std::string> &first_names, std::vector<std::string> &last_names,
  std::vector<int> &prev_line_indexes) {

  std::string line;
  int line_number = 0;

  // Loop over each line of the input file.
  // Function getline() returns false if past the end of the file
  while (std::getline(input, line)) {
    // Loop over each full name to search for it in the line
    for (int i=0; i<full_names.size(); ++i) {
      std::string full_name = full_names.at(i);
      int index;
      // Was the first name at the end of the previous line?
      if (prev_line_indexes.at(i) > 0) {

        // Is the last name at the beginning of the current line?
        std::string last_name = last_names.at(i);
        index = line.find(last_name);

        // If yes, then print the name with the previous line number
        // and the starting position of the first name
        if (index == 0) {
          print_name(line_number - 1, prev_line_indexes.at(i), full_name);
        }
        prev_line_indexes.at(i) = -1;
      }

      // Is the entrie name in this line? If yes, print it.
      index = line.find(full_name);

      // Yes: Print it
      if (index >= 0) {
        print_name(line_number, index, full_name);
      // No: check if just the first name is at end of thie line
      } else {
        std::string first_name = first_names.at(i);
        index = line.find(first_name);
        // Yes it is. Remember the starting index of the first name
        if ((index >= 0) && (index + first_name.length() >= line.length())) {
          prev_line_indexes.at(i) = index;
        }
      }
    }
    line_number++;
  }
}

/*
* Search the input file for the names
* @param input the input stream
* @param names the names
*/
void search_file(std::ifstream &input, const std::vector<std::string> &names) {
  // Maintain vectors first_names, last_names, and prev_line_indexes
  // in parallel the ith entry of each vector is for the ith name.
  // To store first and last names split from the full names.
  std::vector<std::string> first_names, last_names;

  // To store the index of a first name on the previous line
  // if it was at the end of the line.
  std::vector<int> prev_line_indexes;

  // Loop over each name
  for (std::string name : names) {
    // Split each name into its first name and last name
    std::vector<std::string> parts = split_name(name);
    first_names.push_back(parts.at(0));
    last_names.push_back(parts.at(1));
    // Initialize each corresponding previous line index to -1
    prev_line_indexes.push_back(-1);
  }

  std::cout << "LINE POSITION NAME" << std::endl;
  search_lines(input, names, first_names, last_names, prev_line_indexes);
}

int main() {
  std::ifstream input;
  input.open(INPUT_FILE_NAME);
  if (input.fail()) {
    std::cout << "Failed to open " << INPUT_FILE_NAME << std::endl;
    return -1;
  }

  search_file(input, FULL_NAMES);
}
