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
#include "headers/Plaquette.h"

#define endl "\n"

int main() {

    bool pbc[3];
    pbc[0] = true;
    pbc[1] = false;
    pbc[2] = true;
    CVector3 box( 10.0, 10.0, 10.0 );
    CSimu_variables simu( pbc, box );
    CSimu_variables *psimu;
    //#psimu = &simu;
    MTRand_open rand(19301304);
std::cout << box.x << " " << box.y << " " << pbc[2] << "Expected: 10.0 10.0 true " << endl;

    CVector3 v0( 1.0, 0.0, 0.0 );
    CVector3 v1( 1.0, 0.5, -1.0 );
    CVector3 v2( 0.0, 1.0, 0.0 );
    CVector3 v3, v4;
    CVector3 v5( 11.0, 12.0, 13.0);
    CVector3 v6( 5.0, 5.0, 5.0);

v4 = 2.2;
std::cout << v4.x << " " << v4.y << " " << v4.z << "Expected: 2.2 2.2 2.2 " << endl;

v3 = v2 - v1;
std::cout << v3.x << " " << v3.y << " " << v3.z << "Expected: -1 0.5 1 " << endl;

v3 = v2 * v1;
std::cout << v3.x << " " << v3.y << " " << v3.z << "Expected: 0 0.5 0 " << endl;

v3 = v2 / v1;
std::cout << v3.x << " " << v3.y << " " << v3.z << "Expected: 0 2 0 " << endl;

v3 = v2.vec_prod( v0 );
std::cout << v3.x << " " << v3.y << " " << v3.z << "Expected: (0,0,-1) " << endl;

double sum = v2.sum(); 
std::cout << sum << "Expected: 1 " << endl;

double mod = v1.mod(); 
std::cout << mod << "Expected: 1.5 " << endl;

mod = v1.mod2(); 
std::cout << mod << "Expected: 2.25 " << endl;

std::cout << distance2( v2, v1 ) << "Expected  2.25" <<endl;
std::cout << distance( v2, v1 ) << "Expected  1.5" <<endl;

std::cout << nearestint(0.4999) << "Expected  0" <<endl;
std::cout << nearestint(0.5000)<< "Expected  0" <<endl;
std::cout << nearestint(0.6)  << "Expected  1" <<endl;
std::cout << nearestint(0.7) << "Expected  1" <<endl;
std::cout << nearestint(0.8) << "Expected  1" <<endl;

v3 = v5 - v6;
std::cout << v3.x << " " << v3.y << " " << v3.z << "Expected: 6 7 8 " << endl;

v3 = apply_pbc(v5 - v6, &simu);
std::cout << v3.x << " " << v3.y << " " << v3.z << "Expected: -4 7 -2 " << endl;


//Try the bead routine
//
CVector3 dr(0.1,0.2,0.3);
CVector3 pos(1.0,2.0,3.0);

CBead bead1(pos, true);
std::cout << "POS OF BEAD" <<endl;
std::cout << bead1.pos_now->x << "Expected  1" <<endl;
std::cout << bead1.pos_now->y << "Expected  2" <<endl;
std::cout << bead1.pos_now->z << "Expected  3" <<endl;
std::cout << bead1.pos_new->x << "Expected  ??" <<endl;
std::cout << bead1.pos_new->y << "Expected  ??" <<endl;
std::cout << bead1.pos_new->z << "Expected  ??" <<endl;

bead1.try_move_bead(dr);
std::cout << "TRY TO MOVE BEAD" <<endl;
std::cout << bead1.pos_now->x << "Expected  1.0" <<endl;
std::cout << bead1.pos_new->x << "Expected  1.1" <<endl;
std::cout << bead1.pos_now->y << "Expected  2.0" <<endl;
std::cout << bead1.pos_new->y << "Expected  2.2" <<endl;
std::cout << bead1.pos_now->z << "Expected  3.0" <<endl;
std::cout << bead1.pos_new->z << "Expected  3.3" <<endl;

bead1.update_bead_pos();
std::cout << "UPDATED BEAD" <<endl;
std::cout << bead1.pos_new->x << "Expected  1.0" <<endl;
std::cout << bead1.pos_now->x << "Expected  1.1" <<endl;
std::cout << bead1.pos_new->y << "Expected  2.0" <<endl;
std::cout << bead1.pos_now->y << "Expected  2.2" <<endl;
std::cout << bead1.pos_new->z << "Expected  3.0" <<endl;
std::cout << bead1.pos_now->z << "Expected  3.3" <<endl;

std::cout << "ACTIVE:"<<bead1.active << "Expected  true = 1" <<endl;

int bead_id[3] = {1,2,3};
int neigh_id[3] = {10,20,30};
CVector3 edges[3];
CVector3 *pedges;
int *pbead;
int *pneigh;

pbead = bead_id;
pneigh = neigh_id;
pedges = edges;

CVector3 norm;
norm = 44.4;
edges[0] = 1.0;
edges[1] = 2040.32;
edges[2] = 2.342;

edges[0].x = 1.0;
edges[0].y = 0.0;
edges[0].z = 0.0;
edges[1].x = 0.0;
edges[1].y = 0.0;
edges[1].z = 1.0;
edges[2].x = 1.0;
edges[2].y = 0.0;
edges[2].z = 1.0;

CPlaquette plaque( norm, norm, pbead, pedges, pneigh );
std::cout << plaque.normal.x << "Expected  44.4" <<endl;
std::cout << plaque.normal.y << "Expected  44.4" <<endl;
std::cout << plaque.normal.z << "Expected  44.4" <<endl;

std::cout << plaque.edge[0].x << "Expected  1.0" <<endl;
std::cout << plaque.edge[1].y << "Expected  0.0" <<endl;
std::cout << plaque.edge[2].z << "Expected  1.0" <<endl;

std::cout << plaque.bead_id[0] << "Expected  1" <<endl;
std::cout << plaque.bead_id[1] << "Expected  2" <<endl;
std::cout << plaque.bead_id[2] << "Expected  3" <<endl;

std::cout << plaque.neigh_id[0] << "Expected  10" <<endl;
std::cout << plaque.neigh_id[1]<< "Expected  20" <<endl;
std::cout << plaque.neigh_id[2] << "Expected  30" <<endl;

std::cout << plaque.area() << "Expected  0.5" <<endl;

}
