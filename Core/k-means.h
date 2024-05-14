#pragma once
#include "point.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;


class KMeans
{
private:
  int _cluster_cnt;
  int _iterations;
  int _total_points;
  vector<Cluster> _clusters;
  string _output_path;
  
  void ClearClusters() {
    for (size_t i = 0; i < _cluster_cnt; i++) {
      _clusters[i].RemoveAllPoints();
    }
  }

  int GetNearestClusterId(ClusterPoint point) {
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
  KMeans(int cluster_cnt, int iterations, string output_path): 
         _cluster_cnt(cluster_cnt), _iterations(iterations), _output_path(output_path) {};
  
  void Run(vector<ClusterPoint> points) {
    _total_points = points.size();

    vector<int> used_pointIds;

    for (size_t i = 1; i < _cluster_cnt + 1; i++) {
      while (true) {
        int index = rand() % _total_points;

        if (find(used_pointIds.begin(), used_pointIds.end(), index) == used_pointIds.end()) {
          used_pointIds.push_back(index);
          points[index].SetClusterId(i);
          Cluster cluster(i, points[i]);
          _clusters.push_back(cluster);
          break;
        }
      }
    }

    int iter = 1;

    while (true) {
      bool done = true;

      for (size_t i = 0; i < _total_points; i++) {
        int currentClusterId = points[i].GetClusterId();
        int nearestClusterId = GetNearestClusterId(points[i]);
        
        if (currentClusterId != nearestClusterId) {
          points[i].SetClusterId(nearestClusterId);
          done = false;
        }
      }
        
      ClearClusters();

      for (size_t i = 0; i < _total_points; i++) {
        _clusters[points[i].GetClusterId() - 1].SetPoint(points[i]);
      }

      for (size_t i = 0; i < _cluster_cnt; i++) {
        int clusterSize = _clusters[i].GetClusterSize();

        double sum_x = 0, sum_y = 0;
        if (clusterSize > 0) {
          for (size_t j = 0; j < clusterSize; j++) {
            sum_x += _clusters[i].GetPoint(j).GetX();
            sum_y += _clusters[i].GetPoint(j).GetY();
          }
          _clusters[i].SetCentroidX(sum_x / clusterSize);
          _clusters[i].SetCentroidY(sum_y / clusterSize);
        }
      }

      if (done || iter >= _iterations) {
        break;
      }
      iter++;
    }
    
    ofstream output(_output_path);

    for (size_t i = 0; i < _total_points; i++) {
      output << points[i].GetX() << "," << points[i].GetY() << "," << points[i].GetClusterId() << '\n';
    }

    output.close();

    for (size_t i = 0; i < _cluster_cnt; i++) {
      cout << "cluster id: " << _clusters[i].GetClusterId() << '\n';
      cout << "Amount of points: " << _clusters[i].GetClusterSize() << '\n';
      cout << "Centroid X: " << _clusters[i].GetCentroidX() << '\n';
      cout << "Centroid Y: " << _clusters[i].GetCentroidY() << "\n\n";
    }
  }
};
