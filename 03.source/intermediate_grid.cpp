#include "../02.include/intermediate_grid.h"

#include "algorithm"
#include "cmath"

StructuredGrid::StructuredGrid(const UnstructuredGrid &inpGrid, UnstructuredGrid &outGrid) :
inputGrid(inpGrid), outputGrid(outGrid){

    // find the x-coordinate and y-coordinate limits of the input grid
    double xMin, yMin, xMax, yMax;
    xMin = xMax = inpGrid.gridPoints.at(0).at(0); // x coordinate of first point
    yMin = yMax = inpGrid.gridPoints.at(0).at(1); // y coordinate of first point
    for(const auto& gridPoint : inpGrid.gridPoints){
        double x = gridPoint.at(0);
        double y = gridPoint.at(1);
        if(x>xMax){xMax=x;}
        if(y>yMax){yMax=y;}
        if(x<xMin){xMin=x;}
        if(y<yMin){yMin=y;}
    }

    // assign mesh size
    meshSize = 1/std::sqrt(inputGrid.Get_numGridPoints());

    // assign origin
    origin = {xMin, yMin};

    // find number of rows and cols in the mesh
    numRows = int((xMax - xMin)/meshSize) + 1;
    numCols = int((yMax - yMin)/meshSize) + 1;

    // resize the member intersectingCells
    intersectingCells.resize(numRows, std::vector<std::vector<size_t>>(numCols));

}

void StructuredGrid::Find_intersectingTriangles() {

    // for each cell in the structured grid, find intersecting triangles in the input mesh
    for (size_t row = 0; row < numRows; ++row) {
        for (size_t col = 0; col < numRows; ++col) {

            // get the bottom left corner of cell
            double x = origin.at(0) + row * meshSize;
            double y = origin.at(1) + col * meshSize;

            // find the intersecting triangles
            for (size_t triangleCtr = 0; triangleCtr < inputGrid.Get_numGridCells(); ++triangleCtr) {
                cell gridTriangle = inputGrid.gridCells.at(triangleCtr);
                point2D vertex1 = inputGrid.gridPoints.at(gridTriangle.at(0));
                point2D vertex2 = inputGrid.gridPoints.at(gridTriangle.at(1));
                point2D vertex3 = inputGrid.gridPoints.at(gridTriangle.at(2));

                // get the bounding box for the triangle
                double xMin, xMax, yMin, yMax;
                xMin = std::min({vertex1.at(0), vertex2.at(0), vertex3.at(0)});
                xMax = std::max({vertex1.at(0), vertex2.at(0), vertex3.at(0)});
                yMin = std::min({vertex1.at(1), vertex2.at(1), vertex3.at(1)});
                yMax = std::max({vertex1.at(1), vertex2.at(1), vertex3.at(1)});

                // check for intersection
                if (std::max(x, xMin) < std::min(x + meshSize, xMax) &&
                    std::max(y, yMin) < std::min(y + meshSize, yMax)) {
                    intersectingCells[row][col].push_back(triangleCtr);
                }
            }
        }
    }

}
