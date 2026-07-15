#include "simulation.hpp"

Simulation::Simulation(const Config* config) : config(config) {
    space = new Space(config);
}

void Simulation::Start(int steps, const std::string& xyzFile, int exportEvery, double exportScale) {
    std::cout<< "Rozpoczynam symulacje z " << steps << " krokami." << std::endl;

    std::ofstream trajectory(xyzFile, std::ios::trunc);
    if (!trajectory.is_open()) {
        std::cerr << "Błąd: Nie można otworzyć pliku " << xyzFile << " do zapisu trajektorii.\n";
        return;
    }

    for (int step = 0; step < steps; step++) {
        State state = space->GetState();
        std::cout << "Krok: " << step << ", V: " << state.GetV() << ", P: " << state.GetP() << ", H: " << state.GetH() << ", T: " << state.GetT() << std::endl;

        if (exportEvery > 0 && step % exportEvery == 0) {
            space->WriteXYZFrame(trajectory, exportScale);
        }

        Next();
    }
}

void Simulation::Next() {
    space->Update();
}

