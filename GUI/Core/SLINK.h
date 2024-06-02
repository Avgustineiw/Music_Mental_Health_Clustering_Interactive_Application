#pragma once
#include "point.h"
#include "clusteringAlgorithm.h"
#include "silhouette.h"
#include "clusteringResult.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <vector>
#include <set>
#include <map>


using namespace std;

//Hierarchy (SLINK) clustering algorithm
class SLINK : public ClusteringAlgorithm
{
public:
  SLINK(int cluster_cnt, int iterations):
           ClusteringAlgorithm(cluster_cnt, iterations) {};

ClusteringResult Run(vector<Point>& points) override {
    
    unsigned int size = points.size();
    vector<int> pi(size), lambda(size);
    vector<vector<double>> D(size, vector<double>(size, 0));

    for (unsigned int i = 0; i < size; ++i) {
        pi[i] = i;
        lambda[i] = INT_MAX;
    }

    for (unsigned int i = 1; i < size; i++) {
        for (unsigned int j = 0; j < i; j++) {
            D[i][j] = Distance(points[i], points[j]);
        }

        int m = i;

        for (unsigned int j = 0; j < i; j++) {
            if (D[i][j] < lambda[j]) {
                lambda[j] = D[i][j];
                pi[j] = i;
            }
            if (lambda[j] < lambda[m]) {
                m = j;
            }
        }

        for (unsigned int j = 0; j < i; j++) {
            if (lambda[j] >= lambda[m]) {
                D[i][j] = lambda[j];
            } else {
                D[i][j] = lambda[m];
                lambda[m] = lambda[j];
                pi[m] = pi[j];
                m = j;
            }
        }

        lambda[m] = INT_MAX;
    }

    vector<int> clusterId(size);
    
    for (unsigned int i = 0; i < size; i++) {
        clusterId[i] = i;
    }

    for (unsigned int i = 0; i < size - _cluster_cnt; i++) {
        int minIndex = min_element(lambda.begin(), lambda.end()) - lambda.begin();
        int root = pi[minIndex];

        for (unsigned int j = 0; j < size; j++) {
            if (clusterId[j] == minIndex) {
                clusterId[j] = root;
            }
        }

        lambda[minIndex] = INT_MAX;
    }

    
    for(unsigned int i = 0; i < size; i++) {
      points[i].SetClusterId(clusterId[i]);
    }
    
    set<int> uniqueIDs(clusterId.begin(), clusterId.end());
    unsigned int clusterId_cnt = uniqueIDs.size();

    //O(N^3) worst case;
    while (clusterId_cnt > _cluster_cnt) {
        double minDist = INT_MAX;
        int clusterID1 = -1, clusterID2 = -1;
        for (unsigned int i = 0; i < size - 1; i++) {
            for (unsigned int j = i + 1; j < size; j++) {

                if(points[i].GetClusterId() != points[j].GetClusterId()) {
                    double Dist = Distance(points[i], points[j]);

                    if (Dist < minDist) {
                        minDist = Dist;
                        clusterID1 = points[i].GetClusterId();
                        clusterID2 = points[j].GetClusterId();
                    }
                }
            }
        }

        for(unsigned int i = 0; i < size; i++) {
            if(points[i].GetClusterId() == clusterID2) {
                points[i].SetClusterId(clusterID1);
            }
        }
        clusterId_cnt--;
    }

    set<int> uniqueIDs2;
    map<int,int> oldID_newID;
    int tmp = 1;
    for(Point i : points) {
        uniqueIDs2.insert(i.GetClusterId());
    }
    for(unsigned int i : uniqueIDs2) {
        oldID_newID[i] = tmp++;
    }
    for(unsigned int i = 0; i < size; i++) {
        points[i].SetClusterId(oldID_newID[points[i].GetClusterId()]);
    }

    for(unsigned int i = 0; i < _cluster_cnt; i++) {
        Cluster cluster = Cluster(i + 1, points[i]);
        for(unsigned int j = 0; j < size; j++) {
            if(points[j].GetClusterId() == i + 1) {
                cluster.SetPoint(points[j]);
            }
        }
        _clusters.push_back(cluster);
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
