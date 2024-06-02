#pragma once
#include "hierarchy.h"
#include "readFromCSV.h"
#include "respondentToPoint.h"
#include "point.h"
#include "k-medoids.h"
#include "hierarchy.h"
#include "SLINK.h"

#include <vector>
#include <ctime>

#include <QString>
#include <QVector>
#include <QVariant>

#include "k-means.h"

vector<Point> InitializeProgram(const QVector<QVector<QVariant>>& tableData)
{
  vector<vector<string>> data;
  vector<Point>          data_points;
  vector<Respondent>     respondents;

  data.push_back({});
  for (qsizetype i = 0; i < tableData.size(); ++i) {
      data.push_back({});
      for (qsizetype j = 0; j < tableData[0].size(); ++j) {
          data.back().push_back(tableData[i][j].toString().toStdString());
      }
  }
  DataToRespondent(data, respondents);

  for (size_t i = 0; i < respondents.size(); i++) {
    data_points.push_back(respondentToPoint(respondents[i], i+1));
  }

  // Hierarchy clustering = {2, 10}; //terminal debug
  // clustering.Run(data_points);

  return data_points;
}

vector<Point> InitializeProgram(QString CSV_PATH)
{
  vector<vector<string>> data;
  vector<Point>          data_points;
  vector<Respondent>     respondents;

  ReadFromCSV(CSV_PATH, data);
  DataToRespondent(data, respondents);

  for (size_t i = 0; i < respondents.size(); i++) {
      data_points.push_back(respondentToPoint(respondents[i], i+1));
    }

         // Hierarchy clustering = {2, 10}; //terminal debug
         // clustering.Run(data_points);

  return data_points;
}
