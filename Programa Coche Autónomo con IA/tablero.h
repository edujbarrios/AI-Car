#ifndef TABLERO_H_
#define TABLERO_H_
#include <iostream>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <set>
#include <list>
#include <ctime>

#define CEL_W  "⬜"
#define CEL_B  "⬛"
#define CEL_R  "🟥"
#define CEL_G  "🟩"
#define CEL_Y  "🟨"



using namespace std;


class tablero

{
private:
    vector <vector<string>> tablero_;
    int n_;
    int m_;
public:
    tablero(int n=4, int m=4);
    ~tablero();
// getters
    int get_m(void) const;
    int get_n(void) const;
    string get_color(int i, int j);
// setters
    void set_m (const int);
    void set_n (const int);
// funciones generales
    void mostrar(void) const;
    void marcar(string color, int i, int j);
    void Obstaculos(const float);
    bool Valido(int, int);
    //void TrazarCamino(); //implementar
    void clonar(tablero& T_clonado);
};

#endif // TABLERO_H_
