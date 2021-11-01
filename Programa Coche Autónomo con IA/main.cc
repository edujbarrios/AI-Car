#include <iostream>
#include <fstream>
#include <string>
#include "tablero.h"
#include "taxi.h"

//PSEUDOCÓDIGO DEL MAIN

/*bienvenido al simuulador de coche autónomo (WORK IN PROGRESS)*/
//introduce el valor de la matriz del mundo, suponiendo que es de la forma NxM
//Introduce el valor de N:
//Introduce el valor de M:


//introduce el valor del punto de entrada suponiendo un AxB
//Introduce el valor de A:
//Introduce el valor de B:
// valor Matriz AxB == visitado

//Introduce el valor del punto de salida, suponiendo un IxJ
//Introduce el Valor de I:
//Introduce el valor de J:
// Valor Matriz IxJ == visitado (para que no haya obstaculos en ese punto y/o eliminar obstaculos si aparece en esa posicion desde fichero)

//ELIJA UNA OPCION (pulsar 1 o 2)

//1. Introducir obstaculos manualmente
//2. Introducir obstaculos desde fichero

//if opcion==1 generar obstaculos aleatorios y/o cantidad especificada por teclado
//if opcion 2, leer fichero y contar obstaculos

//MOSTRAR MATRIZ CON LOS OBSTACULOS Y EL PUNTO DE ENTRADA Y SALIDA

using namespace std;

int leer_obs(ifstream &a, tablero &T);
int main()
{
    int n, m, a, b, i, j, seleccion;
    bool confirmacion = false;
    float porcentaje_obstaculos;
    string fichero_obstaculos; 
    string conf_caracter;
    tablero* T;
    while (!confirmacion) {
    confirmacion = false;
    //cout << "\x1B[2J\x1B[H";    
    cout << "~ Simulador de Búsqueda: Coche Autónomo ~" << endl;
    cout << "Está ajustando el tamaño del escenario de simulación.\nIntroduzca el número de filas: ";
    cin >> n;
    cout << "Ahora, introduzca el número de columnas: ";
    cin >> m;
    T = new tablero(n, m);
    tablero& ref = *T;
    cout << "\n--\n";
    cout << "Ahora ajustará las coordenadas de salida y destino (de la forma AxB, siendo A la fila y B la columna)" << endl;
    cout << "Casilla de SALIDA" << endl;
    cout << "Introduce coordenada A: ";
    cin >> a;
    cout << "Introduce coordenada B: ";
    cin >> b;
    cout << "--" << endl;
    cout << "Casilla de DESTINO" << endl;
    cout << "Introduce coordenada A: ";
    cin >> i;
    cout << "Introduce coordenada B: ";
    cin >> j;
    cout << "--" << endl;
    cout << "Configuración de los obstáculos" << endl;
    cout << "Elija una de las dos opciones:" << endl;
    cout << "1. Obstáculos aleatorios." << endl;
    cout << "2. Cargar obstáculos desde fichero" << endl;
    cout << "Selección [1] o [2]: ";
    cin >> seleccion;
    switch (seleccion)
    {
        case 1:
            bool confirmacion_random;
            confirmacion_random = false;
            bool configuracion_correcta;
            configuracion_correcta = false;
            //string conf_random;
            //while (!confirmacion_random) {
                cout << "Introduzca porcentaje de celdas con obstáculo (de 0 a 1): ";
                cin >> porcentaje_obstaculos;
                T->Obstaculos(porcentaje_obstaculos);
                /*while (!configuracion_correcta) {
                cout << "\nEste es el tablero configurado:" << endl;
                T.mostrar();
                cout << "\n¿Volver a generar obstáculos? [s]/[n]: ";
                cin >> conf_random;
                if ((conf_random == 's') || (conf_random == 'n'))
                {
                    if (conf_random == 'n') {
                        confirmacion_random = true;
                        configuracion_correcta = true;
                    }
                    else if (conf_random == 's')
                    confirmacion_random = false;
                }
                }
            }*/
            break;    
        case 2:
            cout << "Introduzca nombre del fichero con los obstáculos: ";
            cin >> fichero_obstaculos;
            int cantidad_obs;
            int n_obstaculos;
            ifstream archivo;
            archivo.open(fichero_obstaculos);
            if(!archivo.is_open()) {
                cout << "no se ha podido leer el archivo seleccionado" << endl;
                return 1;
            }
            else {
                cout << "\nExaminando el archivo seleccionado" << endl;
                n_obstaculos = leer_obs(archivo, ref);
                cout << "\nSe han encontrado " << n_obstaculos << " obstáculos." << endl;
            }
            break;
    };
    cout << "\nEste es el tablero configurado:" << endl;
    T->marcar(CEL_G, a, b);
    T->marcar(CEL_G, i, j);
    T->mostrar();
    
    bool char_correcto_main = false;    
    while (!char_correcto_main) {
    cout << "\n¿Esta es la configuración deseada? [s]/[n]: ";
    cin >> conf_caracter;
    if ((conf_caracter == "s") || (conf_caracter == "n")) {
        char_correcto_main = true;
    if (conf_caracter == "s")
        confirmacion = true;
    else if (conf_caracter == "n")
        confirmacion = false;
    }
    }
   }

//    Coordenada inicio(a, b), final(i, j); 
    bool q_tipo = true;
    while (q_tipo) {
      bool enea;
      bool q_enea = false;
      while (!q_enea) {
      cout << "\n¿Permitir movimiento diagonal?";
      cout << "\n[s/n]: ";
      string respuesta_enea;
      cin >> respuesta_enea;
      if ((respuesta_enea == "s") || (respuesta_enea == "n")) {
        q_enea = true;
        if (respuesta_enea == "s")
            enea = true;
        else if (respuesta_enea == "n")
            enea = false;
      }
      else
        cout << "El caracter introducido no ha sido reconocido." << endl;
      }
      Taxi taxi(enea);       
      bool q_tipo_input = false;
      string tipo;
      while (!q_tipo_input) {   
      cout << "\nEscribe el tipo de función heurística:";
      cout << "\n[manhattan]";
      cout << "\n[diagonal]";
      cout << "\n[euclidea]" << endl;
      cout << "Seleccion: ";
      cin >> tipo;
      if ((tipo == "manhattan") || (tipo == "diagonal") || (tipo == "euclidea")) {
        q_tipo_input = true;
      }
      else
        cout << "El tipo de funcion introducida no ha sido reconocida." << endl;
      }
      Coordenada ini, fin;
      ini.x = a;
      ini.y = b;
      fin.x = i;
      fin.y = j;
      tablero *Clon;
      Clon = new tablero(1, 1);
      Clon->clonar(*T);

      unsigned t0, t1;
 
      t0 = clock();

      ListaCoordenadas path = taxi.EncontrarCamino(ini, fin, *Clon, tipo);

      t1 = clock();
      
      double time = (double(t1-t0)/CLOCKS_PER_SEC);
      cout << "Tiempo de ejecución: " << time << endl;
      cout << "Nodos abiertos: " << taxi.GetNodosAbiertos() << endl;
   
      for(auto& coordinate : path) {
        if (ini == coordinate) {
          Clon->marcar(CEL_G, coordinate.x, coordinate.y);
        } else if (fin == coordinate) {
          Clon->marcar(CEL_G, coordinate.x, coordinate.y);
        } else {
          Clon->marcar(CEL_R, coordinate.x, coordinate.y);
        }
      }
      Clon->mostrar();
      bool q_cambio_funcion = false;
      while (!q_cambio_funcion) {      
      cout << "¿Quiere probar con otra función heurística? [s/n]: " << endl;
      string cambio_funcion;
      cin >> cambio_funcion;
      if ((cambio_funcion == "s") || (cambio_funcion == "n")) {
          q_cambio_funcion = true;
        if (cambio_funcion == "s")
            q_tipo = true;
        else if (cambio_funcion == "n")
            q_tipo = false;
      }
      else
        cout << "El caracter introducido no ha sido reconocido. Reconfiguración automática" << endl;
    }
    }
return 0;
}

int leer_obs(ifstream &a, tablero &T)
{ 
    string obstaculo;
    int i, j;
    int contador = 0;
    while (!a.eof()) {
        a >> obstaculo;
        i = stoi(obstaculo);
        a.get();
        a >> obstaculo;        
        j = stoi(obstaculo);
        a.get();
        cout << "Obstaculo nº " << contador << " = fila: " << i << " | columna: " << j << endl;
        T.marcar(CEL_B, i, j);
        contador++;
    }
    return contador;
}