#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

const std::string INPUT_FILE_NAME = "students.txt";

typedef std::string *NamePtr;    // a student name
typedef std::string *NameArray;  // dynamic array of student names
typedef int *ScorePtr;           // a score
typedef int *ScoreRow;           // dynamic array (row) of student scores
typedef ScoreRow *RowArray;      // dynamic array of pointers to scores rows
typedef ScoreRow *RowPtr;        // a pointer to a score row

/*
Read a student's assignment scores and fill
the dynamic integer array (row) of the scores
@param input the input stream
@param score_count the count of scores for this student
@param row_ptr the pointer to the score row
*/
void fill_score_row(std::ifstream &input, int score_count, const RowPtr row_ptr) {
  ScorePtr score_ptr = *row_ptr; // first score of the row
  // Loop once per assignment score of the student
  while (score_count > 0) {
    input >> *score_ptr; // read the next score into the score row
    score_ptr++; // next score of the row
    score_count--; // decrement the copy of the score count
  }

  *score_ptr = -1; // sentinel to mark the end of this score row
}

/*
Fill the dynamic array of student names and the dynamic array of pointers to the score rows
@param input the input stream
@param student_count the count of students
@param names the dynamic array of student names
@param rows the dynamic array of pointers to the score rows
*/
void fill_dynamic_arrays(std::ifstream &input, int student_count, const NameArray names, const RowArray rows) {
  int score_count;
  std::string first_name, last_name;
  NamePtr name_ptr = names; // first name of the names array
  RowPtr row_ptr = rows; // first pointer to the score rows

  // Loop once per student
  while (student_count > 0) {
    // Read a student name and the number of assignments
    // Use name_ptr to enter the name into the name array
    input >> first_name >> last_name >> score_count;
    *name_ptr = first_name + " " + last_name;

    // Create a dynamic integer array as a row of student scores
    // Make it one larger for the -1 sentinel as the end. Fill the array
    *row_ptr = new int[score_count + 1];
    fill_score_row(input, score_count, row_ptr);

    name_ptr++; // next element of the name array
    row_ptr++; // next element of the row array
    student_count--; // decrement the copy of the student count
  }
}

/*
Read the course name and the count of students.
Create dynamic arrays for the student names and scores
@param input the input file stream
@param course the course name
@param names the dynamic array of names
@param rows the dynamic array of pointers to the rows of scores
@return the count of students
*/
int create_dynamic_arrays(std::ifstream &input, std::string &course, NameArray &names, RowArray &rows) {
  int student_count;

  // Read the course name and student count
  // Create the dynamic array of student names and the dynamic array of pointers
  // to the rows of student acores
  input >> course >> student_count;
  names = new std::string[student_count];
  rows = new ScoreRow[student_count];

  // Create the dynamic array of pointers
  // to the rows of student scores
  fill_dynamic_arrays(input, student_count, names, rows);

  return student_count;
}

void delete_dynamic_arrays(int student_count, NameArray names, RowArray rows) {
  RowPtr row_ptr = rows; // the first row pointer

  // Loop once per row of student scores
  while (student_count > 0) {
    delete[] *row_ptr; // delete the row of scores
    row_ptr++; // next pointer to a score row
    student_count--; // decrement the copy of the student count
  }
  delete[] rows; // delete the array of row pointers
  delete[] names; // delete the array of names
}

/*
Print the scores for each student in the course
@param course the name of the score
@param names the dynamic array of students names
@param rows the dynamic array of pointers to the scores
*/
void print_student_scores(const std::string course, int student_count, const NameArray names, const RowArray rows) {
  NamePtr name_ptr = names; // print the students name
  RowPtr row_ptr = rows; // first score of the row

  std::cout << "STUDENT SCORES for " << course << std::endl;

  // Loop once per row of student scores
  while (student_count > 0) {
    std::cout << std::endl;
    std::cout << *name_ptr << std::endl; // print the students name

    int *score_ptr = *row_ptr; // first score of the row

    // No scores?
    if (*score_ptr < 0) {
      std::cout << "  (none)";
    // Else loop to print each score in the row
    // Stop at the -1 sentinel
    } else {
      while (*score_ptr >= 0) {
        std::cout << std::setw(5) << *score_ptr;
        score_ptr ++; // nest score of the row
      }
      std::cout << std::endl;
    }
    name_ptr++; // next name in the name array
    row_ptr++; // next pointer to a score row
    student_count--; // decrement the copy of the student count
  }
}

int main() {
  std::ifstream input;
  input.open(INPUT_FILE_NAME);
  if (input.fail()) {
    std::cout << "Failed to open " << INPUT_FILE_NAME << std::endl;
    return -1;
  }

  std::string course;
  NameArray names = nullptr; // array of student names
  RowArray rows = nullptr; // array of pointers to the row of student scores

  int student_count = create_dynamic_arrays(input, course, names, rows);
  print_student_scores(course, student_count, names, rows);
  delete_dynamic_arrays(student_count, names, rows);
}
