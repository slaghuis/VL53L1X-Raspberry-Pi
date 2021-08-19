/* ******************************* XENI ROBOTICS *******************************
 * A test program to test the functionality of the vl53l1x library
 * Developed by Eric Slaghuis, Xeni Robotics, 18 August 2021
 *
 * g++ test.cpp vl53l1x.cpp -o test
 *
 * ********************************** X *** X ********************************** */

#include <iostream>
#include <string>

#include "vl53l1x.h"

using namespace std;

int main() {
  Vl53l1x sensor;

  sensor.setTimeout(500);
  if( sensor.init() ) {
    cout << "We are rocking!" << endl;
  } else {
    cout << "No, not yet" << endl;
    return -1;
  }

  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  sensor.setDistanceMode(Vl53l1x::Long);
  sensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor.startContinuous(50);

  for(auto i=0; i<60; i++) {
    int altitude = sensor.read_range();
    if(sensor.timeoutOccurred()) {
      cout << "TIMEOUT" << endl;
    } else {
      cout << "Altitude: " << altitude << "mm" << endl;
    }
  }

}
