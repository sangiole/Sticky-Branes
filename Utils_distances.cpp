//
//  Utils_distances.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 05/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "headers/Utils_distances.h"
#include "headers/Simu_variables.h"

double distance2( CVector3 v1, CVector3 v2, CSimu_variables *simu ){
    
    CVector3 dx;
    dx = v2 - v1;
    dx = apply_pbc( dx, simu );
    
    return dx.mod2();
    
};

double distance2( CVector3 v1, CVector3 v2 ){
    
    CVector3 dx;
    dx = v2-v1;
    return dx.mod2();
    
};

double distance(CVector3 v1, CVector3 v2, CSimu_variables *simu){
    
    return sqrt( distance2( v1, v2, simu ) );
    
};

double distance(CVector3 v1, CVector3 v2){
    
    return sqrt( distance2( v1, v2 ) );
    
};

int nearestint(double x){
    
    int num;
    if ( x - int( x ) > 0.5 ) {
        num = int( x ) + 1; 
    }
    else {
        num = int(x);
    }
    return num;
};

CVector3 apply_pbc(CVector3 v1, CSimu_variables *simu){
    
    CVector3 vscaled = v1 / simu->box;
    CVector3 vfinal = v1;
    if ( simu->pbc[0] ) vfinal.x = v1.x - simu->box.x * nearestint(vscaled.x);
    if ( simu->pbc[1] ) vfinal.y = v1.y - simu->box.y * nearestint(vscaled.y);
    if ( simu->pbc[2] ) vfinal.z = v1.z - simu->box.z * nearestint(vscaled.z);
    return vfinal;
    
};
