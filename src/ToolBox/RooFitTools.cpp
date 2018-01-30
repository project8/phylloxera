#include "RooDataSet.h"

// namespace Phylloxera
// {

inline std::vector<double> getDataFromDataset(RooDataSet *data, const char *name)
// Extract the values of a dataset into a vector
{
    std::vector<double> vectorData;
    for (int i = 0; i < data->numEntries(); i++)
    {
        vectorData.push_back(data->get(i)->getRealValue(name));
    }
    return vectorData;
}
// }
