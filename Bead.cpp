//
//  CBead.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 04/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "headers/Bead.h"

/* General constructor for this class */
CBead::CBead (){}

/* A more specific constructor for the class*/
CBead::CBead (CVector3 v1, bool activity){ 
    
    pos = new CVector3;
    pos_now = new CVector3;
    pos_new = new CVector3;
    pos->x = v1.x;
    pos->y = v1.y;
    pos->z = v1.z;
    pos_now->x = v1.x;
    pos_now->y = v1.y;
    pos_now->z = v1.z;
    pos_new = 0; 

    active = activity;
    
}

void CBead:: move_bead( CVector3 dr ){
    pos_new->x = pos->x + dr.x;
    pos_new->y = pos->y + dr.y;
    pos_new->z = pos->z + dr.z;
    pos_now = pos_new;
}
    
void CBead::update_bead_pos() {
        //Only do it if effectively the new position exist, otherwise return an error and exit

        if ( pos_new ) {
            pos = pos_new;
            pos_now = pos;
            pos_new = 0;
            return;
        }
        else {
            std::cout<< "You are trying to copy a non-existent position, program will stop \n";
            exit(1);
        }
}
