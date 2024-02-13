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
    auto begin = std::chrono::high_resolution_clock::now(); // timer start (loading inputs)
    UnstructuredGrid inGrid(inputGridPath);
    UnstructuredGrid outGrid(outputGridPath);
    auto end = std::chrono::high_resolution_clock::now(); // timer stop (loading inputs)
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout<<"\nTime taken to load INGRID and OUTGRID : "<<elapsed.count() * 1e-9<<"s\n";

    // construct the intermediate structured grid
    begin = std::chrono::high_resolution_clock::now(); // timer start (interpolation)
    StructuredGrid intermediateGrid(inGrid, outGrid);
    intermediateGrid.Find_intersectingTriangles();

    // carry out the interpolation from the INGRID to the OUTGRID using the intermediate grid
    Interpolate(intermediateGrid);
    end = std::chrono::high_resolution_clock::now(); // timer stop (interpolation)
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout<<"Time taken interpolate : "<<elapsed.count() * 1e-9<<"s\n";

    // write the VTK file for output grid
    begin = std::chrono::high_resolution_clock::now(); // timer start (writing output)
    outGrid.Write_VTK();
    end = std::chrono::high_resolution_clock::now(); // timer stop (writing output)
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout<<"Time taken write output : "<<elapsed.count() * 1e-9<<"s\n";

    return 0;
}
