#include <iostream>
#include "Solve.h"
#include "Analyze.h"
#include <mpi.h>
#include <thread>

std::mutex gen;
std::vector<std::complex<double> > my_points;

void generate(int);
void write(double, double, double, double);

int main(int argc, char * argv[]) {
  int proc_count, name;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
  MPI_Comm_rank(MPI_COMM_WORLD, &name);

  std::thread thread_1(generate, 1);
  std::thread thread_2(generate, 2);
  std::thread thread_3(generate, 3);
  std::thread thread_4(generate, 4);

  thread_1.join();
  thread_2.join();
  thread_3.join();
  thread_4.join();

  std::cout << "Node " << name << " generated " << my_points.size() << " points."<< std::endl;

  if(name == 0) {
    for (int i = 1; i < proc_count; ++i) {
      std::cout << "Recieceing from Node " << i << std::endl;
      
      int size = 0;
      MPI_Recv(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      std::cout << "Recieving Node's " << i << "  " << size << " doubles/n";

      std::vector<double> temp_list(size);
      MPI_Recv(&temp_list[0], size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      for (int k = 0; k < size; k += 2) {
        std::complex<double> temp(temp_list[k], temp_list[k+1]);
        my_points.push_back(temp);
      }

      std::cout << "Recieved " << size/2 << " points from Node " << i << " points\n\n";
    }
  } else {
    std::vector<double> temp_list;
    std::for_each(my_points.begin(), my_points.end(), [&] (std::complex<double> val) {
      temp_list.push_back(val.real());
      temp_list.push_back(val.imag());
    });
    
    int size = temp_list.size();
    std::cout << "Sending from Node " << name << " size to be sent " << size << " doubles/n";

    MPI_Send(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    std::cout << "Sending from Node " << name << "  " << size << " doubles/n";

    MPI_Send(&temp_list[0], size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

    std::cout << "Sent " << size/2 << " points from Node " << name << " points\n\n";
  }



  if (name == 0) {

    std::thread t1(write, -2.0, 2.0, -2.0, 2.0);
    std::thread t2(write, -1.0, 1.0, -1.0, 1.0);
    std::thread t3(write, -1.5, 1.5, -1.5, 1.5);
    std::thread t4(write, -2.0, 2.0, -1.0, 1.0);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
  }

  MPI_Finalize();
}


void generate(int seed) {
  int count = 0;
  for (int i = 0; i < 1000000; ++i) {
    Solve cur(seed);
    auto temp = cur.solve();
    {
      std::lock_guard<std::mutex> lock(gen);
      count += temp.size();
      my_points.insert(my_points.end(), temp.begin(), temp.end());
    }
  }
  std::cout << "\n THREAD IS DONE: list length = " << count << "\n\n";
}

void write (double x_min, double x_max, double y_min, double y_max) {
  Analyze a;
  a.set_x_min(x_min);
  a.set_y_min(x_max);
  a.set_x_max(y_min);
  a.set_y_max(y_max);
  std::string filename = std::to_string(x_min) + "_" + std::to_string(x_max) + "_" + std::to_string(y_min) + "_" + std::to_string(y_max);
  a.set_filename(filename);
  a.process(my_points);
}