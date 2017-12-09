#ifndef DATASET_HH
#define DATASET_HH

#include "param.hh"

#include "CROOTData.hh"

namespace Phylloxera
{
class Dataset
{

public:
  Dataset(){};

protected:
  scarab::param_node fDatasetConfig;
  Katydid::TMultiTrackEventData fMultiTrackEventData;

  // ClassDef(Dataset, 1)
};
}

#endif