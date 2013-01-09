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
#include "headers/Curv_Area_Norm.h"
#include <cmath.h>
#include <vector>

// Given the bead positions and a specific bead (the vertex), returns the curvature and the "area" associated to
// that vertex to calculate the H^2 dA term for the bending integral
Curv_Area_Norm Mean_Curvature_Area_At_Vertex( CBead *pbead, int vertex ){

    Curv_Area_Norm c_a_n;
    double area;
    double curvature;

    //Number of plaques to which a vertex belong to, necessary to build 1-Ring neighbourhood
    //If the bead is in the bulk, this is equal to the number of neighbours, otherwise
    //nplaques = nneighbours - 1
    //For the time being, check that you only have the bulk case since you have not checked that all
    //formulas are also retained in the presence of boundaries
    //
    int nplaques = pbead[ vertex ]->myplaquettes.size();
    int nneighs = pbead[ vertex ]->nneighbours; 

    if ( nplaques != nneighs ) {
        std::cout << "This case has not been tested, program exit";
        exit(111);
    } 
    else  {
        vector< vector<double> > cot_angle( n_beads, 0.0 );
        vector< CVector3 > xij( n_beads );

        // First build the 1-Ring neighbourhood
        double total_area = 0.0;
        
        for ( int i = 0; i < nplaques; i++ ){

            int v1,v2,v3,va,vb,vc;
            //pick a plaquette and the other two neighbours that form it
            int plaque_id = pbead[ vertex ]->myplaquettes[ i ];
            int v1 = vplaquette[ plaque_id ].bead_id[ 0 ];
            int v2 = vplaquette[ plaque_id ].bead_id[ 1 ];
            int v3 = vplaquette[ plaque_id ].bead_id[ 2 ];

            if ( vertex == v1 ) {
                va == v1;
                vb == v2;
                vc == v3;
            } 
            else if ( vertex == v2 ){
                va == v2;
                vb == v1;
                vc == v3;
            } 
            else {
                va == v3;
                vb == v1;
                vc == v2;
            };

            // Now first take the a-b vector and calculate the opposite angle 
            CVector3 veca,vecb,vecc;
            CVector3 vec_ab,vec_ac,vec_bc;

            veca = ( pbead[ va ]->pos_now->x, pbead[ va ]->pos_now->y, pbead[ va ]->pos_now->z );
            vecb = ( pbead[ vb ]->pos_now->x, pbead[ vb ]->pos_now->y, pbead[ vb ]->pos_now->z );
            vecc = ( pbead[ vc ]->pos_now->x, pbead[ vc ]->pos_now->y, pbead[ vc ]->pos_now->z );

            vec_ab = vecb - veca;
            vec_ac = vecc - veca;
            vec_bc = vecc - vecb;
            double mod_ab = vec_ab.mod();
            double mod_ac = vec_ac.mod();
            double angle_a =  vec_ab.angle( vec_ac ); 
            double angle_b = -vec_ab.angle( vec_bc );
            double angle_c =  -vec_ac.angle( -vec_bc ); 
            double cotan_b = std::cotan( angle_b );
            double cotan_c = std::cotan( angle_c );

            xij[ vb ].x = vec_ab.x;
            xij[ vb ].y = vec_ab.y;
            xij[ vb ].z = vec_ab.z;
            xij[ vc ].x = vec_ac.x;
            xij[ vc ].y = vec_ac.y;
            xij[ vc ].z = vec_ac.z;
           
            // it is right, angle in c is associated with vector vb and viceversa...
            cot_angle[ vb ].push_back( cotan_c );
            cot_angle[ vc ].push_back( cotan_b );

            double area_now = Mixed_Area( vec_ab, vec_ac, mod_ab, mod_ac, angle_a, angle_b, angle_c, cotan_b, cotan_c );
            area[ i ].push_back( area_now );
            total_area += area_now;

        }
        //Ok, at this point you should have all the data you need in cot_angle and xij to calculate the area associated
        //to the vertex and the mean curvature at the vertex
        CVector3 k_beltrami( 0.0 );

        for ( i = 0; i < nneighs, i++ ) {
            double half_area = 0.5 * total_area;
            k_beltrami.x += half_area * ( cot_angle[ i ][ 0 ] + cot_angle[ i ][ 1 ] ) * xij[ i ].x;
            k_beltrami.y += half_area * ( cot_angle[ i ][ 0 ] + cot_angle[ i ][ 1 ] ) * xij[ i ].y;
            k_beltrami.z += half_area * ( cot_angle[ i ][ 0 ] + cot_angle[ i ][ 1 ] ) * xij[ i ].z;
        };

        c_a_n.curvature = 0.5 * K_Beltram.mod();// curvature
        c_a_n.area = total_area  ;// area
        c_a_n.normal = K_Beltram / K_Beltram.mod();// direction of the normal at the vertex; 
    }

    return c_a_n; 
}

vector< double > Gaussian_Curvature_Area_At_Vertex( CBead *pbead, int vertex ); 
//double Mean_Curvature_At_Vertex( CBead *pbead, int vertex ); 
//double Gaussian_Curvature_At_Vertex( CBead *pbead, int vertex ); 
//double Area_At_Vertex( CBead *pbead, int vertex );
//

double cotan( double x ){ return tan( M_PI - x ) };

//Given a triangle, returns the associated "Mixed Area" to the triangle, 
//following the recipe given in XXXX.
//It is implied that the "ij" vector is vec1, so that the angle in the vertex "i" is given 
//by asin( | vec1.vec_prod(vec2) | / vec1.mod/ vec2.mod )
double Mixed_Area( CVector3 vec_ab, CVector3 vec_ac, double mod_ab, double mod_ac, double angle_a, double angle_b, 
                double angle_c, double cotan_b, double cotan_c ){

    //first check if triangle is obtuse. if not, apply Voronoi formula
    double area = 0.0;

    //If obtuse, use T/2 or T/4 depending on whether the angle at "i" is the obtuse one or not
    if ( angle_a > M_PI/2.0 or angle_b > M_PI/2.0 or angle_c > M_PI/2.0 ) {
        double area_triangle = vec_ab.vec_prod( vec_ac ).mod() / 2.0;
        if ( angle_a > M_PI/2.0 ) { 
            area = area_triangle / 2.0;
        }
        else {
            area = area_triangle / 4.0;
        }
    }
    // else use normal Voronoi area...
    else { 
        area = 1.0 / 8.0 * ( mod_ab*mod_ab * cotan_c +  mod_ac*mod_ac * cotan_b );  
    }

    return area;
};

#endif
