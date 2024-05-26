#pragma once
#include "point.h"
#include "clusteringAlgorithm.h"
#include "clusteringResult.h"

#include <vector>

using namespace std;


class KMeans : public ClusteringAlgorithm
{ 
public:
  KMeans(int cluster_cnt, int iterations):
         ClusteringAlgorithm(cluster_cnt, iterations) {};
  
  ClusteringResult Run(vector<Point>& points) override {
    _total_points = points.size();

    vector<int> used_pointIds;

    for (unsigned int i = 1; i < _cluster_cnt + 1; i++) {
      while (true) {
        int index = rand() % _total_points;

        if (find(used_pointIds.begin(), used_pointIds.end(), index) == used_pointIds.end()) {
          used_pointIds.push_back(index);
          points[index].SetClusterId(i);
          Cluster cluster(i, points[index]);
          _clusters.push_back(cluster);
          break;
        }
      }
    }

    unsigned int iter = 1;

    while (true) {
      bool done = true;

      for (unsigned int i = 0; i < _total_points; i++) {
        int currentClusterId = points[i].GetClusterId();
        int nearestClusterId = GetNearestClusterId(points[i]);
        
        if (currentClusterId != nearestClusterId) {
          points[i].SetClusterId(nearestClusterId);
          done = false;
        }
      }
        
      ClearClusters();

      for (unsigned int i = 0; i < _total_points; i++) {
        _clusters[points[i].GetClusterId() - 1].SetPoint(points[i]);
      }

      for (unsigned int i = 0; i < _cluster_cnt; i++) {
        unsigned int clusterSize = _clusters[i].GetClusterSize();

        double sum_x = 0, sum_y = 0;
        if (clusterSize > 0) {
          for (unsigned int j = 0; j < clusterSize; j++) {
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

    ClusteringResult res = {_iterations};
    res.SetClusters(_clusters);
    res.SetPoints(points);

    // cout << Silhouette(_clusters, points) << '\n'; //terminal debug
    // for (unsigned int i = 0; i < _clusters.size(); i++) {
    //   cout << "Id: " <<_clusters[i].GetClusterId() << '\n';
    //   cout << "Size: " <<_clusters[i].GetClusterSize() << '\n';
    //   cout << "Centroid X: " <<_clusters[i].GetCentroidX() << '\n';
    //   cout << "Centroid Y: " <<_clusters[i].GetCentroidY() << '\n';
    // }

    return res;
  }
};
