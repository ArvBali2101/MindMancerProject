#include <iostream>
#include <thread>

#include "../include/MotivationalQuoteManager.h"

int main() {
  MotivationalQuoteManager quoteManager(1);  // quote every 1 sec

  quoteManager.startTask("Test");
  for (int i = 0; i < 3; ++i) {
    quoteManager.update();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  quoteManager.stopTask();

  std::cout << "✅ TestMotivationalQuoteManager passed.\n";
  return 0;
}
