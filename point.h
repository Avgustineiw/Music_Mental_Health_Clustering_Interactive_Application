class Point
{
protected:
  double _x;
  double _y;

public:
  Point(double x, double y): _x(x), _y(y) {};
  double GetX() const {
    return _x;
  }
  double GetY() const {
    return _y;
  }

  void SetX(double x) {
    this->_x = x;
  }
  void SetY(double y) {
    this->_y = y;
  }
};
