#pragma once

#include "inc.hpp"
#include "config.hpp"

class Atom {
   int i;
   double x, y, z;
   double px, py, pz;
   const Config* config;

   public:
   
   Atom(int i, const Config* config, double x, double y, double z) : i(i), x(x), y(y), z(z), config(config) {
     SetMomentum(config->T);
   }
   
   void SetMomentum(double T);
   
   numc::vector<double> GetPosition() const { return {x, y, z}; }
   numc::vector<double> GetMomentum() const { return {px, py, pz}; }

   double GetEnergy() const { return (px*px + py*py + pz*pz) / (2*config->m); }

  void NormalizeEnergy(double scale);
  void ZeroMomentum(const numc::vector<double>& P, double N);
  
  void UpdateP12(std::vector<Atom>& atoms);
  void UpdateR(std::vector<Atom>& atoms);

  numc::vector<double> CalculateForce(std::vector<Atom>& atoms) const;

};