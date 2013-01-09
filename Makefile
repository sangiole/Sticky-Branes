rm *.o *.x
g++ -c 3D_Vectors.cpp 
g++ -c MTrand.cpp 
g++ -c Simu_variables.cpp 
g++ -c Utils_distances.cpp 
g++ -c Bead.cpp 
g++ -c Main.cpp

echo "DONE COMPILING"
g++ -o "deformable.x" Main.o 3D_Vectors.o MTrand.o Utils_distances.o Simu_variables.o Bead.o
rm *.o
