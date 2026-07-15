#pragma once

class Config {
  

  public:
   Config(int n, double a, double T, double m, double epsilon, double sigma, double L, double f, double dt) : n(n), a(a), T(T), m(m), epsilon(epsilon), sigma(sigma), L(L), f(f), dt(dt) {}

    int n;
    double a;
    double T;
    double m;
    double epsilon;
    double sigma;
    double L;
    double f;
    double dt;
};

constexpr double k_B = 0.00831;