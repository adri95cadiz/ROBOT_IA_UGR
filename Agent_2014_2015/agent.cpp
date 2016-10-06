#include "agent.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <climits>

using namespace std;
// ----------------------------------------------------------- //
Agent::ActionType Agent::Think()
{

	ActionType accion;
    //showmap();                              //Descomentar para mostrar el mapa en cada turno del programa y ver su evolución.
	if(last_step==actFORWARD && bump_!=true && step >= 150){ //Si en el último paso avanzó, es decir, cambió de casilla, huele dicha casilla.
        accion=actSNIFF;
    }
    else if(last_step==actSNIFF && trufa_size_>=8){ //Si en el último turno olió, extrae las trufas de la casilla si estas superan un número.
        accion=actEXTRACT;                           //Probar para diferentes tamaños de trufa_size_ y poner el que de mejores resultados. (Resultado = 10, reflejado en la memoria).
    }
    else if(tmap[pos_y][pos_x]==-1){  //Cuando choca gira a la izquierda por defecto,
        accion=actTURN_L;               //si lo hacemos de forma aleatoria pueden ocurrir casos
        direction++;                    //en los que el sistema vuelva sobre sus pasos en lugar de realizar un recorrido.
        if(direction>=4)
            direction =0;
    }
    else{
        if(bump_ != true && getDirection()==direction){ //Aquí si no ha chocado y getDirection le devuelve la dirección en la que va sigue adelante y cambia su posición en la matriz.
            accion=actFORWARD;
            if(direction==0){
                pos_y--;
            }
            else if(direction==1){
                pos_x--;
            }
            else if(direction==2){
                pos_y++;
            }
            else if(direction==3){
                pos_x++;
            }
        } else{
            if(direction==0 && bump_==true){       //Aquí si ha chocado deja un muro en la matriz y reajusta su posición.
                tmap[pos_y][pos_x] = -1;
                pos_y++;
            }
            else if(direction==1 && bump_==true){
                tmap[pos_y][pos_x] = -1;
                pos_x++;
            }
            else if(direction==2 && bump_==true){
                tmap[pos_y][pos_x] = -1;
                pos_y--;
            }
            else if(direction==3 && bump_==true){
                tmap[pos_y][pos_x] = -1;
                pos_x--;
            }

            if(direction==0 && getDirection()==3){ //Aquí establece la dirección de giro según la dirección que le devuelva getDirection().
                accion=actTURN_R;
                direction=3;
            }
            else if((direction - getDirection()) == 1){
                accion=actTURN_R;
                direction--;
            }
            else{                                  //Si no se da ninguna de las condiciones para girar a la derecha girará a la izquierda.
                accion=actTURN_L;
                direction++;
                if(direction>=4)
                    direction=0;
            }
        }
    }
    tmap[pos_y][pos_x]=step;
    step++;
    last_step=accion;
	return accion;
}

int Agent::getDirection(){
    int direccion, pmin, arr_pos[4];
    pmin=INT_MAX;
    arr_pos[0] = tmap[pos_y-1][pos_x]; //Arriba.
    arr_pos[1] = tmap[pos_y][pos_x-1]; //Izquierda.
    arr_pos[2] = tmap[pos_y+1][pos_x]; //Abajo.
    arr_pos[3] = tmap[pos_y][pos_x+1]; //Derecha.

    if(arr_pos[direction] == 0){ //Si la dirección en la que está mirando no está explorada, continúa en esa dirección
        direccion = direction;
    }
    else{
        for(int i=0;i<4;i++){    //Si la dirección está explorada elige el que tenga el mínimo de entre las 4 direcciones posibles.
            if(arr_pos[i] != -1 && arr_pos[i] < pmin){
                pmin = arr_pos[i];
                direccion = i;
            }
        }
    }
    return direccion;
}

void Agent::showmap(){      //Esta función sólo la utilizo para realizar comprobaciones, la dejo por si se requiere su uso para probar el programa u otras cosas.
    for(int i=0;i<17;i++){  //Muestra el mapa en casillas de 4 cifras, realizar una ejecución para más de 9999 pasos descordinaría el mapa.
        for(int k=0;k<17;k++){
            printf("%4d",tmap[i][k]);
        }
        cout << endl;
    }
    cout << endl;
}

// ----------------------------------------------------------- //
void Agent::Perceive(const Environment &env)
{
	trufa_size_ = env.TrufaAmount();
	bump_ = env.isJustBump();
}
// ----------------------------------------------------------- //
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actSNIFF: return "SNIFF";
	case Agent::actEXTRACT: return "EXTRACT";
	case Agent::actIDLE: return "IDLE";
	default: return "IDLE";
	}
}
