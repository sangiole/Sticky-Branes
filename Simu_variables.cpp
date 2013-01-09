////
//  Global_variables.h
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 05/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "headers/Simu_variables.h"

CSimu_variables::CSimu_variables(){
    
    // Pbc in x-y-z directions
    pbc[0] = false;
    pbc[1] = false;
    pbc[2] = false;

    // Size of the box in the x-y-z direction
    box.x = 10.0e10; 
    box.y = 10.0e10;
    box.z = 10.0e10;
    
}

CSimu_variables::CSimu_variables (bool * ppbc, CVector3 fbox ) {
    
    // Pbc in x-y-z directions
    pbc[0] = *(ppbc);
    pbc[1] = *(ppbc+1);
    pbc[2] = *(ppbc+2);

    // Size of the box in the x-y-z direction
    box.x = fbox.x; 
    box.y = fbox.y;
    box.z = fbox.z;
    
}
