
#pragma once

#include "../../include/fft/fft.h"
#include "../Perlin.hpp"
#include "../TrUtils/TrMath.hpp"
#include "../TrUtils/TrSimulation.hpp"
#include "TrMapData.hpp"

class TrMap;

// map
// is this too much memory? make sure to check
class TrColorMap : public TrMapData<uint32_t> {
 public:
  int m_renderState;
  dvec3 m_light;
  dvec3 m_moonlight;
  double m_hour;
  int m_day;
  int m_month;
  double m_elevation;

  bool m_raytrace = false;

  cOcean* ocean;

  const dvec3 m_shallowWater = dvec3(0x3A, 0x5B, 0xAA);
  const dvec3 m_mediumWater = dvec3(0x5A, 0x8B, 0xCA);
  const dvec3 m_deepWater = dvec3(0x1A, 0x2B, 0x56);

  TrColorMap(int rows, int cols);

  ~TrColorMap() { delete ocean; }

  void update(TrMap* map);

  void updateLightAngle();

  void updateGrayscale(TrMap* map);
  void updateHistogram(TrMap* map);
  void updateDisplay(TrMap* map);
  void updateMoistureDemo(TrMap* map);
};
