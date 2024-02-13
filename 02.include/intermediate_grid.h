#ifndef ASSIGNMENT03_INTERMEDIATE_GRID_H
#define ASSIGNMENT03_INTERMEDIATE_GRID_H

#include "unstructured_grid.h"
#include "array"
#include "vector"

// A struct for intermediate structured grid
struct StructuredGrid{
    // data members
    UnstructuredGrid const& inputGrid;
    UnstructuredGrid& outputGrid;
    point2D origin;
    double meshSize;
    size_t numRows;
    size_t numCols;
    // container for the IDs of triangles in inputGrid that intersect the corresponding cells of the intermediate grid.
    // 2D vector, each element is again a vector of type size_t.
    // Outer dimension : row of the cell, Inner dimension : column of the cell
    std::vector<std::vector<std::vector<size_t>>> intersectingCells;

    // constructor
    StructuredGrid(UnstructuredGrid const& inpGrid, UnstructuredGrid& outGrid);

    // members
    // uses bounding boxes to find intersecting triangles for each cell in the grid
    void Find_intersectingTriangles();
};

#endif //ASSIGNMENT03_INTERMEDIATE_GRID_H
