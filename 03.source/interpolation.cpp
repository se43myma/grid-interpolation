#include "../02.include/interpolation.h"

std::array<double, 3> Get_barycentric(point2D const& vertex1, point2D const& vertex2, point2D const& vertex3,
                                       point2D const& outGridPoint){

    // find the coordinates of the vertices of the triangle
    double x1, x2, x3, y1, y2, y3;
    x1 = vertex1.at(0);
    x2 = vertex2.at(0);
    x3 = vertex3.at(0);
    y1 = vertex1.at(1);
    y2 = vertex2.at(1);
    y3 = vertex3.at(1);
    double x = outGridPoint.at(0);
    double y = outGridPoint.at(1);

    // computing barycentric coordinates
    double alpha = (-(x-x2)*(y3-y2) + (y-y2)*(x3-x2))/(-(x1-x2)*(y3-y2) + (y1-y2)*(x3-x2));
    double beta = (-(x-x3)*(y1-y3) + (y-y3)*(x1-x3))/(-(x2-x3)*(y1-y3) + (y2-y3)*(x1-x3));
    double gamma = 1 - alpha - beta;

    return {alpha, beta, gamma};
}


void Interpolate(StructuredGrid& intermediateGrid){

    double originX = intermediateGrid.origin.at(0);
    double originY = intermediateGrid.origin.at(1);
    double meshSize = intermediateGrid.meshSize;
    size_t numRows = intermediateGrid.numRows;
    size_t numCols = intermediateGrid.numCols;

    // for each point in the output grid, find the data value by interpolation from input grid
    for(size_t pointCtr=0; pointCtr<intermediateGrid.outputGrid.Get_numGridPoints(); ++pointCtr){

        // find the cell of intermediate grid to which the point belongs to
        point2D outGridPoint = intermediateGrid.outputGrid.gridPoints.at(pointCtr);
        double x = outGridPoint.at(0);
        double y = outGridPoint.at(1);
        size_t cellIndex1 = 0;
        size_t cellIndex2 = 0;
        // find the row in which the point is present
        for(size_t row=0; row<numRows; ++row){
            if((originX + row*meshSize <= x) && (originX + row*meshSize + meshSize >= x)){
                cellIndex1 = row;
                break;
            }
        }
        // find the column in which the point is present
        for(size_t col=0; col<numCols; ++col){
            if((originY + col*meshSize <= y) && (originY + col*meshSize + meshSize >= y)){
                cellIndex2 = col;
                break;
            }
        }

        // get the intersecting triangles for the corresponding cell
        auto intersectingTriangles = intermediateGrid.intersectingCells.at(cellIndex1).at(cellIndex2);

        // find the triangle in which the point is present
        std::array<double, 3> barycentric;
        for(size_t triangleID : intersectingTriangles){
            cell triangle = intermediateGrid.inputGrid.gridCells.at(triangleID);
            point2D vertex1 = intermediateGrid.inputGrid.gridPoints.at(triangle.at(0));
            point2D vertex2 = intermediateGrid.inputGrid.gridPoints.at(triangle.at(1));
            point2D vertex3 = intermediateGrid.inputGrid.gridPoints.at(triangle.at(2));
            barycentric = Get_barycentric(vertex1, vertex2, vertex3, outGridPoint);

            // if all barycentric coordinates >= 0, the point belongs to the triangle
            if(barycentric.at(0)>=0 && barycentric.at(1)>=0 && barycentric.at(2)>=0){
                //interpolate
                double value1 = intermediateGrid.inputGrid.gridPointData.at(triangle.at(0));
                double value2 = intermediateGrid.inputGrid.gridPointData.at(triangle.at(1));
                double value3 = intermediateGrid.inputGrid.gridPointData.at(triangle.at(2));
                intermediateGrid.outputGrid.gridPointData[pointCtr] =
                        barycentric.at(0)*value1 + barycentric.at(1)*value2 + barycentric.at(2)*value3;
                break;
            }
        }
    }

}