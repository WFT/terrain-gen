#include "TrPlanningComponent.hpp"

void TrPlanningComponent::addTarget(tr_target_t t) {
  this->m_targets.insert(t);
}

void TrPlanningComponent::removeTarget(tr_target_t t) {
  this->m_targets.erase(t);
  // Invalidate the current target if these are equivalent.
  if (t == m_current_target) {
      m_current_target_is_valid = false;
  }
}
