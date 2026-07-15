#pragma once

#include "inc.hpp"
#include "space.hpp"
#include "config.hpp"

class Simulation {
  const Config* config;
  Space* space;

 public:
  Simulation(const Config* config);
  ~Simulation() {}

  void Start(int steps, const std::string& xyzFile = "trajectory.xyz", int exportEvery = 1, double exportScale = 1.0);
  void Next();
};