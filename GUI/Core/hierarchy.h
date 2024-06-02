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
#include <map>

using namespace std;

class Hierarchy : public ClusteringAlgorithm
{
public:
  Hierarchy(int cluster_cnt, int iterations):
           ClusteringAlgorithm(cluster_cnt, iterations) {};

  ClusteringResult Run(vector<Point>& points) override {

    for(Point i: points) {
      Cluster j = Cluster(i.GetPointId(), i);
      _clusters.push_back(j);
    }

    while (_clusters.size() > _cluster_cnt) {
        double minDist = 100000;
        int cluster1 = -1, cluster2 = -1;
        
        for (unsigned int i = 0; i < _clusters.size() - 1; i++) {
            for (unsigned int j = i + 1; j < _clusters.size(); j++) {
                double Dist = ClusterDistance(_clusters[i], _clusters[j]);
                if (Dist < minDist) {
                    minDist = Dist;
                    cluster1 = i;
                    cluster2 = j;
                }
            }
        }

        _clusters[cluster1].merge(_clusters[cluster2]);
        _clusters.erase(_clusters.begin() + cluster2);
    }

    ClusteringResult res = {_iterations};
    res.SetPoints(points);
    res.SetClusters(_clusters);
    
    cout << Silhouette(_clusters, points) << '\n'; //terminal debug
    for (size_t i = 0; i < _clusters.size(); i++) {
      cout << "Id: " <<_clusters[i].GetClusterId() << '\n';
      cout << "Size: " <<_clusters[i].GetClusterSize() << '\n';
      cout << "Centroid X: " <<_clusters[i].GetCentroidX() << '\n';
      cout << "Centroid Y: " <<_clusters[i].GetCentroidY() << '\n';
    }

    return res;
  };
};
