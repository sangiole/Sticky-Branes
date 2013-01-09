//
//  3D_Vectors.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 05/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <cmath>
#include "headers/3D_Vectors.h"
//#include "Global_variables.h"

/* More generic constructor for the object */
CVector3::CVector3(){};

/* Less generic constructor for the object */
CVector3::CVector3(double xx, double yy, double zz){
    x = xx;
    y = yy;    
    z = zz;
};

/* dot product with other member */
double CVector3::dot_prod(CVector3 v1){
    
    double dotprod = 0.0;
    dotprod += x * v1.x;
    dotprod += y * v1.y;
    dotprod += z * v1.z;
    return dotprod;
    
};

/* Vector product with other member */
CVector3 CVector3::vec_prod(CVector3 v1){
   
    double va[3],vb[3],vc[3];

    vc[0] = vc[1] = vc[2] = 0.0;
    va[0] = x;
    va[1] = y;
    va[2] = z;
    vb[0] = v1.x;
    vb[1] = v1.y;
    vb[2] = v1.z;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            for (int k=0; k<3; k++) {
                vc[k] += va[i] * vb[j] * ( (i-j) * (j-k) * (k-i) / 2 ); 
                
            }
        }
    }
   
    CVector3 vprod;

    vprod.x = vc[0];
    vprod.y = vc[1];
    vprod.z = vc[2];
    
    return vprod;
    
};


/* Sum of two vectors */
CVector3 CVector3::operator + (CVector3 v1){
    
    CVector3 sum;
    sum.x = x + v1.x;
    sum.y = y + v1.y;
    sum.z = z + v1.z;
    return sum;
    
};

/* Difference of two vectors */
CVector3 CVector3::operator - (CVector3 v1){
    
    CVector3 diff;
    diff.x = x - v1.x;
    diff.y = y - v1.y;
    diff.z = z - v1.z;
    return diff;
    
};

/* Component-wise product of two vectors */
CVector3 CVector3::operator * (CVector3 v1){
    
    CVector3 mult;
    mult.x = x * v1.x;
    mult.y = y * v1.y;
    mult.z = z * v1.z;
    return mult;
    
};

/* Product of a vector with a scalar */
CVector3 CVector3::operator * (double a){
    
    CVector3 mult;
    mult.x = x * a;
    mult.y = y * a;
    mult.z = z * a;
    return mult;
    
};
/* Division of a vector with a scalar */
CVector3 CVector3::operator / (double a){
    
    CVector3 mult;
    mult.x = x / a;
    mult.y = y / a;
    mult.z = z / a;
    return mult;
    
};


/* Component-wise ratio of two vectors */
CVector3 CVector3::operator / (CVector3 v1){
    
    CVector3 ratio;
    ratio.x = x / v1.x;
    ratio.y = y / v1.y;
    ratio.z = z / v1.z;
    return ratio;
    
};

/* Sum of the components of a vector */
double CVector3::sum(){
    
    double sum = 0.0;
    sum += x;
    sum += y;
    sum += z;
    return sum;
    
};

/* Set a vector equal to another one */
void CVector3::operator = (CVector3 v1) {

    x = v1.x;
    y = v1.y;
    z = v1.z;

};
    

/* Set all components equal to a scalar d1 */
void CVector3::operator = (double d1){
    
    x = d1;
    y = d1;
    z = d1;
    return;
    
};


/* Squared modulus of a vector */
double CVector3::mod2(){
    
    double mod2;
    mod2 = x*x + y*y + z*z;
    return mod2;

};

/* Modulus of a vector */
double CVector3::mod(){
    
    return std::sqrt(mod2());
    
};

/* Return the angle  with vector vec2  of a vector */
double CVector3::angle( CVector3 v2 ) {

    //take the dot_product and divide by modules, than invert with 
    //acos.
    double angle = 0.0;
    double dot = 0.0;
    double mod1 = std::sqrt( x*x + y*y +z*z );
    double mod2 = v2.mod(); 

    dot = ( x*v2.x + y*v2.y + z*v2.z ) / mod1 / mod2; 
    dot = std::acos( dot );
    
};



