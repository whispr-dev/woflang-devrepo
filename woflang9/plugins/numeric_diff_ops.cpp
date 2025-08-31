// plugins/numeric_diff_ops.cpp
#include <iostream>
#include <vector>
#include <cmath>

namespace woflang {

double forward(const std::vector<double>& x,const std::vector<double>& y,int i){
    double h=x[i+1]-x[i]; return (y[i+1]-y[i])/h;
}
double backward(const std::vector<double>& x,const std::vector<double>& y,int i){
    double h=x[i]-x[i-1]; return (y[i]-y[i-1])/h;
}
double central(const std::vector<double>& x,const std::vector<double>& y,int i){
    double h=x[i+1]-x[i-1]; return (y[i+1]-y[i-1])/h;
}

} // namespace woflang
