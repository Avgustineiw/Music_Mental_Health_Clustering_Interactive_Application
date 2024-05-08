#include <vector>

using namespace std;


class Point
{
protected:
  double _x;
  double _y;

public:
  Point(double x, double y): _x(x), _y(y) {};
  virtual double GetX() const {
    return _x;
  }
  virtual double GetY() const {
    return _y;
  }

  virtual void SetX(double x) {
    this->_x = x;
  }
  virtual void SetY(double y) {
    this->_y = y;
  }
};


class ClusterPoint : public Point
{
private:
  int _pointId;
  int _clusterId;

public: 
  ClusterPoint(double x, double y, int pointId, int clusterId = 0): 
               Point(x, y), _pointId(pointId), _clusterId(clusterId) {};

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
  vector<ClusterPoint> _points;

public:
  Cluster(int clusterId, ClusterPoint centroid): _clusterId(clusterId) {
    this->_centroid.push_back(centroid.GetX());
    this->_centroid.push_back(centroid.GetY());
    this->SetPoint(centroid);
  };
  
  void SetPoint(ClusterPoint point) {
    point.SetClusterId(this->_clusterId);
    _points.push_back(point);
  }
  bool RemovePoint(int pointId) {
    int size = _points.size();

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
  Point GetPoint(int pointId) {
    return _points[pointId];
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
};
