#ifndef ASSIGNMENT03_UNSTRUCTURED_GRID_H
#define ASSIGNMENT03_UNSTRUCTURED_GRID_H

#include "array"
#include "string"
#include "vector"

typedef std::array<double, 2> point2D;
typedef std::array<size_t, 3> cell;

// A struct for unstructured grid
struct UnstructuredGrid {
    // data members
    std::string const gridFilePath;
    std::vector<point2D> gridPoints;
    std::vector<double> gridPointData;
    std::vector<cell> gridCells;

    // constructor
    explicit UnstructuredGrid(std::string pathToVTK);
    ~UnstructuredGrid();

    // methods
    size_t Get_numGridPoints() const;
    size_t Get_numGridCells() const;
    void Write_VTK() const;
};

#endif //ASSIGNMENT03_UNSTRUCTURED_GRID_H
