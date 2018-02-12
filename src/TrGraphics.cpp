/**
 * TrGraphics
 *
 * Victor Jiao
 *
 * a test file for testing driving.
 */

#include "TrGraphics.hpp"


void TrMap::updateColors() {
  if (0) {
    for (int i = 0; i < m_rows; i++) {
      for (int j = 0; j < m_cols; j++) {
        // render land
        m_color->set(i,j,multiplyColor(0xFFFFFFFF, m_height->at(i,j), m_height->at(i,j), m_height->at(i,j)));
         
      }
    }
    return;
  }

  if (0) {
    // buffer counts in the top row, set to 0 later.
    
    for (int j = 0; j < m_cols; j++) {
      m_color->set(0,j, 0);
    }

    for (int i = 1; i < m_rows; i++) {
      for (int j = 0; j < m_cols; j++) {
        int col = m_cols - m_height->at(i,j) * m_cols;

        m_color->at(i,j) = 0;
        m_color->at(0,col)++;
      }
    }

    double cur_col = 0.0;
    for (int j = 0; j < m_cols; j++) {
      double amt = (double) m_color->at(0,j) / (double) m_cols;
      if (floor(cur_col + amt) > floor(cur_col)) {
        if (cur_col < m_cols) {
          for (int r = j; r < m_rows; r++) {
            m_color->set(r,(int)floor(cur_col), 0xFFFFFFFF);
          }
        }
      } 

      cur_col += amt ;
    }


    for (int j = 0; j < m_cols; j++) {
      m_color->set(0,j, 0xFF000000);
    }
    return;
  }

  if (!m_useMoisture) {


    int threshold[9];
    // -: deep 
    threshold[0] = 0.20 * 256; 
    threshold[1] = 0.40 * 256; 
    threshold[2] = 0.45 * 256; // sand
    threshold[3] = 0.49 * 256; // grass
    threshold[4] = 0.55 * 256; 
    threshold[5] = 0.60 * 256; 
    threshold[6] = 0.68 * 256; // dark mountain level
    threshold[7] = 0.70 * 256;
    threshold[8] = 0.80 * 256;
    // 1: snow


    uint32_t colors[9] = {
      0xFF1A2B56,
      0xFF253C78,
      0xFF3A5BAA,
      0xFFEEDDBB,
      0xFF77BC49,
      0xFF58A327,
      0xFF28771F,
      0xFF210E04,
      0xFF5B3F31};

    Vec3 light(0.4, 0.2, 0.8);
    light.normalize();

    for (int i = 0; i < m_rows; i++) {
      for (int j = 0; j < m_cols; j++) {
        // render land
        
        for (int c = 0; c < 9; c++) {
          if (m_height->get(i,j) * 255 < threshold[c]) {
            m_color->set(i,j,colors[c]);
            break;
          }

          if (m_height->get(i,j) * 255 >= threshold[8]) {
            m_color->set(i,j,0xFFFFFFFF);
            break;
          }
        }

        // moisture lerping
        if (m_height->at(i,j)  * 255 > threshold[2] && m_moisture->at(i,j) < 0.1) {
          m_color->at(i,j) = lerpColor(
                      lerpColor(0xFFEEDDBB, 0xFF5B3F31, (m_height->at(i,j) - 0.458) * 0.8), 
                           m_color->at(i,j), 0.2 + 0.8 * m_moisture->at(i,j) * 10.0);
        }


        // render water
        if (m_water->at(i,j) > 0.001 && m_height->at(i,j)  * 255 > threshold[2]) {
          float height = m_water->at(i,j) + m_height->at(i,j);
          m_color->at(i,j) = 0xFF305090;

          int rip = floor(height * 160.0) - 64;
          m_color->at(i,j) = shiftColor(m_color->at(i,j), rip, rip, rip); 
        } else {
          float wat = 0.6 * light.dot(m_normal->at(i,j));

          if (m_height->at(i,j) * 255  < threshold[2]) {
            wat = 0.6;
          }

          m_color->at(i,j) = multiplyColor(m_color->at(i,j), wat + 0.4, wat + 0.4, wat + 0.4);
        }


      }
    }
  } else {

    // no initial water colors,just land.
    uint32_t c_wetdirt = 0xFF664433;
    uint32_t c_drydirt = 0xFFBB8866;
    // uint32_t c_sand = 0xFFEEDDBB;
    uint32_t c_grass = 0xFF67AC40;
    uint32_t c_forest = 0xFF58A327;
    uint32_t c_rainforest = 0xFF28771F;
    uint32_t c_rock = 0xFFAB9F91;

    Vec3 light(0.4, 0.2, 0.8);
    light.normalize();

    for (int i = 0; i < m_rows; i++) {
      for (int j = 0; j < m_cols; j++) {
        // errr how do I do this....

        if (m_height->at(i,j) > 0.7) {
          m_color->at(i,j) = c_rock;
        } else {
          if (m_moisture->at(i,j) > 0.05) {
            m_color->at(i,j) = lerpColor(c_drydirt, c_wetdirt, 0.4 + m_moisture->at(i,j) * 0.6);
          } else {
            m_color->at(i,j) = c_drydirt;
          }

          if (m_vegetation->at(i,j) > 0.2 && m_moisture->at(i,j) > 0.3) {
            m_color->at(i,j) = c_grass;
          }

          if (m_vegetation->at(i,j) > 0.65 && m_moisture->at(i,j) > 0.4) {
            m_color->at(i,j) = c_forest;
          }

          if (m_vegetation->at(i,j) > 0.8 && m_moisture->at(i,j) > 0.8) {
            m_color->at(i,j) = c_rainforest;
          }
        }

        // render water
        if (m_water->at(i,j) > 0.001) {
          float height = m_water->at(i,j) + m_height->at(i,j);
          m_color->at(i,j) = 0xFF305090;

          int rip = floor(height * 128.0) - 32;
          m_color->at(i,j) = shiftColor(m_color->at(i,j), rip, rip, rip); 
        } else {
          float wat = 0.6 * light.dot(m_normal->at(i,j));
          m_color->at(i,j) = multiplyColor(m_color->at(i,j), wat + 0.4, wat + 0.4, wat + 0.4);
        }
      }
    }
  }
}

void TrMap::updateWind() {
  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_cols; j++) {
      m_wind->at(i,j) = Vec3::project(m_normal->at(i,j), Vec3(1.0,0.0,0.0));
      m_wind->at(i,j).normalize();
    }
  }
}

void TrMap::updateMoisture() {

  // for (int j = 0; j < m_cols; j++) {
  //   for (int i = 0; i < m_rows; i++) {
  //     if (m_water->at(i,j) + m_height->at(i,j) < 0.458) {
  //       m_water->at(i,j) = 0.458 - m_height->at(i,j);
  //     }
  //   }
  // }


  // // Good Moisture Carried by Wind
  // // m_moisture->set(0.0);

  // for (int j = 0; j < m_cols; j++) {
  //   for (int i = 0; i < m_rows; i++) {
  //     m_moisture->at(i,j) *= 0.9; // random drying bullshit
  //     m_moisture->at(i,j) += m_water->at(i,j) * 3.0; // random water humidifying bullshit

  //     if (m_moisture->at(i,j) < 0) m_moisture->at(i,j) = 0;
  //     if (m_moisture->at(i,j) > 1.0) m_moisture->at(i,j) = 1.0;
  //   }
  // }


  // for (int j = 0; j < m_cols; j++) {
  //   for (int i = 0; i < m_rows; i++) {
  //     // propogate moisture forwards based on current WATER and MOISTURE
  //     m_moisture->at(i  ,j+1) += (m_moisture->at(i,j)*0.5) * (m_wind->at(i,j).x + m_wind->at(i,j).z * 0.25 + abs(m_wind->at(i,j).z) * 0.05) * 0.98;
  //     if (m_wind->at(i,j).y > 0.0) {
  //       m_moisture->at(i+1,j+1) += (m_moisture->at(i,j)*0.5) * m_wind->at(i,j).y * 0.98;
  //     } else {
  //       m_moisture->at(i-1,j+1) -= (m_moisture->at(i,j)*0.5) * m_wind->at(i,j).y * 0.98;
  //     }
  //     m_moisture->at(i,j) *= 0.5;

  //   }
  // }

  // m_moisture->boxBlur();
  // m_moisture->boxBlur();
  // m_moisture->boxBlur();
  // m_moisture->boxBlur();
  // m_moisture->boxBlur();


  // for (int i = 0; i < m_rows; i++) {
  //   for (int j = 0; j < m_cols; j++) {
  //     if (m_moisture->at(i,j) > 0.1) {
  //       m_vegetation->at(i,j) += 0.01;
  //     } else {
  //       m_vegetation->at(i,j) -= 0.01;
  //     }
  //   }
  // }






  // // Moisture: carried by WIND...
  // for (int i = 0; i < m_rows; i++) {
  //     for (int j = 0; j < m_cols; j++) {
  //         // if there is water
  //         if (m_water->at(i,j) > 0.002) {
  //             // increase moisture from previous tile
  //             // wait, which is the previous tile???
  //             m_moisture->at(i,j) = 1.0;
  //         } else {
  //             m_moisture->at(i,j) = m_moisture->at(i,j) * 0.35;
  //         }

  //         if (m_moisture->at(i,j) > 0.1 && m_moisture->at(i,j) < 0.9) {
  //             m_vegetation->at(i,j) += 0.01;
  //         } else {
  //             m_vegetation->at(i,j) -= 0.01;
  //         }

  //         if (m_moisture->at(i,j) < 0.0) m_moisture->at(i,j) = 0;
  //         if (m_moisture->at(i,j) > 1.0) m_moisture->at(i,j) = 1.0;
  //     }
  // }

  // for (int i = 0; i < m_rows; i++) {
  //     for (int j = 0; j < m_cols; j++) {
  //         m_moisture->at(i  ,j+1) += m_moisture->at(i,j) * 0.60 * m_wind->at(i,j).y;
  //         if (m_wind->at(i,j).x > 0.0) {
  //             m_moisture->at(i+1,j+1) += m_moisture->at(i,j) * 0.60 * m_wind->at(i,j).x;
  //         } else {
  //             m_moisture->at(i-1,j+1) -= m_moisture->at(i,j) * 0.60 * m_wind->at(i,j).x;
  //         }

  //         if (m_moisture->at(i,j) < 0) {
  //             m_moisture->at(i,j) = 0;
  //             printf("%f\n", m_wind->at(i,j).x);
  //         }
  //     }
  // }

  // m_moisture->boxBlur();


  // Regular moisture
  // okay set moisture to 1 if there is some water
  for (int i = 0; i < m_rows; i++) {
      for (int j = 0; j < m_cols; j++) {
          if (m_water->at(i,j) > 0.01) {
              m_moisture->at(i,j) = 1.0;
          } else {
              m_moisture->at(i,j) = m_moisture->at(i,j) * 0.50 +
                                    m_water->at(i,j) * 50.0;
          }

          if (m_moisture->at(i,j) > 0.1 && m_moisture->at(i,j) < 0.5) {
              m_vegetation->at(i,j) += 0.01;
          } else {
              m_vegetation->at(i,j) -= 0.01;
          }
      }
  }

  for (int i = 0; i < m_rows; i++) {
      for (int j = 0; j < m_cols; j++) {


          m_moisture->at(i,j+1) += m_moisture->at(i,j) * 0.25;
          m_moisture->at(i+1,j+1) += m_moisture->at(i,j) * 0.125;
          m_moisture->at(i-1,j+1) += m_moisture->at(i,j) * 0.125;
      }
  }

  m_moisture->boxBlur();
}

void TrMap::updateWater(bool erosion) {
  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_cols; j++) {
      double m = m_height->get(i,j) +
             m_water->get(i,j);
      int mi = i;
      int mj = j;
      double mh = m;

      // straight
      if (m_height->get(i+1,j) + m_water->get(i+1,j) < mh) {
        mi = i+1; mj = j;
        mh = m_height->get(i+1,j) + m_water->get(i+1,j); }

      if (m_height->get(i-1,j) + m_water->get(i-1,j) < mh) {
        mi = i-1; mj = j;
        mh = m_height->get(i-1,j) + m_water->get(i-1,j); }

      if (m_height->get(i,j+1) + m_water->get(i,j+1) < mh) {
        mi = i; mj = j+1;
        mh = m_height->get(i,j+1) + m_water->get(i,j+1); }

      if (m_height->get(i,j-1) + m_water->get(i,j-1) < mh) {
        mi = i; mj = j-1;
        mh = m_height->get(i,j-1) + m_water->get(i,j-1); }

      // diagonal
      if (m - (m_height->get(i+1,j+1) + m_water->get(i+1,j+1)) > (m - mh) * 1.4142) {
        mi = i+1; mj = j+1;
        mh = m_height->get(i+1,j+1) + m_water->get(i+1,j+1); }

      if (m - (m_height->get(i-1,j-1) + m_water->get(i-1,j-1)) > (m - mh) * 1.4142) {
        mi = i-1; mj = j-1;
        mh = m_height->get(i-1,j-1) + m_water->get(i-1,j-1); }

      if (m - (m_height->get(i+1,j-1) + m_water->get(i+1,j-1)) > (m - mh) * 1.4142) {
        mi = i+1; mj = j-1;
        mh = m_height->get(i+1,j-1) + m_water->get(i+1,j-1); }

      if (m - (m_height->get(i-1,j+1) + m_water->get(i-1,j+1)) > (m - mh) * 1.4142) {
        mi = i-1; mj = j+1;
        mh = m_height->get(i-1,j+1) + m_water->get(i-1,j+1); }

      if (mh < m - 0.0001) {
        double diff = m-mh;
        diff *= 0.5;

        // prevents water from cutting too deep
        diff *= 1.0 - m_water->get(i,j);
        if (diff > m_water->get(i,j)) {
          diff = m_water->get(i,j);
        }

        m_water_temp->at(mi,mj) += diff;
        m_water_temp->at(i,j) -= diff;
      }
    }
  }
  // wait or shud we blur the moisture map?

  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_cols; j++) {

      if (erosion) {
        double change = m_water_temp->at(i,j);
        if (change > 0.0) {
          // adding land
          // TODO: WHAT DO I DO WITH THIS
          change = change * 0.5;
        }
        // printf("%f\n", change);
        // TODO: also look at water differene
        if (m_water->at(i,j) > 0.001) {
          // printf("%4f\n", 0.1 / m_water->at(i,j));
          change *= abs(change * 0.1 / m_water->at(i,j));
        } else {
          change *= abs(change * 40.0);

        }

        m_height->at(i  ,j  ) += change /  8.0f;
        m_height->at(i+1,j+1) += change / 22.63f;
        m_height->at(i+1,j  ) += change / 16.0f;
        m_height->at(i+1,j-1) += change / 22.63f;
        m_height->at(i  ,j+1) += change / 16.0f;
        m_height->at(i  ,j-1) += change / 16.0f;
        m_height->at(i-1,j+1) += change / 22.63f;
        m_height->at(i-1,j  ) += change / 16.0f;
        m_height->at(i-1,j-1) += change / 22.63f;
      }
      m_water->at(i,j) += m_water_temp->at(i,j) -.00001;

      if (m_water->at(i,j) < 0.0) {
        m_water->at(i,j) = 0.0;
      } 
      if (m_water->at(i,j) > 1.0) {
        m_water->at(i,j) = 1.0;
      }

      m_water_temp->at(i,j) = 0.0;
    }
  }
}

void TrMap::updateNormals() {
  // go through the map
  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_cols; j++) {
      // l->r
      Vec3 lr(2.0, 0.0, 255.0 * (m_height->at(i,j+1) - m_height->at(i,j-1)));
      // u->d
      Vec3 ud(0.0, 2.0, 255.0 * (m_height->at(i+1,j) - m_height->at(i-1,j)));
      
      m_normal->at(i,j) = Vec3::cross(lr,ud);
      m_normal->at(i,j).normalize();
    }
  }
}


void renderTextureWithOffset(SDL_Renderer* renderer, SDL_Texture* texture, int xOff, int yOff, int pixelSize) {
  SDL_Rect SrcR;
  SDL_Rect DestR;

  SrcR.x = xOff / pixelSize;
  SrcR.y = yOff / pixelSize;
  SrcR.w = K_MAP_SIZE - xOff / pixelSize;
  SrcR.h = K_MAP_SIZE - yOff / pixelSize;

  DestR.x = 0;
  DestR.y = 0;
  DestR.w = sz(K_DISPLAY_SIZE) - xOff;
  DestR.h = sz(K_DISPLAY_SIZE) - yOff;

  SDL_RenderCopy(renderer, texture, &SrcR, &DestR);
}


void TrMap::printSimpleHeightMatrix() {
  int threshold[9] = {70, 100, 117, 132, 148, 165, 180, 198, 218};

  uint32_t simpleHeights[9] = {0,1,2,
              3,4,5,
              6,7,8};

  std::cout << m_rows << " " << m_cols << endl;


  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_cols; j++) {
      // render land
      for (int c = 0; c < 9; c++) {
        if (m_height->get(i,j) * 255 < threshold[c]) {
          std::cout << simpleHeights[c] << " ";
          break;
        }

        if (m_height->get(i,j) * 255 >= threshold[8]) {
          std::cout << 9 << " ";
          break;
        }
      }
    }
    std::cout << endl;
  }
}