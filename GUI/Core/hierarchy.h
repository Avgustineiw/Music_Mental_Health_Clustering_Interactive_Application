#pragma once
#include "point.h"
#include "clusteringAlgorithm.h"
#include "clusteringResult.h"

#include <algorithm>
#include <cstdlib>
#include <set>
#include <vector>
#include <iostream>
#include "silhouette.h"

using namespace std;


class Hierarchy : public ClusteringAlgorithm
{ 
public:
  Hierarchy(int cluster_cnt, int iterations):
         ClusteringAlgorithm(cluster_cnt, iterations) {};
  
  ClusteringResult Run(vector<Point>& points) override {
    _total_points = points.size();

    unsigned int unique_clusters = 0;

    for (unsigned int i = 0; i < _total_points; i++) {
      points[i].SetClusterId(points[i].GetPointId()+_cluster_cnt+1);
      unique_clusters++;
    }

    int index_1 = 0;
    int index_2 = 0;

    while (unique_clusters > _cluster_cnt) {
      double min_dist = INT_MAX;

      #pragma omp parallel num_threads(16)

      for (unsigned int i = 0; i < _total_points; i++) {
        for (unsigned int j = 0; j < _total_points; j++) {
          if (points[i].GetClusterId() != points[j].GetClusterId()) {
            double dist = Distance(points[i], points[j]);
            if (dist < min_dist) {
              min_dist = dist;
              index_1 = points[i].GetClusterId();
              index_2 = points[j].GetClusterId();
            }
          }
        }
      }

      for (unsigned int i = 0; i < _total_points; i++) {
        if (points[i].GetClusterId() == index_2) {
          points[i].SetClusterId(index_1);
        }
      }

      unique_clusters--;
    }

    vector<int> remaining_ids;

    for (unsigned int i = 0; i < _total_points; i++) {
      if (remaining_ids.size() == _cluster_cnt) {
        break;
      }
      int index = points[i].GetClusterId();
      if (find(remaining_ids.begin(), remaining_ids.end(), index) == remaining_ids.end()) {
        remaining_ids.push_back(index);
        Cluster cluster(remaining_ids.size(), points[i]);
        _clusters.push_back(cluster);
      }
    }

    for (unsigned int i = 0; i < _total_points; i++) {
      for (unsigned int j = 0; j < _cluster_cnt; j++) {
        if (points[i].GetClusterId() == remaining_ids[j]) {
          points[i].SetClusterId(j);
          _clusters[j].SetPoint(points[i]);
        }
      }
    }

    // cout << Silhouette(_clusters, points) << '\n'; //terminal debug
    // for (unsigned int i = 0; i < _clusters.size(); i++) {
    //   cout << "Id: " <<_clusters[i].GetClusterId() << '\n';
    //   cout << "Size: " <<_clusters[i].GetClusterSize() << '\n';
    //   cout << "Centroid X: " <<_clusters[i].GetCentroidX() << '\n';
    //   cout << "Centroid Y: " <<_clusters[i].GetCentroidY() << '\n';
    // }

    ClusteringResult res = {_iterations};
    res.SetPoints(points);
    res.SetClusters(_clusters);

    return res;
  }
};
