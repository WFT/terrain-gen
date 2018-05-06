#pragma once

#include "TrMapData.hpp"

class TrMap;

// map
// is this too much memory? make sure to check
class TrMoistureMap : public TrMapData<double> {
 public:
  TrMoistureMap(int rows, int cols) : TrMapData<double>(rows, cols) {}

  void update(TrMap* map) override;
};
