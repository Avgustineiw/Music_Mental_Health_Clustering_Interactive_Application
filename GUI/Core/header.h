#pragma once
#include "hierarchy.h"
#include "readFromCSV.h"
#include "respondentToPoint.h"
#include "point.h"

#include <vector>
#include <ctime>

#include <QString>

#include "k-means.h"

vector<Point> InitializeProgram(QString CSV_PATH)
{
  vector<vector<string>> data;
  vector<Point> data_points;
  vector<Respondent> respondents;

  ReadFromCSV(CSV_PATH, data);
  DataToRespondent(data, respondents);

  for (size_t i = 0; i < respondents.size(); i++) {
    data_points.push_back(respondentToPoint(respondents[i], i+1));
  }

  // Hierarchy clustering = {2, 10}; //terminal debug
  // clustering.Run(data_points);

  return data_points;
}
