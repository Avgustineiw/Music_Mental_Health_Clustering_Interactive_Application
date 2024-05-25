#include "string"
#include "getSetting.h"
#include <iostream>

const std::string INPUT_PATH = "/Users/avgustine/Project_cpp/GUI/build/Source/settings.txt";


int main()
{
  std::cout << GetSetting(INPUT_PATH, 0);
}
