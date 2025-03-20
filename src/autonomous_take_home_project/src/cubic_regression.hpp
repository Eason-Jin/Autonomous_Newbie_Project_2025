#ifndef CUBIC_REGRESSION_HPP
#define CUBIC_REGRESSION_HPP

#include <vector>
#include <geometry_msgs/msg/point.hpp>

class CubicRegression
{
public:
    void fit(const std::vector<uint64_t> &x, const std::vector<geometry_msgs::msg::Point> &y);
    geometry_msgs::msg::Point predict(uint64_t x) const;

private:
    void solveSystem(double A[4][4], double B[4], double &a, double &b, double &c, double &d);

    double ax, bx, cx, dx;
    double ay, by, cy, dy;
};

#endif // CUBIC_REGRESSION_HPP