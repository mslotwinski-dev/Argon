#pragma once

#include "inc.hpp"
#include "atom.hpp"
#include "config.hpp"

class State {
  const Config* config;

  double V;
  double P;
  double H;
  double T;
  std::vector<Atom> atoms;

  public:
  State(const Config* config, const std::vector<Atom>& atoms);
  ~State() {}

  double GetV() const { return V; }
  double GetP() const { return P; }
  double GetH() const { return H; }
  double GetT() const { return T; }
  const std::vector<Atom>& GetAtoms() const { return atoms; }
};