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
#include <vector>

using namespace std;

/* Defines the plaquettes, i.e. the mesh given particles' positions. 
 1) Create bonds between all particles that can effectively bond given the constraint on the distances
    if sigma is the hard sphere ( sigma < L < sqrt(3)sigma )
 2) Define the ternes that build up each plaquette
 3) Build the plaquette characteristics: centre, normal and the likes 
 
 */
vector< CPlaquette > Build_Mesh( CBead *pbead, int n_beads, CSimu_variables *simu ){
    
    int i,j,k;
    vector< CPlaquette > vplaquette;
    
    // Build the connectivity matrix. matrix[i][j]=1 if i and j are neighbours, 0 otherwise 
    vector< vector<int> > connectivity = Build_Connectivity( pbead, n_beads, simu )
    
    //Build the neighbours list for your system
    for ( i = 0; i < n_beads, i ++ ){
        for ( std::vector<int>::iterator it = connectivity[ i ].begin(); it != connectivity[i].end(); it ++ ) {
            pbead->neighbour.push_back( *it );
            pbead->nneighbours += 1;
        }
    }
    // Given the connectivity matrix build the triangular plaquettes of the mesh and update bead info
    vector< vector<int> > plaquettes = Build_Plaquettes( pbead, connectivity, n_beads );
    // Ok, at this point you have all the terns correctly stored. Next, for each tern, tell its neighbouring ones 
    // Each has exactly 3 ( or less if it is a boundary plaquette in a non-closed structure...),
    // each of which share an edge 
    vector< vector<int> > plaquettes_neighbours = Build_Plaquettes_Neighbours( plaquettes );

    // Now store a vector Plaquette to which you will
    // point and you have to build all Plaquettes accordingly...
    int nplaques = plaquettes.size()

    //Now set all the plaquettes characteristics!
    for ( int plaque = 0; plaque < nplaques; plaque++ ) {

        CVector3 v1,v2,v3,normal;

        //Build the normal
        int i = plaquettes[ plaque ][0];
        int j = plaquettes[ plaque ][1];
        int k = plaquettes[ plaque ][2];
        
        v1 = ( pbead[i]->pos_now->x, pbead[i]->pos_now->y, pbead[i]->pos_now->z );
        v2 = ( pbead[j]->pos_now->x, pbead[j]->pos_now->y, pbead[j]->pos_now->z );
        v3 = ( pbead[k]->pos_now->x, pbead[k]->pos_now->y, pbead[k]->pos_now->z );

        normal = v2.vec_prod(v1); 
        vplaquette[ plaque ].normal = normal / normal.mod();
        vplaquette[ plaque ].normal_centre = ( v1 + v2 + v3 ) / 3.0;

        vplaquette[ plaque ].pedge[0] = v2 - v1;
        vplaquette[ plaque ].pedge[1] = v3 - v1;
        vplaquette[ plaque ].pedge[2] = v3 - v2;

        vplaquette[ plaque ].neigh_id[0] = plaquettes_neigh[plaque][0];
        vplaquette[ plaque ].neigh_id[1] = plaquettes_neigh[plaque][1];
        vplaquette[ plaque ].neigh_id[2] = plaquettes_neigh[plaque][2];

    }

    return vplaquette
                
}

//This function takes pbead and the positions and returns the connectivity matrix
vector< vector<int> > Build_Connectivity( CBead * pbead, int n_beads, CSimu_variables *simu ){

    //Prepare a 2D array needed to store the list of neighbours
    double lower = simu->sigma;
    double upper = std::sqrt(3.0) *  lower;
    CVector3 v1,v2;
    bool condition_bond;

    vector< vector<int> > connectivity( n_beads, 0 );
    
    //Set to zero the elements of the connectivity matrix and the plaquettes terns
    for ( i = 0; i < n_beads, i++ ){ connectivity[ i ].resize( n_beads, 0 ); }

    for ( i =0 ; i < n_beads, i++ ) {
        
        if ( pbead[i]->active ) { n_active_beads += 1;};

        //v1 just gives the position of the initial bead
        v1 = ( pbead[i]->pos_now->x, pbead[i]->pos_now->y, pbead[i]->pos_now->z );
        
        for ( j = i + 1; j < n_beads; j++ ){
        
            //v2 is the position of the candidate neighbour
            v2 = ( pbead[j]->pos_now->x, pbead[j]->pos_now->y, pbead[j]->pos_now->z );
            //Check that the distance is right to create a bond
            condition_bond =  ( distance( v2, v1, simu ) < upper ) &&  distance( v2, v1, simu ) > lower; 
            //If two beads are neighbours, update the neighbour list accordingly
            if ( condition_bond ) connectivity[ i ][ j ] = connectivity[ j ][ i ] = 1; 
        }
    }
    return connectivity;
}

//This function takes the connectivity matrix and returns a set of terns each constituting a plaquette
vector< vector<int> > Build_Plaquettes( CBead * pbead, vector< vector<int> > c_matrix, int n_beads ) {
    // Build the plaquettes -i.e. a tern- in this way:
    // 1 - Cycle over all atoms "i" 
    // 2 - Cycle over all neighbours "j" that have cardinal number greater than "i"
    // 3 - Cycle over all neighbours "k" of "i" and i,j <k 
    // If C is an element of the connectivity matrix, there is a plaquette if c_ij * c_ik * c_jk = 1. If you enforce
    // i>j>k all the plaquette are also given in this way exactly one time
    //
    vector< vector<int> > plaquettes;
    int num_plaquettes = 0;

    for ( int bead1 = 0; bead1 < n_beads, bead1++ ){

        for ( int bead2 = bead1 + 1; bead2 < n_beads; bead2++ ) {

            for ( int bead3 = bead2 + 1; bead3 < n_beads; bead3++ ) {

                if (connectivity[ bead1 ][ bead2 ] * 
                    connectivity[ bead1 ][ bead3 ] * 
                    connectivity[ bead2 ][ bead3 ] == 1 ) {

                        //This also means all three beads belong to this plaquette. 
                        num_plaquettes += 1;
                        pbead[ bead1 ]->myplaquettes.push_back( num_plaquettes ); 
                        pbead[ bead2 ]->myplaquettes.push_back( num_plaquettes ); 
                        pbead[ bead3 ]->myplaquettes.push_back( num_plaquettes ); 

                        plaquettes.push_back( bead1 );
                        plaquettes.push_back( bead2 );
                        plaquettes.push_back( bead3 );

                }
            } 
        }         
    }
    return plaquettes
}

//This function takes the plaquettes and gives back another vector stating for each one which are its neighbours
vector< vector<int> > Build_Plaquettes_Neighbours( vector< vector<int> > terns ){

    int nplaques = terns.size();
    vector< vector<int> > terns_neigh;

    for ( int i = 0; i < nplaques; i++ ) {

        int i1 = terns[ i ][0];
        int i2 = terns[ i ][1];
        int i3 = terns[ i ][2];
        int counter = 0;

        for ( int j = i + 1; j < nplaques; j++ ){
        
            int j1 = terns[ j ][0];
            int j2 = terns[ j ][1];
            int j3 = terns[ j ][2];
            if ( i1 == j1 or i1 == j2 or i1 == j3 ) counter += 1;
            if ( i2 == j1 or i2 == j2 or i2 == j3 ) counter += 1;
            if ( i3 == j1 or i3 == j2 or i3 == j3 ) counter += 1;
        }

        // Check for impossible case and raise an error
        if ( counter == 3 ) {
            std::cout << "Impossible to have equal beads in different plaques!";
            exit(100);
        }

        //This is the case of two plaques sharing an edge, hence count them as neighbours
        else if ( counter == 2 ) {

            terns_neigh[ i ].push_back( j );
            terns_neigh[ j ].push_back( i );

        }
    }

    return terns_neigh;
}
