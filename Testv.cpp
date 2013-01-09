#include <iostream>
#include <vector>
#include <cmath>
#include "headers/3D_Vectors.h"

#define endl "\n"

using namespace std;

int main() {

    CVector3 v1( 2.0, 0.0, 0.0 );
    CVector3 v2( 0.0, 0.0, 2.0 );
    CVector3 v3;
    v3 = 0.0;
    v3 = v1.vec_prod( v2 );

    cout << v3.x << v3.y << v3.z << "Expected  all equal" << endl;
    cout << v1.vec_prod( v2 ).mod() << "Expected 4"  << endl;

}
