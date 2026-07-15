#include "state.hpp"

State::State(const Config* config, const std::vector<Atom>& atoms) : config(config), atoms(atoms) {
    V = 0.0;
    P = 0.0;
    H = 0.0;
    T = 0.0;

    if (atoms.empty()) return;

    const double epsilon = config->epsilon;
    const double sigma = config->sigma;
    const double L = config->L;
    const double f = config->f;

    const double sigma2 = sigma * sigma;
    const size_t N = atoms.size();

    for (size_t i = 0; i < N; ++i) {
        const auto r_i = atoms[i].GetPosition(); 

        for (size_t j = 0; j < i; ++j) {
            const auto r_j = atoms[j].GetPosition();
            numc::vector<double> dr = r_i - r_j;

            double r2 = dr * dr;

            double inv_r2 = 1.0 / r2;
            double sr2 = sigma2 * inv_r2;   
            double sr6 = sr2 * sr2 * sr2;    
            double sr12 = sr6 * sr6;          

            V += 4.0 * epsilon * (sr12 - sr6);
        }
    }

    double total_wall_force = 0.0;
    for (const auto& atom : atoms) {
        auto selfR = atom.GetPosition(); 
        double r_norm = selfR.norm();

        if (r_norm > L) {
            total_wall_force += std::abs(f * (L - r_norm));
        }
    }
    
    P = total_wall_force / (4.0 * numc::PI * L * L);

    double total_kinetic_energy = 0.0;

    for (const auto& atom : atoms) {
        total_kinetic_energy += atom.GetEnergy();
    }

    T = (2.0 * total_kinetic_energy) / (3.0 * N * k_B);
    H = V + total_kinetic_energy;
}