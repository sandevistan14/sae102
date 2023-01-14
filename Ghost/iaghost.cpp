//*****************************************************************************
//*************************     Initialisation     ****************************
//*****************************************************************************
#include <iostream>
#include <thread>
#include <fstream>
#include <map>
#include <vector>
#include "mingl/mingl.h"
#include "mingl/gui/sprite.h"
#include "GhostH/iaghost.h"
#include "type.h"
#include <cmath>
using namespace std;


//*****************************************************************************
//*****************************     nbsortie     ******************************
//*****************************************************************************
vector<bool> nbsortie(unsigned y , unsigned x, CMat map){
    vector<bool> sortie = {true,true,true,true};

    if (map[y-1][x] == 'X'){sortie[0] = false;}
    if (map[y][x+1] == 'X'){sortie[1] = false;}
    if (map[y+1][x] == 'X'){sortie[2] = false;}
    if (map[y][x-1] == 'X'){sortie[3] = false;}
    return sortie;
}

//*****************************************************************************
//***********************    calcule distance     *****************************
//*****************************************************************************
vector <float> CalculeDistance (vector<bool> sortie,unsigned yg , unsigned xg,
                                unsigned yp , unsigned xp){
//        for (unsigned i = 1;i < sortie.size(); ++i){
//            cout << sortie[i] << " ";
//        }
//        cout << endl;
    vector<float> distance ={1000000,1100000,1000000,1000000};
    for(unsigned i = 0;i < sortie.size();++i){
        if (sortie[i] == true){
            if (i == 0){
            distance[i] = sqrt(((xp-xg)*(xp-xg))+((yp-(yg-1))*(yp-(yg-1))));;
            }
            if (i == 1){
            distance[i] = sqrt(((xp-(xg+1))*(xp-(xg+1)))+((yp-yg)*(yp-yg)));;
            }
            if (i == 2){
            distance[i] = sqrt(((xp-xg)*(xp-xg))+((yp-(yg+1))*(yp-(yg+1))));;
            }
            if (i == 3){
            distance[i] = sqrt(((xp-(xg-1))*(xp-(xg-1)))+((yp-yg)*(yp-yg)));;
            }
        }
    }
    return distance;
}
//*****************************************************************************
//***********************    calcule distance     *****************************
//*****************************************************************************
unsigned TrouveIndiceMinDanstab (vector<float> Vec){
//    for (unsigned i = 1;i < Vec.size(); ++i){
//        cout << Vec[i] << endl;
//    }
    unsigned imin = 0;
    unsigned Vecmin = Vec[0];
    for (unsigned i = 1;i < Vec.size(); ++i){
        if(Vec[i] < Vecmin){
//            cout << Vec[i] << "   " << Vecmin << endl;
            Vecmin = Vec[i];
            imin = i;
        }
    }
    return imin;
}

//*****************************************************************************
//**************************    déplacement     *******************************
//*****************************************************************************
void MOVE(vector<bool> sortie,unsigned yg , unsigned xg,
                          unsigned yp , unsigned xp, Entity & entity)
{
    vector<float> distance = CalculeDistance(sortie,yg,xg,yp,xp);
//    for (unsigned i = 1;i < distance.size(); ++i){
//        cout << distance[i] << endl;
//    }
    unsigned imin = TrouveIndiceMinDanstab(distance);
    if(imin == 0){entity.viewdirection = "Top";}
    if(imin == 1){entity.viewdirection = "Right";}
    if(imin == 2){entity.viewdirection = "Bottom";}
    if(imin == 3){entity.viewdirection = "Left";}
}
