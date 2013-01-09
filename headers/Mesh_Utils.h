//  Utilities to calculate curvature and other quantities on a triangular mesh 
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#ifndef MESH__UTILS_H
#define MESH_UTILS_H

#include "headers/3D_Vectors.h"
#include "headers/Simu_variables.h"
#include "headers/Utils_distances.h"
#include "headers/Bead.h"
#include "headers/Plaquette.h"
#include <vector>

vector< double > Mean_Curvature_Area_At_Vertex( CBead *pbead, int vertex );
vector< double > Gaussian_Curvature_Area_At_Vertex( CBead *pbead, int vertex ); 
double Mean_Curvature_At_Vertex( CBead *pbead, int vertex ); 
double Gaussian_Curvature_At_Vertex( CBead *pbead, int vertex ); 
double Area_At_Vertex( CBead *pbead, int vertex );
double cotan( double x );

#endif
