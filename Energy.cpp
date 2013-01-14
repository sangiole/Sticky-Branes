//  Stefano Angioletti-Uberti. Is the author of this program, help from science 
//  CPlaquette.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "headers/Energy.h"
#include <vector>

using namespace std;

// Returns the total energy of the mesh defined by pplaquette
// Returns a negative value is some impossible feature is present in the system (i.e. overlap between beads)
double tot_energy_system( CColloid *pcolloids, int n_colloids ){

    double energy = 0.0 ;
    for ( i = 0; i< n_colloids, i++ ){

        energy += bending_energy_colloid( pcolloids + i );

    }
    return energy;
    
};

// Returns the total bending energy of the mesh defined by pplaquette
double bending_energy_colloid( CColloid *pcolloid ){

    //Step 1: Calculate the curvature at each vertex of the system of plaquettes
    for ( i = 0; i < pcolloid->num_beads; i++ ) {


        
        
        }
    //
    //Step 2: Integrate the energy by assigning to each vertex the baricentric area as described in the paper
    //
    //
    
    
};

// Returns the partial energy in the case when the bead = bead_id is moved by the vector dx
// Returns a negative value IF the move generates an impossible configuration ( i.e. overstretched bond )
double partial_energy_bead( CPlaquette *pplaquette, int n_plaquettes, int bead_id ){
    
};

double partial_energy_plaquette( CPlaquette *pplaquette, int n_plaquettes, int plaq1, int plaq2 ){
    
};

double absorption_energy( CPlaquette *pplaquette, int n_plaquettes ){
    
};

#endif
