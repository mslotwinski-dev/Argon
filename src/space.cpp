#include "space.hpp"

Space::Space(const Config* config) : config(config) {
    const double a = config->a;
    const int n = config->n;
    const double T = config->T;
    const double N = static_cast<double>(n * n * n);

    this->atoms.reserve(N);

    const numc::vector b0 = {a, 0.0, 0.0};
    const numc::vector b1 = {a / 2.0, a * numc::SQRT3 / 2.0, 0.0};
    const numc::vector b2 = {a / 2.0, a * numc::SQRT3 / 6.0, a * numc::SQRT2 / numc::SQRT3};

    numc::vector P = {0.0, 0.0, 0.0};
    double ENERGY = 0.0;

    const double sf = (n - 1.0) / 2.0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                numc::vector r = (i - sf) * b0 + (j - sf) * b1 + (k - sf) * b2;
                int index = i + n * j + n * n * k;

                atoms.emplace_back(index, config, r[0], r[1], r[2]);

                P += atoms.back().GetMomentum();
                ENERGY += atoms.back().GetEnergy();
            }
        }
    }

    for (auto& atom : atoms) {
        atom.ZeroMomentum(P, N);
    }

    for (auto& atom : atoms) {
        atom.NormalizeEnergy(ENERGY);
    }
}

void Space::Update() {
    for (auto& atom : atoms) {
        atom.UpdateP12(atoms);
    }
    for (auto& atom : atoms) {
        atom.UpdateR(atoms);
    }
    for (auto& atom : atoms) {
        atom.UpdateP12(atoms);
    }
}

State Space::GetState() {
    return State(config, atoms);
}

void Space::WriteXYZFrame(std::ostream& out, double scale) const {
    out << atoms.size() << "\n";
    out << "Symulacja MD - klatka trajektorii\n";

    for (const auto& atom : atoms) {
        auto pos = atom.GetPosition();

        out << "Ar "
            << pos[0] * scale << " "
            << pos[1] * scale << " "
            << pos[2] * scale << "\n";
    }
}

void Space::SaveToXYZ(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Błąd: Nie można otworzyć pliku " << filename << " do zapisu.\n";
        return;
    }

    WriteXYZFrame(file);
}