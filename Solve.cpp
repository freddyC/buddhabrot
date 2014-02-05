
#include "Solve.h"

Solve::Solve()
  : iterations(1000)
  , results()
{
  std::random_device rd;
  std::uniform_int_distribution<> dis(0, 1000);
  std::mt19937 gen(rd());
  this->seed = dis(gen);
}


Solve::Solve(int s)
  : iterations(1000)
  , seed(s)
  , results()
{}

#include <iostream>
std::vector<std::complex<double> > Solve::solve(void) {
  std::complex<double> z(0.0, 0.0);
  auto c = this->get_c();
  std::vector<std::complex<double> > temp;

  int i = 0;
  while (i < this->iterations) {
    if ((z.real() * z.real()) + (z.imag() + z.imag()) > 4) {
      return temp;
    }

    z = z * z + c;
    temp.push_back(z);
    ++i;
  }

  std::vector<std::complex<double> > blank;
  return blank;
}


std::complex<double> Solve::get_c (void){
  std::complex<double> c(this->get_dbl(-3, 3), this->get_dbl(-3, 3));
  return c;
}


double Solve::get_dbl (double min, double max) {
  std::random_device rd;
  int seed = rd() + this->seed;
  std::mt19937 gen(seed);
  std::uniform_real_distribution<double> dis(min, max);
  return dis(gen);
}