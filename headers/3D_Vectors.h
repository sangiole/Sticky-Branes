//
//  3D_Vectors.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 05/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//

#ifndef THREED_VECTORS_H
#define THREED_VECTORS_H
#include <iostream>
#include <cmath>

class CVector3 {

public:
    CVector3 ();
    CVector3 ( double, double, double );
    double x,y,z;
    double dot_prod( CVector3 );
    CVector3 vec_prod( CVector3 );
    double mod();
    double mod2();
    double sum();
    double angle( CVector3 );
    CVector3 operator + ( CVector3 );
    CVector3 operator - ( CVector3 );
    void operator = ( CVector3 );
    void operator = ( double );
    CVector3 operator * ( CVector3 );
    CVector3 operator / ( CVector3 );
    CVector3 operator * ( double );
    CVector3 operator / ( double );
};

#endif
