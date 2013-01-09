//
//  Global_variables.h
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 05/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "3D_Vectors.h"
#ifndef SIMU_VARIABLES_H
#define SIMU_VARIABLES_H

class CSimu_variables {

    public:
    // Pbc in x-y-z directions
    bool pbc[3];
    // Vectors defining the simulation box
    CVector3 box;

    CSimu_variables();
    CSimu_variables(bool *pbc, CVector3 box );
    CSimu_variables(CVector3 box );

};

#endif
