#pragma once
#include "respondent.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include <QString>

using namespace std;


void ReadFromCSV(string& CSV_PATH, vector<vector<string>>& data)
{
  ifstream csv;
  csv.open(CSV_PATH, ifstream::in);

  if (!csv.is_open()) {
    throw std::runtime_error("Failed to open csv file");
    return;
  }

  string line, field;

  while (!csv.eof()) {
    getline(csv, line);
    stringstream ss_line(line);
    vector<string> tmp_data;

    while (getline(ss_line, line, ',')) {
      tmp_data.push_back(line);
    }
    data.push_back(tmp_data);
  }

  csv.close();
  return;
}


int Frequency(const string& field)
{
  if (field == "Rarely") {
    return 1;
  }
  else if (field == "Sometimes") {
    return 2;
  }
  else if (field == "Very Frequently") {
    return 3;
  }

  return 0;
}

int Effect(const string& field) 
{
  if (field == "Improve") {
    return 1;
  }
  
  return 0;
}


int ValidStringToInt(const string& field)
{
  if (!field.empty()) {
    return stoi(field);
  }

  return 0;
}


double ValidStringToDouble(const string& field)
{
  if (!field.empty()) {
    return stod(field);
  }

  return 0;
}


int Musician(const string& field_inst, const string& field_comp)
{
  if (field_inst == "YES" && field_comp == "YES") {
    return 1;
  }

  return 0;
}


void DataToRespondent(vector<vector<string>>& data, vector<Respondent>& respondents)
{
  for (size_t i = 1; i < data.size(); i++) { //start from 1 to avoid field names
    int age = 0;
    double hpd = 0;
    int musician = 0;
    int frequency = 0;
    int anxiety = 0;
    int depression = 0;
    int insomnia = 0;
    int ocd = 0;
    int effect = 0;

    for (size_t j = 0; j < data[i].size(); j++) {
      switch (j) {
        case 1: //age
          age = ValidStringToInt(data[i][j]);
          break;
        case 3: //hpd 
          hpd = ValidStringToDouble(data[i][j]);
          break;
        case 5: //instrumental and composer
          musician = Musician(data[i][j], data[i][j+1]);
          break;
        case 11: //frequency classical
          frequency += Frequency(data[i][j]);
          break;
        case 12: //frequency country
          frequency += Frequency(data[i][j]);
          break;
        case 13: //frequency EDM
          frequency += Frequency(data[i][j]);
          break;
        case 14: //frequency folk
          frequency += Frequency(data[i][j]);
          break;
        case 15: //frequency Gospel
          frequency += Frequency(data[i][j]);
          break;
        case 16: //frequency Hip Hop
          frequency += Frequency(data[i][j]);
          break;
        case 17: //frequency jazz
          frequency += Frequency(data[i][j]);
          break;
        case 18: //frequency K-pop
          frequency += Frequency(data[i][j]);
          break;
        case 19: //frequency Latin
          frequency += Frequency(data[i][j]);
          break;
        case 20: //frequency Lofi
          frequency += Frequency(data[i][j]);
          break;
        case 21: //frequency metal
          frequency += Frequency(data[i][j]);
          break;
        case 22: //frequency pop
          frequency += Frequency(data[i][j]);
          break;
        case 23: //frequency R&B
          frequency += Frequency(data[i][j]);
          break;
        case 24: //frequency Rap
          frequency += Frequency(data[i][j]);
          break;
        case 25: //frequency Rock
          frequency += Frequency(data[i][j]);
          break;
        case 26: //frequency Video Game Music
          frequency += Frequency(data[i][j]);
          break;
        case 27: //Anxiety
          anxiety = ValidStringToInt(data[i][j]);
          break;
        case 28: //Depression
          depression = ValidStringToInt(data[i][j]);
          break;
        case 29: //Insomnia
          insomnia = ValidStringToInt(data[i][j]);
          break;
        case 30: //OCD
          ocd = ValidStringToInt(data[i][j]);
          break;
        case 31: //Effect
          effect = Effect(data[i][j]);
          break;
      }
    }

    Respondent tmp_respondent = {age, hpd, musician, frequency, anxiety, depression, insomnia, ocd,                                  effect};
    respondents.push_back(tmp_respondent);
  }
  return;
}
