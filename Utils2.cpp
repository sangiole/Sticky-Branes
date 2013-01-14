//Trying to branch...
//  Utils2.cpp
//  Deformable colloids
//
//  Created by Stefano Angioletti-Uberti on 05/11/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <CPlaquette.cpp>

int unshared( Plaquette p1,p2 ){
    
    int i,j,at,at2;
    bool found;
    
    for (i=0,i<3,i++){
        
        at1 = p1.bead_id[i];
        
        for (j=0,j<3,j++){
            
            at2 = p2.bead_id[j];
            if (at1==at2) {
                found = true;   
                break;
            }

            
        }
            
        if (!found) return at1;
    }
    
    cout << "A problem occured, these plaquettes are not neighbours!";
    exit(1);
}
