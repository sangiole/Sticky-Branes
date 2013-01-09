//
//  CPlaquette.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PLAQUETTE_H
#define PLAQUETTE_H
#include "3D_Vectors.h"

class CPlaquette {

    public:
    /*Beads composing the plaquette*/
    int bead_id[3];
    /*ID of the neighbouring plaquettes*/
    int neigh_id[3];
    
    //Constructors
    CPlaquette();
    CPlaquette( int *pbead_id, int *pneigh_id);
   
    //This returns a vector of int, the first two are the shared beads, then comes the 
    //corner of the first plaquette and then that of the second.
    //return an array of negative integers in case there is no shared edge
    vector< int > CPlaquette::Shared_Unshared( CPlaquette plaque1, CPlaquette plaque2 ){
    // self-descriptive
    double area();
    // a XOR  b returns the ID of the unshared beads between neighbour
    int operator^(CPlaquette neighbour); 

};

#endif
