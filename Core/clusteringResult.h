#pragma once

#include "point.h"

#include <vector>


class ClusteringResult
{
private:
  int _iterations;
  vector<Point> _points;
  vector<Cluster> _clusters;

public:
  ClusteringResult(int iterations, vector<Point> points, vector<Cluster> clusters):
                   _iterations(iterations), _points(points), _clusters(clusters) {};
  ~ClusteringResult() {};

  int GetIterations() const {
    return _iterations;
  }
  int GetPointsSize() const {
    return _points.size();
  }
  int GetClustersSize() const {
    return _clusters.size();
  }
  Point GetPoint(int& i) const {
    return _points[i];
  }
  Cluster GetCluster(int& i) const {
    return _clusters[i];
  }
};
