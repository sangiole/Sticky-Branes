#include "headers/C2DMatrix.h"

C2DMatrix::C2DMatrix(){};

C2DMatrix::C2DMatrix( int rows, int cols ){

    nrows = rows;
    ncols = cols;
    pmatrix = new int[ nrows * ncols ];

}

int C2DMatrix::operator()( int row, int col ){

    int value;
    value = *( pmatrix +  row*nrows + col*ncols );
    return value;

}

