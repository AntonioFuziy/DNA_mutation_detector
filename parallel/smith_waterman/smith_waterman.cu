#include <iostream>
#include <algorithm>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/reduce.h>
#include <thrust/fill.h>

using namespace std;

struct sequence_match{
  __host__ __device__
  int operator()(const char& a, const &char b){
    if()
  }
};

int main(){
  int m, n;
  string a, b;
  
  cin >> n;
  cin >> m;
  cin >> a;
  cin >> b;

  thrust::device_vector<char> a_gpu(n);
  thrust::device_vector<char> b_gpu(m);

  for(int i = 0; i < n; i++){
    a_gpu[i] = a[i];
  }

  for(int i = 0; i < m; i++){
    b_gpu[i] = b[i];
  }

  thrust::device_vector<int> calc[2];
  calc[0].resize(n+1);
  calc[1].resize(n+1);
  
  thrust::fill(calc[0].begin(), calc[0].end(), 0);
  thrust::device_vector<char> gpu_vec = a_gpu;


  
  return 0;
}