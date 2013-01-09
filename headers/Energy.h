//
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifndef ENERGY_H
#define

#include "3D_Vectors.h"
#include "Plaquette.h"
#include "Bead.h"
#include <cmath>
#include <vector>

// This returns the total energy of the system of colloids
double tot_energy_system( CColloid *pcolloids, int n_colloids );

// Returns the total bending energy of the colloid pointed by pcolloid
double bending_energy_colloid( CColloid *pcolloid );

// This returns the partial energy change in the system of beads pointed by pbeads when "bead_id" is moved
double partial_energy_bead( CBead *pbeads, int n_beads, int bead_id );

// This returns the partial energy change when two plaquettes pointed by plaquette1 anb plaquette2 exchange their vertices 
double partial_energy_exchange_vertex( CPlaquette pplaq1, CPlaquette pplaq2 );

//This calculate the absorption energy of a system of beads 
double absorption_energy( CBead *pbeads, int n_beads );

#endif
