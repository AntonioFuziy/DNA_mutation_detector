#include <iostream>
#include <vector>

using namespace std;

int match(string a, string b){
  if(a == b){
    return 2;
  };
  return -1;
}

int get_max_from_matrix(vector<vector<int>> matrix, int m, int n){
  int max = 0;
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      if(matrix[i][j] > max){
        max = matrix[i][j];
      }
    }
  }
  return max;
}

int smith_waterman(vector<vector<int>> H, int m, int n, string a, string b, int w){
  int diagonal, delecao, insercao;
  // calculando diagonal, delecao e insercao
  for (int i = 1; i < m; i++){
    for (int j = 1; j < n; j++){
      w = match(a, b);
      cout << w << endl;
      cout << H[i][j] << endl;
      diagonal = H[i-1][j-1] + w;
      cout << "diagonal" << endl;
      cout << diagonal << endl;
      delecao = H[i-1][j] - 1;
      cout << "delecao" << endl;
      cout << delecao << endl;
      insercao = H[i][j-1] - 1;
      cout << "insercao" << endl;
      cout << insercao << endl;
      H[i][j] = max(diagonal, max(delecao, max(insercao, 0))); 
    }
  }
  return get_max_from_matrix(H, m, n);
};

int main(){
  int n, m, w;
  w = 0;
  string a, b;
  cin >> n;
  cin >> m;
  cin >> a;
  cin >> b;

  //inicializando matriz H com zeros
  vector<vector<int>> H(m+1, vector<int>(n+1, 0));

  //printando as entradas do arquivo
  cout << "n: " << n << " m: " << m << endl;
  cout << "a: " << a << " b: " << b << endl;

  //chamando a funcao que monta a matriz H e retorna o valor maximo dela
  int max_from_H = smith_waterman(H, n, m, a, b, w);
  cout << max_from_H << endl;

  return 0;
}