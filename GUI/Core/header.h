#pragma once
#include "readFromCSV.h"
#include "respondentToPoint.h"
#include "k-means.h"
#include "point.h"
#include "k-medoids.h"
#include "hierarchy.h"

#include <vector>
#include <iostream>
#include <ctime>

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

   Hierarchy clustering = {2, 10}; //terminal debug
   clustering.Run(data_points);

  return data_points;
}
