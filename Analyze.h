
#ifndef __BuddahPar__Analyze__
#define __BuddahPar__Analyze__

#include <vector>
#include <complex>
#include <array>
#include <algorithm>
#include <fstream>
#include <iostream>

class Analyze
{
public:
  Analyze()
  : pixels()
  , x_histogram()
  , y_histogram()
  , x_min(-2.0)
  , y_min(-2.0)
  , x_max(2.0)
  , y_max(2.0)
  , filename("buddha")
  , max(0)
  , height(480)
  , width(640)
{}

  void set_x_min (double x) { this->x_min = x;}
  void set_y_min (double y) { this->y_min = y;}
  void set_x_max (double x) { this->x_max = x;}
  void set_y_max (double y) { this->y_max = y;}
  void set_filename (std::string str) { this->filename = str;}

  void process (std::vector<std::complex<double> >);

private:
  void add_point (double x, double y);
  void write_file(void);
  int get_r(double bias) { return (int)(((bias - 1 ) * (-1)) * 255 / 8); }
  int get_g(double bias) { return (int)(bias * 255 / 5); }
  int get_b(double bias) { return (int)(bias * 255); }
  void write_histograms (void);
  void write_x_histogram (void);
  void write_y_histogram (void);

  std::array<std::array<int, 480>, 640> pixels;
  std::array<int, 640> x_histogram;
  std::array<int, 480> y_histogram;
  std::string filename;
  double  x_min
        , y_min
        , x_max
        , y_max
        ;
  int max
    , height
    , width
    ;
};


#endif
/* defined(__bud__Analyze__) */
