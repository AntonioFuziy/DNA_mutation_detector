#include <iostream>
#include <vector>

using namespace std;

//funcao que identifica match da base nitrogenada
int match(char a, char b){
  if(a == b){
    return 2;
  };
  return -1;
}

//funcao para calcular smith waterman
vector<vector<int>> smith_waterman(vector<vector<int>> H, int n, int m, string a, string b, int w){
  int diagonal, delecao, insercao, max_H;
  // calculando diagonal, delecao e insercao
  for (int i = 1; i < n; i++){
    for (int j = 1; j < m; j++){
      w = match(a[i], b[j]);
      diagonal = H[i-1][j-1] + w;
      delecao = H[i-1][j] - 1;
      insercao = H[i][j-1] - 1;
      H[i][j] = max(diagonal, max(delecao, max(insercao, 0)));
    }
  }
  return H;
};

int main(){
  int n, m, w;
  w = 0;
  string a, b;
  vector<vector<int>> H;
  cin >> n;
  cin >> m;
  cin >> a;
  cin >> b;

  a = a.insert(0, " ");
  b = b.insert(0, " ");

  //inicializando matriz H com zeros
  H.resize(n);
  for(int i = 0 ; i < n ; i++){
    H[i].resize(m);
  }

  //printando as entradas do arquivo
  cout << "n: " << n << " m: " << m << endl;
  cout << "a: " << a << " b: " << b << endl;

  //chamando a funcao que monta a matriz H e retorna o valor maximo dela
  H = smith_waterman(H, n, m, a, b, w);

  int max_H, max_i, max_j = 0;
  for(int i = 1; i < n; i++){
    for(int j = 1; j < m; j++){
      if(H[i][j] > max_H){
        max_H = H[i][j];
        max_i = i;
        max_j = j;
      }
    }
  }
  cout << "max " << max_H << endl;

  return 0;
}