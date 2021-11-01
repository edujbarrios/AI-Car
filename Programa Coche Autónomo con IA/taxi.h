#ifndef TAXI_H_
#define TAXI_H_


#include <vector>
#include <functional>
#include <set>
#include <string>
#include <cmath>
#include "tablero.h"

struct Coordenada {
  int x, y;
  bool operator == (const Coordenada& coor);
};

using uint = unsigned int;
using FuncionHeuristica = std::function<uint(Coordenada, Coordenada)>;
using ListaCoordenadas = std::vector<Coordenada>;

struct Node {
  uint G, H;
  Coordenada coor;
  Node *padre;

  Node(Coordenada coord_, Node *parent_ = nullptr);
      uint GetCoste();
};

using ConjuntoNodos = std::vector<Node*>;

class Taxi {

        Node* findNodeOnList(ConjuntoNodos& nodes_, Coordenada coordinates_);
        void releaseNodes(ConjuntoNodos& nodes_);

    public:
        Taxi(bool mov);
        void Diagonal(bool activar);
        uint AjustarHeuristico(std::string& heur, Coordenada inicio, Coordenada fin);
        ListaCoordenadas EncontrarCamino(Coordenada inicio_, Coordenada fin_, tablero& T, std::string& heur);
        static uint manhattan(Coordenada inicio, Coordenada fin);
        static uint euclidean(Coordenada inicio, Coordenada fin);
        static uint octagonal(Coordenada inicio, Coordenada fin);
        uint GetNodosAbiertos();
    private:
      ListaCoordenadas direction;
      uint directions;
      uint nodos_abiertos;
      
};

  

#endif // TAXI_H_