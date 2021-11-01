
#include "tablero.h"

tablero::tablero(int n, int m)
{
    n_ = n;
    m_ = m;
    tablero_.resize(n_);
    for(int i = 0; i < tablero_.size(); i++)
        tablero_[i].resize(m_);
    for(int i = 0; i < tablero_.size(); i++)
        for(int j = 0; j < tablero_[i].size(); j++)
            tablero_[i][j] = CEL_W;
}

tablero::~tablero()
{}

int tablero::get_n() const
{
    return n_;
}

int tablero::get_m() const
{
    return m_;
}

void tablero::set_n(int n)
{
    n_ = n;
}

void tablero::set_m(int m) 
{
    m_ = m;
}

void tablero::mostrar() const
{
    for (int i = 0; i < n_; i++) {
        for (int j = 0; j < m_; j++)
            cout << tablero_[i][j];
        cout << "\n";
    }
}

void tablero::marcar(string color, int i, int j)
{
  if (i < 0 || i > (n_) || j < 0 || j > (m_)) {
    cout << "----No se pueden establecer este obstáculos, verifique que" << endl;
    cout << "----se mantengan dentro de las dimensiones del tablero." << endl;
    return;
  }
    tablero_[i][j] = color;
}

void tablero::Obstaculos( const float porcentaje) {
   int aleatorio_i, aleatorio_j;
  srand(time(NULL));
  int numero;
  numero = (n_ * m_) * porcentaje; // iteraciones segun el porcentaje
  for (int j = 0; j < numero; j++) {
    aleatorio_i = rand() % (n_);
    aleatorio_j = rand() % (m_); 
    tablero_[aleatorio_i][aleatorio_j] = CEL_B;
  }
  
}

bool
tablero::Valido(int x, int y) {
  if (x < 0 || y < 0) {
    return false;
  }
  if (x >= n_ || y >= m_) {
    return false;
  }
  if (tablero_[x][y] == CEL_B) {
     return false;
  } 
  return true;
}

string
tablero::get_color(int i, int j)
{
  return tablero_[i][j];
}

void
tablero::clonar(tablero& clonado)
{
  n_ = clonado.get_n();
  m_ = clonado.get_m();
  tablero_.resize(n_);
  for(int i = 0; i < tablero_.size(); i++){
      tablero_[i].resize(m_);
      for(int j = 0; j < tablero_[i].size(); j++)
          tablero_[i][j] = clonado.get_color(i, j);
  }
}