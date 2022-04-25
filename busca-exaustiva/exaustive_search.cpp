#include <iostream>
#include <vector>
#include <string>

using namespace std;

int match(char a, char b){
  if(a == b){
    return 2;
  }
  return -1;
}

int calculate_score(string a, string b){
  int score = 0;
  for(int i = 0; i < int(a.size()); i++){
    score += match(a[i], b[i])
  }
  return score;
}

int main(){
  int n, m;
  string a, b;

  cin >> n >> m;
  cin >> a >> b;

  cout << "A size: " << n << endl;
  cout << "B size: " << m << endl;
  cout << "A: " << a << endl;
  cout << "B: " << b << endl;



  return 0;
}