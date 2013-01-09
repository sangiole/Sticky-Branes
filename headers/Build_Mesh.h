//  CSystem.cpp
//  Deformable colloids
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#ifndef BUILD_MESH_H
#define BUILD_MESH_H

#include "headers/3D_Vectors.h"
#include "headers/Simu_variables.h"
#include "headers/Utils_distances.h"
#include "headers/Bead.h"
#include "headers/Plaquette.h"

CPlaquette * Build_Mesh( CBead *pbead, int n_beads, CSimu_variables *simu );
vector< vector<int> > Build_Connectivity( CBead *pbead, int n_beads, CSimu_variables *simu );
vector< vector<int> > Build_Plaquettes( CBead *pbead, vector< vector<int> > connectivity, int n_beads );
vector< vector<int> > Build_Plaquettes_Neighbours( vector< vector<int> > plaquettes );

#endif
