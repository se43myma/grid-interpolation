#include "cmath"
#include "chrono"
#include "iostream"
#include "string"

#include "../02.include/unstructured_grid.h"
#include "../02.include/intermediate_grid.h"
#include "../02.include/interpolation.h"

int main(int argc, char *argv[]) {

    // read command line inputs
    std::string const inputGridPath = argv[1];
    std::string const outputGridPath = argv[2];

    // load the input and output grids
    UnstructuredGrid inGrid(inputGridPath);
    UnstructuredGrid outGrid(outputGridPath);

    for(int i=0; i<=9; ++i){
        auto begin = std::chrono::high_resolution_clock::now(); // timer start

        // construct the intermediate structured grid
        StructuredGrid intermediateGrid(inGrid, outGrid);

        // Change the mesh size
        intermediateGrid.meshSize = std::pow(0.5,i);
        std::cout << "Step size: " << intermediateGrid.meshSize << "\n";

        // Find intersecting triangles for the cells
        intermediateGrid.Find_intersectingTriangles();

        // carry out the interpolation from the INGRID to the OUTGRID using the intermediate grid
        Interpolate(intermediateGrid);

        auto end = std::chrono::high_resolution_clock::now(); // timer stop
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        std::cout<<"Time taken interpolate : "<<elapsed.count() * 1e-9<<"s\n";
    }

    // write the VTK file for output grid
    outGrid.Write_VTK();

    return 0;
}
