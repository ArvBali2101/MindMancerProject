#include <cassert>
#include <iostream>

#include "../include/SessionConfigManager.h"

int main() {
  std::cout << "🔧 Running SessionConfigManager tests...\n";

  SessionConfigManager config;

  // ✅ Test 1: Check default durations
  assert(config.getDefaultWorkDuration() == 1500);  // 25 minutes
  assert(config.getDefaultBreakDuration() == 300);  // 5 minutes
  std::cout << "✅ Default durations OK\n";

  // ✅ Test 2: Change durations and verify
  config.setDefaultWorkDuration(1200);  // 20 minutes
  config.setDefaultBreakDuration(180);  // 3 minutes
  assert(config.getDefaultWorkDuration() == 1200);
  assert(config.getDefaultBreakDuration() == 180);
  std::cout << "✅ Custom durations OK\n";

  std::cout << "✅ TestSessionConfigManager passed.\n";
  return 0;
}
