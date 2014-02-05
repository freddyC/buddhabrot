
#ifndef SOLVE_H
#define SOLVE_H

#include <random>
#include <complex>
#include <vector>

class Solve {
  public:
    Solve();
    Solve(int);

    std::vector<std::complex<double> > solve(void);

  private:
    std::vector<std::complex<double> > solve (std::complex<double> z, std::complex<double> c, int iters);
    std::complex<double> get_c (void);
    double get_dbl (double, double);

    int iterations;
    int seed;
    std::vector<std::complex<double> > results;
};

#endif 
/* defined(__bud__File__) */