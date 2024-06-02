#pragma once
#include <string>
#include <time.h>

const std::string currentDateTime() {
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  for (unsigned int i = 0; i < sizeof(buf); i++) {
      if (buf[i] == ':') {
          buf[i] = '-';
        }
    }

  return buf;
}
