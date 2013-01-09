//
//  CPlaquette.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "headers/Plaquette.h" 

/* General Constructor for the class*/
CPlaquette :: CPlaquette(){}
    
/*Constructor for the class*/
CPlaquette :: CPlaquette( int *beads, int *neighbour){
    
    for ( int i=0; i<3; i++ ){
        
        bead_id[i] = *( beads + i );    
        neigh_id[i] = *( neighbour + i );
    }    
}

//This returns a vector of int, the first two are the shared beads, then comes the 
//corner of the first plaquette and then that of the second.
//return an array of negative integers in case there is no shared edge
vector< int > CPlaquette::Shared_Unshared( CPlaquette plaque1, CPlaquette plaque2 ){
    
    for ( int i = 1; i < 3; i++ ) {

        int bead_try = plaque1.bead_id[ i ];
        for ( int j = 1; j < 3; j++ ) {

            int bead_try2 = plaque2.bead_id[ j ];
            if ( bead_try == bead_try2 ) {

                shared.push_back( bead_try );
                break;
            }
            //If it exits from here, no common bead was found, so it must be an unshared one
            unshared.push_back( bead_try );
        }
    }
    // Check that you found 2 shared neighbours, otherwise you know the plaques are not neighbouring ones!
    if ( shared.size() != 2 ) { 
        vector< int > shared_unshared( 4, -1 );
    } 
    else {
        //At this point, you know the shared ones and one of the unshared, the remaining one on plaque2
        //is the second unshared bead
        for ( int i = 1; i < 3; i++ ) {
            int bead_try2 = plaque2.bead_id[ j ];
            if ( bead_try2 != shared[ 0 ] and bead_try2 != shared[ 1 ] ){
                unshared.push_back( bead_try2 );
                break;
            };
        };

        vector< int > shared_unshared( 4, 0 );
        shared_unshared[ 0 ] = shared[ 0 ];
        shared_unshared[ 1 ] = shared[ 1 ];
        shared_unshared[ 2 ] = unshared[ 0 ];
        shared_unshared[ 3 ] = unshared[ 1 ];

    }

    return shared_unshared;
}

/* Calculate the area of a plaquette b*h/2.0*/
double CPlaquette::area(){
    
    CVector3 v1 = edge[1].vec_prod( edge[2] ); 
    double aa = v1.mod() / 2.0;
    
    return aa;
    
}
