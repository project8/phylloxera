#include <string>
#include <sstream>
#include <iostream>
#include <vector>

// namespace Phylloxera
// {

inline double getMinFromVector(std::vector<double> vectX)
// Extract the min value of a vector
{
    size_t iMin = 0;
    for (size_t i = 1; i < vectX.size(); ++i)
    {
        if (vectX[iMin] > vectX[i])
            iMin = i;
    }
    return vectX[iMin];
}

inline double getMaxFromVector(std::vector<double> vectX)
// Extract the max value of a vector
{
    size_t iMax = 0;
    for (size_t i = 1; i < vectX.size(); ++i)
    {
        if (vectX[iMax] < vectX[i])
            iMax = i;
    }
    return vectX[iMax];
}
// }