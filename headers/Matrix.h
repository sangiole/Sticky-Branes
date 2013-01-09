#ifndef MATRIX_H
#define MATRIX_H

Class C2DMatrix{

    public:
        int nrows;
        int ncols;
        int *pmatrix;
        char type;
        C2DMatrix();
        C2DMatrix(int rows, int cols);
        void clear();

}

#endif
