#include "atom.hpp"

void Atom::SetMomentum(double T) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    double std_dev = std::sqrt(config->m * k_B * T);
    std::normal_distribution<double> gauss(0.0, std_dev);

    px = gauss(gen);
    py = gauss(gen);
    pz = gauss(gen);
}

void Atom::NormalizeEnergy(double scale) {
    double sqrtscale = std::sqrt(scale);
    px /= sqrtscale;
    py /= sqrtscale;
    pz /= sqrtscale;
}

void Atom::ZeroMomentum(const numc::vector<double>& P, double N) {
    px -= P[0] / N;
    py -= P[1] / N;
    pz -= P[2] / N;
}

numc::vector<double> Atom::CalculateForce(std::vector<Atom>& atoms) const {
  numc::vector<double> F{0.0, 0.0, 0.0};
    
  const double sigma2 = config->sigma * config->sigma;
  const double lj_coef = 24.0 * config->epsilon;

  for (const auto& atom : atoms) {
    if (atom.i == i) continue; 

    numc::vector<double> r_vec = GetPosition() - atom.GetPosition();

    double r2 = r_vec * r_vec; 
      
    double inv_r2 = 1.0 / r2;
    double sr2 = sigma2 * inv_r2;     
    double sr6 = sr2 * sr2 * sr2;     
    double sr12 = sr6 * sr6;          

    double factor = lj_coef * (2.0 * sr12 - sr6) * inv_r2;

    F += r_vec * factor; 
  }

  auto selfR = GetPosition();
  double r_norm = selfR.norm();
    
  if (r_norm > config->L) {
    F += config->f * (config->L - r_norm) * selfR.normalize();
  }

  return F;
}

void Atom::UpdateP12(std::vector<Atom>& atoms) {
  const numc::vector<double> P12 = GetMomentum() + 0.5 * CalculateForce(atoms) * config->dt;
  px = P12[0];
  py = P12[1];
  pz = P12[2];
}

void Atom::UpdateR(std::vector<Atom>& atoms) {
  numc::vector<double> R = GetPosition() + (GetMomentum() / config->m) * config->dt;
  x = R[0];
  y = R[1];
  z = R[2];
}