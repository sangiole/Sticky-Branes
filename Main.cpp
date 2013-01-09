//
//  Main.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//


#include <iostream>
#include <cmath>
#include "headers/3D_Vectors.h"
#include "headers/Simu_variables.h"
#include "headers/Utils_distances.h"
#include "headers/MTrand.h"
#include "headers/Bead.h"

#define endl "\n"

int main() {

    CSimu_variables simu;
    MTRand_open rand(19301304);

//CVector3 v1,v2
//CVector3 v3( 15.1,10.0,11.0 )

//v1 = 1.0
//v2 = 0.0
//v2 = 15.0

//int aaa[3];
//aaa[0] = 22;

std::cout << rand() << endl;
std::cout << rand() << endl;
std::cout << rand() << endl;
std::cout << rand() << endl;
std::cout << rand() << endl;
std::cout << rand() << endl;
std::cout << rand() << endl;
//std::cout << distance( v2, v1 )mod << " \n";
//std::cout << distance2( v2, v1 )mod << " \n";
//std::cout << apply_pbc( v3 ).x  << " \n";

}
