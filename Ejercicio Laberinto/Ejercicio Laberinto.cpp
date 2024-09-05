#include <iostream>
#include <vector>
using namespace std;

const int tam = 7;

//recorrer camino Iterativo
struct coord {
    int x;
    int y;
    bool revDerecha;
    bool revIzquierda;
    bool revArriba;
    bool revAbajo;
    coord* siguiente;
    coord* anterior;
    coord() : revDerecha(false), revIzquierda(false), revArriba(false),
        revAbajo(false), siguiente(nullptr), anterior(nullptr), x(0), y(0) {}
};

bool estaEnElMapa(int num) {
    if (num >= 0 && num < tam) {
        return true;
    }
    return false;
}

void recorrerCaminoIterativo(int Inicio[], int Final[], coord* cabeza, int laberinto[tam][tam]) {

    coord* actual = cabeza;
    int x = cabeza->x, y = cabeza->y;

    if (laberinto[x][y] == 0) {
        cout << "Posicion invalida";
        return;
    }
    int a = 0;
    while (actual != nullptr && (actual->x != Final[0] || actual->y != Final[1])) {

        if (a == 3) {
            a = a;
        }
        if (!(actual->revAbajo)) { //y+1 = derecha
            
            if (laberinto[x+1][y] == 0 || !estaEnElMapa(x + 1)) {
                actual->revAbajo = true;
            }
            else {

                x++;
                actual->revAbajo = true;
                coord* nuevaAbajo = new coord;
                nuevaAbajo->x = x;
                nuevaAbajo->y = y;
                actual->siguiente = nuevaAbajo;
                nuevaAbajo->anterior = actual;
                nuevaAbajo->revArriba = true;
                actual = nuevaAbajo;
            }
        }
        else if (!(actual->revDerecha)) { //x+1 = abajo
            
            if (laberinto[x][y + 1] == 0 || !estaEnElMapa(y + 1)) {
                actual->revDerecha = true;
            }
            else {

                y++;
                actual->revDerecha = true;
                coord* nuevaDerecha = new coord;
                nuevaDerecha->x = x;
                nuevaDerecha->y = y;
                actual->siguiente = nuevaDerecha;
                nuevaDerecha->anterior = actual;
                nuevaDerecha->revIzquierda = true;
                actual = nuevaDerecha;
            }
        }
        else if (!(actual->revArriba)) { //y-1 = izquierda
            
            if (laberinto[x - 1][y] == 0 || !estaEnElMapa(x - 1)) {
                actual->revArriba = true;
            }
            else {

                x--;
                actual->revArriba = true;
                coord* nuevaArriba = new coord;
                nuevaArriba->x = x;
                nuevaArriba->y = y;
                actual->siguiente = nuevaArriba;
                nuevaArriba->anterior = actual;
                nuevaArriba->revAbajo = true;
                actual = nuevaArriba;
            }
        }
        else if (!(actual->revIzquierda)) { //x-1 = arriba
            
            if (laberinto[x][y-1] == 0 || !estaEnElMapa(y - 1)) {
                actual->revIzquierda = true;
            }
            else {

                y--;
                actual->revIzquierda = true;
                coord* nuevaIzquierda = new coord;
                nuevaIzquierda->x = x;
                nuevaIzquierda->y = y;
                actual->siguiente = nuevaIzquierda;
                nuevaIzquierda->anterior = actual;
                nuevaIzquierda->revDerecha = true;
                actual = nuevaIzquierda;
            }
        }
        else {
            actual = actual->anterior;
            if (actual != nullptr) {
                x = actual->x;
                y = actual->y;
                actual->siguiente = nullptr;
            }
        }
    }
}

//recorrer camino recursivo
bool posicionSegura(int x, int y, int laberinto[tam][tam], bool visitados[tam][tam]) {
    return (x >= 0 && x < tam && y >= 0 && y < tam && laberinto[x][y] == 1 && !visitados[x][y]);
}

bool recorrerCamino(int laberinto[tam][tam], int x, int y, int finalX, int finalY, bool visitados[tam][tam], int recorridoX[], int recorridoY[], int& pos) {
    if (x == finalX && y == finalY) {
        recorridoX[pos] = x;
        recorridoY[pos] = y;
        pos++;
        return true;
    }

    visitados[x][y] = true;
    recorridoX[pos] = x;
    recorridoY[pos] = y;
    pos++;

    // Movimientos posibles: arriba, abajo, izquierda, derecha
    int dirX[] = { -1, 1, 0, 0 };
    int dirY[] = { 0, 0, -1, 1 };

    // Recorrer en todas las direcciones
    for (int i = 0; i < 4; ++i) {
        int nuevoX = x + dirX[i];
        int nuevoY = y + dirY[i];

        if (posicionSegura(nuevoX, nuevoY, laberinto, visitados)) {
            if (recorrerCamino(laberinto, nuevoX, nuevoY, finalX, finalY, visitados, recorridoX, recorridoY, pos)) {
                return true;
            }
        }
    }

    pos--;  // Retrocedemos si no se encuentra el camino
    visitados[x][y] = false;
    return false;
}

void printCamino(int recorridoX[], int recorridoY[], int pos) {
    cout << "Recorrido del laberinto: \n";
    for (int i = 0; i < pos; ++i) {
        cout << "(" << recorridoX[i] << ", " << recorridoY[i] << ") ";
    }
    cout << endl;
}

void recorrerCaminoRecursivo(int laberinto[tam][tam], int Inicio[],int Final[]) {
    bool visitados[tam][tam] = { false };  // matriz de posiciones visitadas
    int recorridoX[tam * tam], recorridoY[tam * tam];  //guarda las coordenadas del laberinto, en X y Y de forma simultanea
    int pos = 0;  //posicion actual del recorrido

    if (recorrerCamino(laberinto, Inicio[0], Inicio[1], Final[0], Final[1], visitados, recorridoX, recorridoY, pos)) {
        printCamino(recorridoX, recorridoY, pos);
    }
    else {
        cout << "No se encontró un camino válido.\n";
    }
}

int main(){

    int Inicio[2] = { 0, 0 }, Final[2] = {6, 0};

    cout << "Laberinto\n\n";
    int laberinto[tam][tam] = {
        {1, 1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0 ,1 ,0},
        {1, 1, 1, 1, 1, 1, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 1, 0},
        {1, 0, 1, 0, 0, 0, 1}
    };

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            cout << laberinto[i][j];
        }
        cout << "\n";
    }

    //Iterativo
    cout << "\nCamino Iterativo\n";
    coord* cabeza = new coord;
    cabeza->x = Inicio[0];
    cabeza->y = Inicio[1];
    recorrerCaminoIterativo(Inicio, Final, cabeza, laberinto);

    coord* actual = cabeza;
    while (actual != nullptr) {

        cout << "(" << actual->x <<", "<< actual->y << ") ";
        actual = actual->siguiente;
    }
    //

    //recursivo
    cout << "\n\nCamino recursivo\n";
    recorrerCaminoRecursivo(laberinto, Inicio, Final);
    //
    return 0;
}