#include "../include/magic.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cassert>

int main() {
  std::srand(std::time(nullptr));

  magictest<int, int>(
    [](int f_x, int x) {
      assert(f_x == x);
    },
    [](int x) {
      return x;
    },
    {
      []() {
        return std::rand();
      }
    }
  );
}
