#pragma once
#include "clusteringResult.h"
#include "point.h"

#include <vector>
#include <cmath>
#include <vector>

using namespace std;


class ClusteringAlgorithm
{
protected:
  unsigned int _cluster_cnt;
  unsigned int _iterations;
  unsigned int _total_points;
  vector<Cluster> _clusters;
  
  void ClearClusters() {
    for (unsigned int i = 0; i < _cluster_cnt; i++) {
      _clusters[i].RemoveAllPoints();
    }
  }

  double Distance(Point A, Point B) {
    return sqrt(pow(A.GetX() - B.GetX(), 2) + pow(A.GetY() - B.GetY(), 2));
  }

  Point GetNearestPoint(vector<Point>& points, double x, double y) {
    double min_dist = INT_MAX;
    int id = 0;
    for (unsigned int i = 0; i < points.size(); i++) {
      double dist = 0;
      dist += pow(x - points[i].GetX(), 2);
      dist += pow(y - points[i].GetY(), 2);
      dist = sqrt(dist);
      
      if (dist < min_dist) {
        min_dist = dist;
        id = i;
      }
    }

    return points[id];
  }

  int GetNearestClusterId(Point& point) const {
    double sum = 0, dist = 0, min_dist = INT_MAX;
    int NearestClusterId = 0;
    
    sum += pow(_clusters[0].GetCentroidX() - point.GetX(), 2);
    sum += pow(_clusters[0].GetCentroidY() - point.GetY(), 2);

    min_dist = sqrt(sum);

    NearestClusterId = _clusters[0].GetClusterId();

    for (unsigned int i = 1; i < _cluster_cnt; i++) {
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

  double Distance(const Point& p1, const Point& p2) {
    double point1 = p1.GetX() - p2.GetX();
    double point2 = p1.GetY() - p2.GetY();
    return (point1) * (point1) + (point2) * (point2);
  }

  double ClusterDistance(const Cluster& cluster1, const Cluster& cluster2) {
        double MinDist = 100000;
        for (Point i : cluster1.GetPoints()) {
            for (Point j : cluster2.GetPoints()) {
                double Dist = Distance(i, j);
                if (Dist < MinDist) {
                    MinDist = Dist;
                }
            }
        }
        return MinDist;
    };

public:
  ClusteringAlgorithm(int cluster_cnt, int iterations):  
                       _cluster_cnt(cluster_cnt), _iterations(iterations) {};
  virtual ClusteringResult Run(vector<Point>& points) = 0;
};
