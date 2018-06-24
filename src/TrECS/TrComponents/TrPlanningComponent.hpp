#pragma once

/**
 * TrComponents.hpp
 */

#include <set>

#include "../TrComponents.hpp"
#include "../../Utils.hpp"

using namespace std;

/**
 * @brief holds information about a intended destination to go to
 * @details urgency is on the scale of 0 to 7
 */

struct tr_target_t {
  SDL_Point m_loc;
  uint8_t urgency;
};

inline bool operator==(const tr_target_t& lhs, const tr_target_t& rhs) {
  return lhs.urgency == rhs.urgency && lhs.m_loc == rhs.m_loc;
}

inline bool operator<(const tr_target_t& lhs, const tr_target_t& rhs)
{
  return lhs.urgency < rhs.urgency;
}

/**
 * @brief interface for all planning components
 */
class TrPlanningComponent : public TrComponent {
 public:
  TrPlanningComponent() = default;
  ~TrPlanningComponent() override = default;

  /**
   * @brief based on the game and entity state, figure out something to do
   */
  template<class C>
  void update(TrGame *game, C *entity);
    
  void addTarget(tr_target_t t);
  void removeTarget(tr_target_t t);
  // TODO: getCurrentTarget

 private:
  bool m_current_target_is_valid = false;
  tr_target_t m_current_target;
  set<tr_target_t> m_targets;
};

template<class C>
void TrPlanningComponent::update(TrGame *game, C *entity) {
  // No need to update planning if the current target is still okay.
  if (m_current_target_is_valid || m_targets.empty()) return;

  // TODO: Remove current target once we've reached it.
  m_current_target = *std::min_element(m_targets.begin(), m_targets.end());
  m_current_target_is_valid = true;
}

