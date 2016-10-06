#ifndef AGENT__
#define AGENT__

#include <string>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent{
public:
	Agent(){
        trufa_size_=-1;
        bump_=false;


	pos_x=pos_y=8;

    /* Inicializamos la matriz del mapa:
    0 significa no explorado.
    -1 significa pared (bump==1).
    n significa turno de la última vez que se pasó por dicha posición.
    */

    for(int i=0; i<17; i++){
        for(int j=0; j<17; j++){
            if(j==0 || i==0 || j==16 || i==16)
                tmap[i][j]=-1;
            else
                tmap[i][j]= 0;
        }
    }

}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
	    actSNIFF,
	    actEXTRACT,
	    actIDLE
	};

    void showmap();
    int getDirection();
	void Perceive(const Environment &env);
	ActionType Think();

private:
	int trufa_size_;
	bool bump_;
	int tmap[17][17];
    int pos_x, pos_y;
    int step=1;
    int direction=0;
    ActionType last_step;

};

string ActionStr(Agent::ActionType);

#endif
