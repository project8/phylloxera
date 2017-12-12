#ifndef DATASET_HH
#define DATASET_HH

#include <iostream>
#include "TTree.h"

#include "param.hh"
#include "logger.hh"

#include "CROOTData.hh"

LOGGER(dataset, "Phylloxera::Dataset");

namespace Phylloxera
{
class Dataset
{

public:
  Dataset(std::string);

  bool AppendData(Katydid::TMultiTrackEventData);

protected:
  std::string fName;
  scarab::param_node fDatasetConfig;
  TTree *fMultiTrackEventDataTree;

  // ClassDef(Dataset, 1)
};
}

#endif