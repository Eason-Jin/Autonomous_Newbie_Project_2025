#ifndef CUBIC_REGRESSION_HPP
#define CUBIC_REGRESSION_HPP

#include <vector>
#include <geometry_msgs/msg/point.hpp>

class CubicRegression {
public:
    void fit(const std::vector<uint64_t> &time, const std::vector<double> &value);
    double predict(uint64_t time);

private:
    // Coefficients for the cubic polynomial
    double a0, a1, a2, a3;
};

#endif