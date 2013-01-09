//
//  CSystem.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include "headers/3D_Vectors.h"
#include "headers/Simu_variables.h"
#include "headers/Utils_distances.h"
#include "headers/Bead.h"
#include "headers/Plaquette.h"

class CColloid {
    
public:
    CVector3 centre;
    CBead *pbead;
    vector< CPlaquette > vplaquette;
    int num_beads;
    int n_active_beads, n_passive_beads, n_beads;
   
    CDefColloid();
    CDefColloid( CBead *pbead, int n_beads, Simu_variables *simu );
    // Output the positions of all the beads in the system 
    void Print_System(); 
    // Returns the bending energy of the system 
    double Total_Bending_Energy(); 
    // Returns the energy when a single bead is moved by dr 
    double Partial_Bending_Move_Energy( int bead, CVector3 dr ){
    // Returns the energy when a vertex is exchanged between plaquettes 
    double Partial_Bending_Change_Plaquettes( int plaq1, int plaq2 ); 
    // Returns the bending contribution to the energy of the bead
    double Bending_Energy_Bead( int bead ){
    
};    

#endif
