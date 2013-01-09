//
//  CBead.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BEAD
#define BEAD

#include "3D_Vectors.h"
#include <vector>

class CBead {
    
public:

    // Actual position of the bead and trial position
    CVector3 *pos;
    CVector3 *pos_now; 
    CVector3 *pos_new;
    CVector3 normal;
    std::vector<int> neighbour;
    std::vector<int> myplaquettes;
    int nneighbours;
    // if active a bead can be moved during the simulation
    bool active;

    // Function that moves a particle 
    void move_bead(CVector3);
    // Function that MOVES a particle 
    void update_bead_pos();

    //Constructors
    CBead();
    CBead (CVector3 v1, bool activity);

};

#endif
