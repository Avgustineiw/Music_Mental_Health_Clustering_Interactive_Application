#pragma once
#include "point.h"
#include "clusteringAlgorithm.h"
#include "silhouette.h"
#include "clusteringResult.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;


class KMeans : public ClusteringAlgorithm
{
private:
  string _output_path;
  
public:
  KMeans(int cluster_cnt, int iterations, string output_path): 
         ClusteringAlgorithm(cluster_cnt, iterations), _output_path(output_path) {};
  
  ClusteringResult Run(vector<Point> points) override {
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
      output << points[i].GetX() << "," << points[i].GetY() << "," << points[i].GetClusterId() << "," << points[i].GetPointId() << '\n';
    }

    output.close();

    // for (size_t i = 0; i < _cluster_cnt; i++) {
    //   cout << "cluster id: " << _clusters[i].GetClusterId() << '\n';
    //   cout << "Amount of points: " << _clusters[i].GetClusterSize() << '\n';
    //   cout << "Centroid X: " << _clusters[i].GetCentroidX() << '\n';
    //   cout << "Centroid Y: " << _clusters[i].GetCentroidY() << "\n\n";
    // }
    
    cout << Silhouette(_clusters, points);

    ClusteringResult res = {_iterations, points, _clusters};
    
    return res;
  }
};
