#ifndef ASSIGNMENT03_INTERPOLATION_H
#define ASSIGNMENT03_INTERPOLATION_H

#include "intermediate_grid.h"

// function to find the barycentric coordinates of a point in output grid wrt. a triangle in the input grid
std::array<double, 3> Get_barycentric(point2D const& vertex1, point2D const& vertex2, point2D const& vertex3,
                                      point2D const& outGridPoint);

// function for interpolating between unstructured grids by using an intermediate grid
void Interpolate(StructuredGrid& intermediateGrid);

#endif //ASSIGNMENT03_INTERPOLATION_H
