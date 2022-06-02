#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <cstdlib>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/reduce.h>
#include <thrust/fill.h>

using namespace std;

struct begin_end{
  int start;
  int size;
};

using namespace std::chrono;

void reportTime(const char* msg, steady_clock::duration span) {
  auto ms = duration_cast<milliseconds>(span);
  std::cout << msg << " - levou - " <<
  ms.count() << " milisegundos" << std::endl;
}

struct sequence_match{
  __host__ __device__
  int operator()(const char& a, const char& b){
    if(a == b){
      return 2;
    }
    return -1;
  }
};

int main(){
  int m, n;
  string a, b;
  steady_clock::time_point ts, te;
  
  std::cin >> n;
  std::cin >> m;
  std::cin >> a;
  std::cin >> b;

  int max_size = 0;

  if(int(a.size() < int(b.size()))){
    max_size = int(a.size());
  } else {
    max_size = int(b.size());
  }

  // for(int index = 0; index < max_size; index++){
  //   for(int i = 0; i < int(a.size()); i++){
      
  //   }

  //   for(int j = 0; j < int(b.size()); j++){

  //   }
  // }

  thrust::device_vector<char> a_gpu(n);
  thrust::device_vector<char> b_gpu(m);
  thrust::device_vector<char> all_sequences(max_size);

  for(int i = 0; i < n; i++){
    a_gpu[i] = a[i];
  }

  for(int i = 0; i < m; i++){
    b_gpu[i] = b[i];
  }

  ts = steady_clock::now();
  thrust::transform(
    a_gpu.begin(), a_gpu.end(),
    b_gpu.begin(), all_sequences.begin(),
    sequence_match()
  );
  
  int score = thrust::reduce(all_sequences.begin(), all_sequences.end(), (int) 0, thrust::plus<int>());
  
  te = steady_clock::now();
  reportTime("Tempo para calculo", te - ts);
  std::cout << std::fixed << std::setprecision(4);

  std::cout << "Score: " << score << endl;

  return 0;
}