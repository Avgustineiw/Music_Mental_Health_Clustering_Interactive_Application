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
  ClusteringResult(int iterations = 0):
                   _iterations(iterations) {};
  ~ClusteringResult() {};
  void SetIterations(int iterations) {
      this->_iterations = iterations;
  }
  void SetPoints(vector<Point> points) {
      this->_points = points;
  }
  void SetClusters(vector<Cluster> clusters) {
      this->_clusters = clusters;
  }

  int GetIterations() const {
    return _iterations;
  }
  int GetPointsSize() const {
    return _points.size();
  }
  int GetClustersSize() const {
    return _clusters.size();
  }
  Point GetPoint(int i) const {
    return _points[i];
  }
  Cluster GetCluster(int i) const {
    return _clusters[i];
  }

  vector<Point> GetPoints() {
    return _points;
  }

  vector<Cluster> GetClusters() {
    return _clusters;
  }
};
