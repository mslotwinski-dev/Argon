#pragma once

#include "inc.hpp"
#include "atom.hpp"
#include "state.hpp"

class Space {
  std::vector<Atom> atoms;
  const Config* config;
  State* state;

 public:

  Space(const Config* config);
  ~Space() {}

  State GetState();
  void Update();

  void WriteXYZFrame(std::ostream& out, double scale = 1.0) const;
  void SaveToXYZ(const std::string& filename) const;
};