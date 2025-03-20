#include "cubic_regression.hpp"
#include <stdexcept>
#include <cmath>
#include <geometry_msgs/msg/point.hpp>

void CubicRegression::fit(const std::vector<uint64_t> &x, const std::vector<geometry_msgs::msg::Point> &y)
{
    if (x.size() != y.size())
    {
        throw std::invalid_argument("x and y must have the same size");
    }

    size_t n = x.size();

    // Initialize sums for the normal equations
    double sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0, sum_x5 = 0, sum_x6 = 0;
    double sum_y = 0, sum_xy = 0, sum_x2y = 0, sum_x3y = 0;
    double sum_y2 = 0, sum_xy2 = 0, sum_x2y2 = 0, sum_x3y2 = 0;

    for (size_t i = 0; i < n; ++i)
    {
        double xi = x[i];
        double xi2 = xi * xi;
        double xi3 = xi2 * xi;
        double xi4 = xi3 * xi;
        double xi5 = xi4 * xi;
        double xi6 = xi5 * xi;

        sum_x += xi;
        sum_x2 += xi2;
        sum_x3 += xi3;
        sum_x4 += xi4;
        sum_x5 += xi5;
        sum_x6 += xi6;

        sum_y += y[i].x;
        sum_xy += xi * y[i].x;
        sum_x2y += xi2 * y[i].x;
        sum_x3y += xi3 * y[i].x;

        sum_y2 += y[i].y;
        sum_xy2 += xi * y[i].y;
        sum_x2y2 += xi2 * y[i].y;
        sum_x3y2 += xi3 * y[i].y;
    }

    // Construct the normal equations matrix
    double A[4][4] = {
        {static_cast<double>(n), sum_x, sum_x2, sum_x3},
        {sum_x, sum_x2, sum_x3, sum_x4},
        {sum_x2, sum_x3, sum_x4, sum_x5},
        {sum_x3, sum_x4, sum_x5, sum_x6}};

    // Construct the right-hand side vectors
    double Bx[4] = {sum_y, sum_xy, sum_x2y, sum_x3y};
    double By[4] = {sum_y2, sum_xy2, sum_x2y2, sum_x3y2};

    // Solve the system of equations for x coefficients
    solveSystem(A, Bx, ax, bx, cx, dx);

    // Solve the system of equations for y coefficients
    solveSystem(A, By, ay, by, cy, dy);
}

void CubicRegression::solveSystem(double A[4][4], double B[4], double &a, double &b, double &c, double &d)
{
    for (size_t i = 0; i < 4; ++i)
    {
        // Make the diagonal element 1
        double divisor = A[i][i];
        for (size_t j = 0; j < 4; ++j)
        {
            A[i][j] /= divisor;
        }
        B[i] /= divisor;

        // Eliminate the current variable from other equations
        for (size_t k = 0; k < 4; ++k)
        {
            if (k != i)
            {
                double factor = A[k][i];
                for (size_t j = 0; j < 4; ++j)
                {
                    A[k][j] -= factor * A[i][j];
                }
                B[k] -= factor * B[i];
            }
        }
    }

    // Extract the coefficients
    d = B[0];
    c = B[1];
    b = B[2];
    a = B[3];
}

geometry_msgs::msg::Point CubicRegression::predict(uint64_t x) const
{
    double x2 = x * x;
    double x3 = x2 * x;
    geometry_msgs::msg::Point point;
    point.x = ax * x3 + bx * x2 + cx * x + dx;
    point.y = ay * x3 + by * x2 + cy * x + dy;
    point.z = 0.0;
    return point;
}