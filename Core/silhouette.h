#include "point.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


double Distance(ClusterPoint p1, ClusterPoint p2)
{
  return sqrt(pow(p1.GetX() - p2.GetX(), 2) + pow(p1.GetY() - p2.GetY(), 2));
}


double Silhouette(vector<Cluster> clusters, vector<ClusterPoint> points)
{
  int size = points.size();
  vector<double> inner_mean, outer_mean;
    
  for (size_t i = 0; i < size; i++) {
    double inner_sum = 0; 
    vector<double> outer_sum(clusters.size(), 0.0);

    for (size_t j = 0; j < size; j++) {
      if (i != j) {
        if (points[i].GetClusterId() == points[j].GetClusterId()) {
          inner_sum += Distance(points[i], points[j]);
          outer_sum[points[j].GetClusterId() - 1] = 1000000; //I'd like to fix it later
        }
        else {
          outer_sum[points[j].GetClusterId() - 1] += Distance(points[i], points[j]);
        }
      }
    }

    inner_sum = inner_sum/(clusters[points[i].GetClusterId() - 1].GetClusterSize() - 1);
    inner_mean.push_back(inner_sum);

    for (size_t j = 0; j < outer_sum.size(); j++) {
      outer_sum[j] = outer_sum[j]/clusters[j].GetClusterSize();
    }

    double min_ele = *min_element(outer_sum.begin(), outer_sum.end());
    outer_mean.push_back(min_ele);
  }

  double sil = 0;

  for (size_t i = 0; i < size; i++) {
    sil += (outer_mean[i] - inner_mean[i])/max(inner_mean[i], outer_mean[i]);
  }

  sil = sil/size;

  return sil;
}
