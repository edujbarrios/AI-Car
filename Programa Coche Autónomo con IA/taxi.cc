#include "taxi.h"

bool Coordenada::operator == (const Coordenada& coordinates_) {
    return (x == coordinates_.x && y == coordinates_.y);
}

Coordenada operator + (const Coordenada& left_, const Coordenada& right_) {
    return{ left_.x + right_.x, left_.y + right_.y };
}


Node::Node(Coordenada coordinates_, Node *parent_) {
    padre = parent_;
    coor = coordinates_;
    G = H = 0;
}

uint Node::GetCoste() {
    return G + H;
}

void Taxi::Diagonal(bool enable_) {
     directions = (enable_ ? 8 : 4);
}

Taxi::Taxi(bool mov) {
    nodos_abiertos = 0;
    Diagonal(mov);
    direction = {
        { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
        { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
    };
}
ListaCoordenadas Taxi::EncontrarCamino(Coordenada inicio, Coordenada fin, tablero& T, std::string& heur)
{
    Node *current = nullptr;
    ConjuntoNodos openSet, closedSet;
    openSet.reserve(1000000);
    closedSet.reserve(1000000);
    openSet.push_back(new Node(inicio));

    while (!openSet.empty()) {
        auto current_it = openSet.begin();
        current = *current_it;
        
        for (auto it = openSet.begin(); it != openSet.end(); it++) {
            auto node = *it;
            if (node->GetCoste() <= current->GetCoste()) {
                current = node;
                current_it = it;
            }
        }

        if (current->coor == fin) {
            break;
        }

        closedSet.push_back(current);
        openSet.erase(current_it);
        for (uint i = 0; i < directions; ++i) {
            Coordenada newCoordinates(current->coor + direction[i]);
            if (!T.Valido(newCoordinates.x, newCoordinates.y) || findNodeOnList(closedSet, newCoordinates)) {
                continue;
            } 

            nodos_abiertos++;
            
            uint totalCost = current->G + 1;
            Node *successor = findNodeOnList(openSet, newCoordinates);
            T.marcar(CEL_Y, newCoordinates.x, newCoordinates.y);

            if (successor == nullptr) {
                successor = new Node(newCoordinates, current);
                successor->G = totalCost;
                successor->H = AjustarHeuristico(heur, successor->coor, fin);
                openSet.push_back(successor);
            }
            else if (totalCost < successor->G) {
                successor->padre = current;
                successor->G = totalCost;
            }
        }
    }

    ListaCoordenadas path;
    while (current != nullptr) {
        path.push_back(current->coor);
        current = current->padre;
        //cout << current << " " << current->padre << endl;
    }

    releaseNodes(openSet);
    releaseNodes(closedSet);

    return path;
}

Node* Taxi::findNodeOnList(ConjuntoNodos& nodes_, Coordenada coordinates_) {
    for (auto node : nodes_) {
        if (node->coor == coordinates_) {
            return node;
        }
    }
    return nullptr;
}

uint Taxi::AjustarHeuristico(std::string& heur, Coordenada pos, Coordenada fin) {
  if (heur == "manhattan")
    return manhattan(pos, fin);
  else if (heur == "diagonal")
    return octagonal(pos, fin);
  else if (heur == "euclidea")
    return euclidean(pos, fin);
  return 0;
}

uint Taxi::manhattan(Coordenada pos, Coordenada fin) {
  return (abs(pos.x - fin.x) + abs(pos.y - fin.y));
}

uint Taxi::octagonal(Coordenada pos, Coordenada fin) {
  float dx = abs(pos.x - fin.x );
  float dy = abs(pos.y -  fin.y); 
  float h = (dx + dy) + (sqrt(2) - 2) * min(dx, dy);
  return h;
}

uint Taxi::euclidean(Coordenada pos, Coordenada fin) {
   return sqrt((pow(pos.x -  fin.x, 2))+pow(pos.y - fin.y, 2));
}

void Taxi::releaseNodes(ConjuntoNodos& nodes_) {
    for (auto it = nodes_.begin(); it != nodes_.end();) {
        delete *it;
        it = nodes_.erase(it);
    }
}

uint Taxi::GetNodosAbiertos()
{
    return nodos_abiertos;
}

