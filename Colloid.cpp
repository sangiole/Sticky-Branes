//
//  CSystem.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <cmath>
#include "headers/3D_Vectors.h"
#include "headers/Simu_variables.h"
#include "headers/Bead.h"
#include "headers/Plaquette.h"
#include "headers/Utils_distances.h"
#include "headers/Build_Mesh.h"
#include "headers/Mesh_Utils.h"
#include "headers/Colloid.h"
#include <vector>

using namespace std;

CColloid::CColloid(){}

CColloid::CColloid( CBead *pfbead, int n_beads, CSimu_variables *simu ){
    int i,j,k;
    num_beads = n_beads;
    vplaquette = Build_Mesh( pfbead, n_beads, simu );
    pbead = pfbead;
    n_active_beads = 0;
    n_passive_beads = 0;
    centre = 0.0;

    for ( i = 0; i < n_beads, i++ ) {
        centre.x +=  pfbead[i]->pos_now->x;
        centre.y +=  pfbead[i]->pos_now->y;
        centre.z +=  pfbead[i]->pos_now->z;

        if ( pfbead[i]->active ) n_active_beads += 1
    }

    centre.x /= n_beads;
    centre.y /= n_beads;
    centre.z /= n_beads;
    n_passive_beads = n_beads - n_active_beads;

}

// Returns the total bending energy of the colloid 
double CColloid::Total_Bending_Energy(){

    double energy = 0.0;
    for ( int i = 0; i < num_beads; i++ ){
        
        energy += Bending_Energy_Bead( pbead, i );
    }
    
    return energy;

}

// Returns the change in energy when a single bead is moved by a vector vec 
double CColloid::Partial_Bending_Move_Energy( int bead, CVector3 dr ){
    
    // 1) First calculate the energy due to the curvature at the bead position and its neighbours
    // 2) Then do the same for its neighbours 
    // 3) Then move the bead and repeat the previous to points
    // 4) Finally, take the difference and reposition the bead at its initial position

    // Step 1
    double energy_old = Bending_Energy_Bead( pbead, bead );

    // Step 2
    for ( int i = 0; i < pbead[ bead ]->nneighbours; i++ ){

        int bead2 = pbead[ bead ]->neighbour[ i ];
        energy_old += Bending_Energy_Bead( pbead, bead2 );
    
    }
   
    // Step 3
    ( *pbead[ bead ] ).move_bead( dr );

    double energy_new = Bending_Energy_Bead( pbead, bead );

    for ( int i = 0; i < pbead[ bead ]->nneighbours; i++ ){

        int bead2 = pbead[ bead ]->neighbour[ i ];
        energy_new += Bending_Energy_Bead( pbead, bead2 );

    }
 
    // End by re-putting the system in its initial position, you might accept it only later if needed...
    pbead[ bead ]->pos_now = pbead[ bead ]->pos;  
    return double denergy = energy_new - energy_old;

}

// Returns the contribute to the bending energy of a specific bead 
double CColloid::Bending_Energy_Bead( int bead ){
    
    Curv_Area_Norm c_a_n = Mean_Curvature_Area_At_Vertex( pbead, bead );
    double energy = c_a_n.curvature * c_a_n.curvature * c_a_n.area;
    return energy;

}

// Returns the energy when a vertex is exchanged between plaquettes
// plaquette is plaq1 and its neighbouring plaquette
double CColloid::Partial_Bending_Change_Plaquettes( int plaq1, int neigh ){

    //Avoid looking for non-existent neighbour!
    if ( neigh < 3 ) {
        plaq2 = vplaquette[ plaq1 ].neigh_id[ neigh ];
        vector< int > shared_unshared = Shared_Unshared( plaq1, plaq2 );
        if ( shared_unshared[ 0 ] > -1 ){ //This is true if effectively everything is ok, otherwise there must be a mistake!
            beadA = shared_unshared[2];
            beadD = shared_unshared[3];
            beadB = shared_unshared[0];
            beadC = shared_unshared[1];






        }

    }



    
    //1) Calculate the energy of the 4 beads involved
    for ( int i = 0; i < pbead[ bead ]->nneighbours; i++ ){

        int bead2 = pbead[ bead ]->neighbour[ i ];
        energy_new += Bending_Energy_Bead( pbead, bead2 );

    }
    //2) Change the mesh so as that the plaquettes are changed accordingly.
    //   Basically, you need to change the attributes vplaquette and beads
    //   For the plaquette, what change is their neighbours
    //   For the beads, they change neighbours and the plaquette to which they belong to
    //3) Calculate the energy of the 4 beads in the new configuration
    //4) Get back to the previous mesh
    
    return double energy

}

