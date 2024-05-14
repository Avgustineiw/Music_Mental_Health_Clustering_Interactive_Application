#pragma once
#include "readFromCSV.h"
#include "respondentToPoint.h"
#include "k-means.h"

#include <vector>
#include <iostream>
#include <ctime>

const string CSV_PATH = "/Users/avgustine/Project_cpp/music_health_data.csv";
const string OUTPUT_PATH = "/Users/avgustine/Project_cpp/output.csv";


void InitializeProgram()
{
  vector<vector<string>> data;
  vector<Respondent> respondents;
  vector<ClusterPoint> data_points;

  srand(time(NULL));

  ReadFromCSV(CSV_PATH, data);
  DataToRespondent(data, respondents);


  for (size_t i = 0; i < respondents.size(); i++) {
    data_points.push_back(respondentToPoint(respondents[i]));
  }
  
  KMeans clustering = {2, 100, OUTPUT_PATH};
  clustering.Run(data_points);
}
