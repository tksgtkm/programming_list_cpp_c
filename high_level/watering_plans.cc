#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

int main() {
  const int UNITS_PER_CAN = 3;

  int plant_count;
  int plant_number;
  int unwatered_count;
  int water_aomunt;
  int steps;
  int cum_steps;
  int cum_step_units_near;
  int cum_step_units_far;
  bool trip_done;

  const std::string INPUT_FILE_NAME = "counts.txt"

  std::ifstream input;
  input.open(INPUT_FILE_NAME);
  if (input.fail()) {
    std::cout << "Failed to open " << INPUT_FILE_NAME << std::endl;
    return -1;
  }

  do {
    input >> plant_count;
    if (plant_count <= 0)
      return 0;

    std::cout << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << "Plan Near with " << plant_count << " plants" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << std::endl;
    std::cout << "Where      Cum. steps  Water amt.  Cum. step-units" << std::endl;
    std::cout << "---------  ----------  ----------  ---------------" << std::endl;

    unwatered_count = plant_count;
    cum_steps = 0;
    cum_step_units_near = 0;

    while (unwatered_count > 0) {
      water_aomunt = UNITS_PER_CAN;
      plant_number = plant_count - unwatered_count + 1;
      steps = plant_number;
      cum_steps += steps;
      cum_step_units_near += steps*water_amount;
      do {
        std::cout << "Plant" << std::setw(2) << plant_number
        << std::setw(9) << cum_steps
        << std::setw(11) << water_amont
        << std:::setw(16) << cum_step_units_near << std::endl;

        water_amount--;
        unwatered_count--;
        trip_done = (water_amont == 0) || (unwatered_count == 0);

        if (!trip_done) {
          plant_number++;
          cum_steps++;
          cum_step_units_near += water_amount;
        }
      } while(!trip_done);

      steps = plant_number;
      cum_steps += steps;
      cum_step_units_near += steps*water_amont;

      std::cout << "FAUCET"
      << std::setw(10) << cum_steps
      << std::setw(11) << water_amont
      << std::setw(16) << cum_step_units_near << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Plan Near: Total steps = " << cum_steps
    << ", total step-units = " << cum_step_units_near << std:endl;

    std::cout << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << "Plan Near with " << plant_count << " plants" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << std::endl;
    std::cout << "Where      Cum. steps  Water amt.  Cum. step-units" << std::endl;
    std::cout << "---------  ----------  ----------  ---------------" << std::endl;

    unwatered_count = plant_count;
    cum_steps = 0;
    cum_step_units_far = 0;

    while(unwatered_count > 0) {
      water_amont = UNITS_PER_CAN;
      plant_number = unwatered_count;
      steps = plant_number;
      cum_steps += steps;
      cum_step_units_far += steps*water_amont;

      do {
        std::cout << "Plant" << std::setw(2) << plant_number
        << std::setw(9) << cum_steps
        << std::setw(11) << water_amont
        << std:::setw(16) << cum_step_units_near << std::endl;

        water_amount--;
        unwatered_count--;
        trip_done = (water_amont == 0) || (unwatered_count == 0);

        if (!trip_done) {
          plant_number--;
          cum_steps++;
          cum_step_units_near += water_amount;
        }
      } while(!trip_done);

      steps = plant_number;
      cum_steps += steps;
      cum_step_units_far += steps*water_amont;

      std::cout << "FAUCET"
      << std::setw(10) << cum_steps
      << std::setw(11) << water_amont
      << std::setw(16) << cum_step_units_far << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Plan Far: Total steps = " << cum_steps
    << ", total step-units = " << cum_step_units_far << std::endl;

    std::cout << std::endl;
    std::cout << "*** With" << plant_count << " plants, ";
    if (cum_step_units_far == cum_step_units_near) {
      std::cout << "both plans are equal." << std::endl;
    } else if (cum_step_units_far < cum_step_units_near) {
      std::cout << "Plan Far is better with "
      << cum_step_units_near - cum_step_units_far
      << " fewer step-units." << std::endl;
    } else {
      std::cout << "Plan Near is better with "
      << cum_step_units_far - cum_step_units_near
      << " fewer step-units." << std::endl;
    }
  } while(plant_count > 0);

  return 0;
}
