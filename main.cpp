#include "src/simulation.hpp"

int main() {
  double a = 0.38;
  int n = 5 ;

  Config config(
    n,         // n 
    a,        // a
    0.00000001,      // T
    40,     // m
    1,          // epsilon
    a,          // sigma
    2.3,         // L 1.5 * a * (n - 1)
    1000,         // f
    0.001        // dt    
  );

  Simulation simulation(&config);

  simulation.Start(4000, "public/timelapse.xyz", 10, 10.0);
  return 0;
}

