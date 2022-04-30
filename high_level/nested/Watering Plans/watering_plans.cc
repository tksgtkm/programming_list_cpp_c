#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

int main() {
  const int UNITS_PER_CAN = 3;

  int plant_count;         // count of plants
  int plant_number;        // plant #1, #2, #3, ...
  int unwatered_count;     // count of unwatered plants
  int water_amount;        // amount of water in the watering can
  int steps;               // number of steps token
  int cum_steps;           // cumulative number of steps token for a plan
  int cum_step_units_near; // cumulative step-units for Plan Near
  int cum_step_units_far;  // cumulative step-units for Plan Far
  bool trip_done;          // true if a trip is done

  const std::string INPUT_FILE_NAME = "counts.txt";

  std::ifstream input;
  input.open(INPUT_FILE_NAME);
  if (input.fail()) {
    std::cout << "Failed to open " << INPUT_FILE_NAME << std::endl;
    return -1;
  }

  /*
  Loop once for each number of plants read from the input file.
  Stop when the number of plants is 0 or less.
  During each loop, simulate Plan Near and Plan Far.
  */
  do {
    input >> plant_count;
    if (plant_count <= 0)
      return 0;

    // Plan Near
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

    /*
    Loop once per trip from the faucet until all the plants are watered.
    During each loop, fill the can, water plants according to plan,
    and return to the faucet.
    */
    while (unwatered_count > 0) {

      // Fill the can.
      water_amount = UNITS_PER_CAN;

      // Walk to the nearest unwatered plant with a full can.
      plant_number = plant_count - unwatered_count + 1;
      steps = plant_number;
      cum_steps += steps;
      cum_step_units_near += steps*water_amount;

      /*
      Water plants while walking away from the faucet.
      Loop once per amount until either the can is empty
      or all the plants have been watered.
      During each loop, water one plant.
      */
      do {
        std::cout << "Plant" << std::setw(2) << plant_number
        << std::setw(9) << cum_steps
        << std::setw(11) << water_amount
        << std::setw(16) << cum_step_units_near << std::endl;

        water_amount--;
        unwatered_count--;
        trip_done = (water_amount == 0) || (unwatered_count == 0);

        if (!trip_done) {
          // Water away from to the next unwatered plant.
          plant_number++;
          cum_steps++;
          cum_step_units_near += water_amount;
        }
      } while(!trip_done);

      // Walk back to the faucet with an empty or partially filled can.
      steps = plant_number;
      cum_steps += steps;
      cum_step_units_near += steps*water_amount;

      std::cout << "FAUCET"
      << std::setw(10) << cum_steps
      << std::setw(11) << water_amount
      << std::setw(16) << cum_step_units_near << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Plan Near: Total steps = " << cum_steps
    << ", total step-units = " << cum_step_units_near << std::endl;

    // Plan Far
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
      water_amount = UNITS_PER_CAN;
      plant_number = unwatered_count;
      steps = plant_number;
      cum_steps += steps;
      cum_step_units_far += steps*water_amount;

      do {
        std::cout << "Plant" << std::setw(2) << plant_number
        << std::setw(9) << cum_steps
        << std::setw(11) << water_amount
        << std::setw(16) << cum_step_units_far << std::endl;

        water_amount--;
        unwatered_count--;
        trip_done = (water_amount == 0) || (unwatered_count == 0);

        if (!trip_done) {
          plant_number--;
          cum_steps++;
          cum_step_units_near += water_amount;
        }
      } while(!trip_done);

      steps = plant_number;
      cum_steps += steps;
      cum_step_units_far += steps*water_amount;

      std::cout << "FAUCET"
      << std::setw(10) << cum_steps
      << std::setw(11) << water_amount
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
