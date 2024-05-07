#include "readFromCSV.h"
#include "respondentToPoint.h"

#include <vector>
#include <iostream>

const string CSV_PATH = "music_health_data.csv";
const string OUTPUT_PATH = "output.csv";

void InitializeProgram()
{
  vector<vector<string>> data;
  vector<Respondent> respondents;

  ReadFromCSV(CSV_PATH, data);
  DataToRespondent(data, respondents);

  ofstream output_file(OUTPUT_PATH);

  for (size_t i = 0; i < respondents.size(); i++) {
    // cout << respondents[i];
    double x = 0, y = 0;
    x = respondentToPoint(respondents[i]).GetX();
    y = respondentToPoint(respondents[i]).GetY();
    if (y != 0) {
      output_file << x << "," << y << '\n';
    }
  }
}
