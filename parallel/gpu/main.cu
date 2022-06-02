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
  int start_a;
  int start_b;
  int size_a;
  int size_b;
};

using namespace std::chrono;

std::vector<begin_end> generate_indexes(int max_size, int min_size){
  vector<begin_end> indexes;
  begin_end current_index;

  for(int index = 0; index < min_size; index++){
    for(int i = 0; i < max_size; i++){
      for(int j = 0; j < min_size; j++){
        current_index.start_a = i;
        current_index.start_b = j;
        current_index.size_a = i+index;
        current_index.size_b = j+index;
        indexes.push_back(current_index);
      }
    }
  }
  return indexes;
}

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
  int min_size = 0;
  int max_score = 0;

  min_size = int(a.size());
  max_size = int(b.size());

  std::vector<begin_end> all_indexes = generate_indexes(max_size, min_size);

  thrust::device_vector<char> a_gpu(n);
  thrust::device_vector<char> b_gpu(m);
  thrust::device_vector<char> all_sequences(min_size);

  for(int i = 0; i < n; i++){
    a_gpu[i] = a[i];
  }

  for(int i = 0; i < m; i++){
    b_gpu[i] = b[i];
  }

  ts = steady_clock::now();
  for(int i = 0; i < int(all_indexes.size()); i++){
    thrust::transform(
      a_gpu.begin() + all_indexes[i].start_a, a_gpu.end() + all_indexes[i].size_a,
      b_gpu.begin() + all_indexes[i].start_b, all_sequences.begin(),
      sequence_match()
    );
   
    int score = thrust::reduce(all_sequences.begin(), all_sequences.end(), (int) 0, thrust::plus<int>());
    if (max_score < score){
      max_score = score;
    }
  }
  
  te = steady_clock::now();
  reportTime("Tempo para calculo", te - ts);
  std::cout << std::fixed << std::setprecision(4);

  std::cout << "Score: " << max_score << endl;

  return 0;
}