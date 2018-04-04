#pragma once

#include "TrMapData.hpp"

class TrMap;

// map
// is this too much memory? make sure to check
class TrWindMap : public TrMapData<Vec3<double> > {
 public:
  TrWindMap(int rows, int cols) : TrMapData(rows, cols) {}

  void update(TrMap* map);
};
