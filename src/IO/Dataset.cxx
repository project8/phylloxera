#include "Dataset.hh"

namespace Phylloxera
{
Dataset::Dataset(std::string name) : fDatasetConfig(),
                                     fMultiTrackEventDataTree(),
                                     fName(name)
{
    LPROG(dataset, "Creating dataset " << fName);
}

bool Dataset::AppendData(Katydid::TMultiTrackEventData data)
{
    // fMultiTrackEventData.push_back(data);

    return true;
}
}