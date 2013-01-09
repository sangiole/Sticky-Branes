//
//  Utils_distances.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 05/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "3D_Vectors.h"
#include "Simu_variables.h"
#include <cmath>

// Squared distance between a couple of vectors. Applies pbc if requested 
double distance2( CVector3 v1, CVector3 v2, CSimu_variables *simu );
// Squared distance between a couple of vectors. Never apply pbc
double distance2( CVector3 v1, CVector3 v2 );

// Euclidean distance between a couple of vectors. Applies pbc if requested 
double distance(CVector3 v1, CVector3 v2, CSimu_variables *simu );
// Euclidean distance between a couple of vectors. Never apply pbc
double distance( CVector3 v1, CVector3 v2 );

//nint function since fucking hell I cannot retrieve it from std::
int nearestint (double x);
    
// Apply pbc to the vector v1 and return a vector 
CVector3 apply_pbc(CVector3 v1, CSimu_variables *simu);
