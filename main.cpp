#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cassert>

#include "mutexed.hpp"

int main() {
  mutexed::Mutexed<std::vector<std::string>> words;

  {
    auto ptr = words.Lock();
    ptr->push_back("abra");
    ptr->push_back("cadabra");
    assert(ptr->size() == 2);
  }
  {
    auto ptr = words.Lock();
    ptr->clear();
    assert(ptr->empty());
  }


  mutexed::Mutexed<int> counter{0};
  {
    auto ptr = counter.Lock();

    std::vector<std::thread> pool;
    for (int n = 0; n < 10; ++n) {
      pool.emplace_back([&](){
        *ptr = *ptr + 1;
      });
    }

     for (auto& th : pool) {
      th.join();
    }
  }
  {
    auto ptr = counter.Lock();
    std::cout << *ptr << "\n";
    assert(*ptr == 10);
  }

  return 0;
}
