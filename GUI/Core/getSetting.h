#pragma once
#include <string>
#include <fstream>
#include <sstream>

std::string GetSetting(const std::string& path, int id)
{
  std::ifstream settings(path);
  std::string line; 
  std::string res = "";
  int i = 0;
  while (!settings.eof()) {
    getline(settings, line);
    if (i == id) {
      std::stringstream ss(line);
      for (unsigned int j = 0; j < 3; j++) {
        ss >> res;
      }
      break;
    }
    
    i++;
  }

  return res;
}
