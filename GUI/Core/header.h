#pragma once
#include "readFromCSV.h"
#include "respondentToPoint.h"
#include "k-means.h"
#include "point.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <QString>

vector<Point> InitializeProgram(string CSV_PATH)
{
  vector<vector<string>> data;
  vector<Respondent> respondents;
  vector<Point> data_points;

  ReadFromCSV(CSV_PATH, data);
  DataToRespondent(data, respondents);

  for (size_t i = 0; i < respondents.size(); i++) {
    data_points.push_back(respondentToPoint(respondents[i], i+1));
  }

  return data_points;
  
  //KMeans clustering = {2, 10, OUTPUT_PATH};
  //clustering.Run(data_points);
}
