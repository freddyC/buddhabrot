#include "Analyze.h"

void Analyze::process (std::vector<std::complex<double> > vec) {
  std::for_each(vec.begin(), vec.end(), [&] (std::complex<double> v) {
    this->add_point(v.real(), v.imag());
  });
  std::cout << "Max pixel = " << this->max << std::endl << "Number Of Points = " << vec.size() << std::endl;
  this->write_file();
  this->write_histograms();
}

void Analyze::add_point(double x, double y) {
    // only use points within our window
  if( x < this->x_min || y < this->y_min || x > this->x_max || y > this->y_max) return;

  double x_percent = (x - this->x_min) / (this->x_max - this->x_min)
       , y_percent = (y - this->y_min) / (this->y_max - this->y_min)
       ;

  std::cout << "{" << x << ", " << y << ") = (" << x_percent << ", " << y_percent << ")\n";

  int x_pix = (int)(this->width * x_percent)
    , y_pix = (int)(this->height * y_percent)
    ;

    // update picture and histograms
  ++this->pixels[x_pix][y_pix];
  ++this->x_histogram[x_pix];
  ++this->y_histogram[y_pix];
  if (this->max < this->pixels[x_pix][y_pix]) {
    this->max = this->pixels[x_pix][y_pix];
  }
}

void Analyze::write_file (void) {
  std::ofstream fout (this->filename + ".ppm");
  fout << "P3\n640 420\n255\n";
  for (int y = 0; y < this->height; ++y) {
    for (int x = 0; x < this->width; ++x) {
      double bias = (double)this->pixels[x][y] / (double)this->max;
      std::cout << "Density = " << this->pixels[x][y] << " Bias = " << bias << std::endl;
      fout << this->get_r(bias) << " " << get_g(bias) << " " << get_b(bias);
      if (x < this->width -1) {
        fout << "\t";
      } else {
        fout << std::endl;
      }
    }
  }
}


void Analyze::write_histograms(void) {
  write_x_histogram();
  write_y_histogram();
}

void Analyze::write_x_histogram () {
  std::ofstream fout (this->filename + "_x_histo.txt");
  std::for_each(this->x_histogram.begin(), this->x_histogram.end(), [&] (int val) {
    fout << val << std::endl;
  });
}


void Analyze::write_y_histogram () {
 std::ofstream fout (this->filename + "_y_histo.txt");
  std::for_each(this->y_histogram.begin(), this->y_histogram.end(), [&] (int val) {
    fout << val << std::endl;
  });
}