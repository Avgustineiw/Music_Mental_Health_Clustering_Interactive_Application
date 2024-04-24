#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void ReadFromCSV(const string& DATA_PATH) 
{
  ifstream csv(DATA_PATH);

  string line, field;

  while (!csv.eof()) {
    getline(csv, line);
    stringstream ss_line(line);
    
    for (size_t i = 1; i < 34; i++) { 
      switch (i) {
        case 2: //age
          break;
        case 4: //hpd 
          break;
        case 6: //instrumental
          break;
        case 7: //composer
          break;
        case 11: //bpm
          break;
        case 12: //frequency classical
          break;
        case 13: //frequency country
          break;
        case 14: //frequency EDM
          break;
        case 15: //frequency folk
          break;
        case 16: //frequency Gospel
          break;
        case 17: //frequency Hip Hop
          break;
        case 18: //frequency jazz
          break;
        case 19: //frequency K-pop
          break;
        case 20: //frequency Latin
          break;
        case 21: //frequency Lofi
          break;
        case 22: //frequency metal
          break;
        case 23: //frequency pop
          break;
        case 24: //frequency R&B
          break;
        case 25: //frequency Rap
          break;
        case 26: //frequency Rock
          break;
        case 27: //frequency Video Game Music
          break;
        case 28: //Anxiety
          break;
        case 29: //Depression
          break;
        case 30: //Insomnia
          break;
        case 31: //OCD
          break;
        case 32: //Effect
          break;
      }
    }
  }

  return;
}


void WriteToCSV(const string& DATA_PATH)
{
  

  return;
}
