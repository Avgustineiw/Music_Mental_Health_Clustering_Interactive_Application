#pragma once
#include "clusteringResult.h"
#include "point.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;


class ClusteringAlgorithm
{
protected:
  int _cluster_cnt;
  int _iterations;
  int _total_points;
  vector<Cluster> _clusters;
  
  void ClearClusters() {
    for (size_t i = 0; i < _cluster_cnt; i++) {
      _clusters[i].RemoveAllPoints();
    }
  }

  int GetNearestClusterId(Point point) {
    double sum = 0, dist = 0, min_dist = 0;
    int NearestClusterId = 0;
    
    sum += pow(_clusters[0].GetCentroidX() - point.GetX(), 2);
    sum += pow(_clusters[0].GetCentroidY() - point.GetY(), 2);

    min_dist = sqrt(sum);

    NearestClusterId = _clusters[0].GetClusterId();

    for (size_t i = 1; i < _cluster_cnt; i++) {
      sum = 0;
      dist = 0;

      sum += pow(_clusters[i].GetCentroidX() - point.GetX(), 2);
      sum += pow(_clusters[i].GetCentroidY() - point.GetY(), 2);

      dist = sqrt(sum);

      if (dist < min_dist) {
        min_dist = dist;
        NearestClusterId = _clusters[i].GetClusterId();
      }
    }

    return NearestClusterId;
  }

public:
  ClusteringAlgorithm(int cluster_cnt, int iterations):  
                       _cluster_cnt(cluster_cnt), _iterations(iterations) {};
  virtual ClusteringResult Run(vector<Point> points) = 0;
};
