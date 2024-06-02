#pragma once
#include <vector>

using namespace std;


class Point
{
protected:
  double _x;
  double _y;
  int _pointId;
  int _clusterId;

public:
  Point() = default;
  Point(double x, double y, int pointId, int clusterId = 0):
        _x(x), _y(y), _pointId(pointId), _clusterId(clusterId) {};
  ~Point() {};
  double GetX() const {
    return _x;
  }
  double GetY() const {
    return _y;
  }

  void SetX(double& x) {
    this->_x = x;
  }
  void SetY(double& y) {
    this->_y = y;
  }

  int GetPointId() const {
    return _pointId;
  }
  int GetClusterId() const {
    return _clusterId;
  }

  void SetPointId(int pointId) {
    this->_pointId = pointId;
  }
  void SetClusterId(int clusterId) {
    this->_clusterId = clusterId;
  }
};


class Cluster
{
protected:
  int _clusterId;
  vector<double> _centroid;
  vector<Point> _points;

public:
  Cluster(int clusterId, Point centroid): _clusterId(clusterId) {
    this->_centroid.push_back(centroid.GetX());
    this->_centroid.push_back(centroid.GetY());
    this->SetPoint(centroid);
  };
  ~Cluster() {};
  
  void SetPoint(Point& point) {
    point.SetClusterId(this->_clusterId);
    _points.push_back(point);
  }
  bool RemovePoint(int& pointId) {
    unsigned int size = _points.size();

    for (size_t i = 0; i < size; i++) {
      if (_points[i].GetPointId() == pointId) {
        _points.erase(_points.begin() + pointId);
        return true;
      }
    }
    
    return false;
  }
  void RemoveAllPoints() {
    _points.clear();
  }
  Point GetPoint(int pointId) const {
    return _points[pointId];
  }
  vector<Point> GetPoints() const {
    return _points;
  }

  int GetClusterSize() const {
    return _points.size();
  }
  int GetClusterId() const {
    return _clusterId;
  }
  double GetCentroidX() const {
    return _centroid[0];
  }
  double GetCentroidY() const {
    return _centroid[1];
  }

  void SetCentroidX(double x) {
    this->_centroid[0] = x;
  }
  void SetCentroidY(double y) {
    this->_centroid[1] = y;
  }

  void merge(const Cluster& cluster2) {
        //_points.insert(_points.end(), cluster2._points.begin(), cluster2._points.end());
        for(Point i: cluster2._points) {
          i.SetClusterId(_clusterId);
          _points.push_back(i);
        }
    }
};
