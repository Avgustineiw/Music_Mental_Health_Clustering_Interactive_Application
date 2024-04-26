#include "readFromCSV.h"

const string CSV_PATH = "music_health_data.csv";


void InitializeProgram()
{
  vector<vector<string>> data;
  vector<Respondent> respondents;

  ReadFromCSV(CSV_PATH, data);
  DataToRespondent(data, respondents);

  for (size_t i = 0; i < respondents.size(); i++) {
    cout << respondents[i];
  }
}
