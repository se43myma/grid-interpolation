#include "../02.include/unstructured_grid.h"

#include "fstream"
#include "string"

UnstructuredGrid::UnstructuredGrid(std::string pathToVTK) : gridFilePath(pathToVTK){

    std::ifstream gridFile (pathToVTK);
    std::string throwAwayString;
    size_t numGridPoints, numGridCells;

    // ignore header section
    for(int i=0; i<5; ++i){
        gridFile.ignore(500, '\n');
    }

    // read the point details
    gridFile>>throwAwayString;
    gridFile>>numGridPoints;
    gridFile.ignore(500, '\n');
    gridPoints.resize(numGridPoints);
    for(size_t pointCtr = 0; pointCtr < numGridPoints; ++pointCtr){
        double x, y;
        gridFile >> x >> y >> throwAwayString;
        gridPoints[pointCtr] = {x, y};
    }

    // read the cell details
    gridFile.ignore(500, '\n');
    gridFile>>throwAwayString;
    gridFile>>numGridCells;
    gridFile.ignore(500, '\n');
    gridCells.resize(numGridCells);
    for(size_t cellCtr = 0; cellCtr < numGridCells; ++cellCtr){
        size_t id1, id2, id3;
        gridFile >> throwAwayString >> id1 >> id2 >> id3;
        gridCells[cellCtr] = {id1, id2, id3};
    }

    // ignore cell types section and point data section details
    for(size_t i=0; i< Get_numGridCells() + 7; ++i) {
        gridFile.ignore(500, '\n');
    }

    // read the point data
    gridPointData.resize(numGridPoints);
    for (size_t pointCtr = 0; pointCtr < numGridPoints; ++pointCtr) {
        double pointData;
        gridFile >> pointData;
        gridPointData[pointCtr] = pointData;
    }

    gridFile.close();
}

UnstructuredGrid::~UnstructuredGrid() {}

size_t UnstructuredGrid::Get_numGridPoints() const {
    return gridPoints.size();
}

size_t UnstructuredGrid::Get_numGridCells() const {
    return gridCells.size();
}

void UnstructuredGrid::Write_VTK() const {

    std::ofstream outputFile("../05.outputs/OUTGRID_interpolated.vtk");
    std::ifstream gridFile(gridFilePath);
    std::string line;

    // copy contents up to the point data section
    for(size_t i=0; i<(14 + Get_numGridPoints() + 2*Get_numGridCells()); ++i){
        std::getline(gridFile,line);
        outputFile << line << "\n";
    }

    // write point data from the member gridPointData to file
    for(size_t pointCtr=0; pointCtr<Get_numGridPoints(); ++pointCtr){
        outputFile << gridPointData[pointCtr] << "\n";
    }

    outputFile.close();
}