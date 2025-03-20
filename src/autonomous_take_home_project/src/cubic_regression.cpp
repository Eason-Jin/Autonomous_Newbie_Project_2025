#include "cubic_regression.hpp"
#include <Eigen/Dense>

void CubicRegression::fit(const std::vector<uint64_t> &time, const std::vector<geometry_msgs::msg::Point> &point) {
    // Ensure the input vectors are of the same size
    if (time.size() != point.size()) {
        throw std::invalid_argument("Time and point vectors must be of the same length");
    }

    // Number of data points
    size_t n = time.size();

    // Construct the Vandermonde matrix
    Eigen::MatrixXd A(n, 4);
    Eigen::VectorXd bx(n), by(n), bz(n);

    for (size_t i = 0; i < n; ++i) {
        double t = static_cast<double>(time[i]);
        A(i, 0) = 1.0;
        A(i, 1) = t;
        A(i, 2) = t * t;
        A(i, 3) = t * t * t;
        bx(i) = point[i].x;
        by(i) = point[i].y;
        bz(i) = point[i].z;
    }

    // Solve for the coefficients using least squares
    Eigen::VectorXd coeffs_x = A.colPivHouseholderQr().solve(bx);
    Eigen::VectorXd coeffs_y = A.colPivHouseholderQr().solve(by);
    Eigen::VectorXd coeffs_z = A.colPivHouseholderQr().solve(bz);

    // Store the coefficients
    a0 = coeffs_x(0);
    a1 = coeffs_x(1);
    a2 = coeffs_x(2);
    a3 = coeffs_x(3);
}

geometry_msgs::msg::Point CubicRegression::predict(uint64_t time) {
    double t = static_cast<double>(time);
    geometry_msgs::msg::Point result;
    result.x = a0 + a1 * t + a2 * t * t + a3 * t * t * t;
    result.y = a0 + a1 * t + a2 * t * t + a3 * t * t * t;
    result.z = a0 + a1 * t + a2 * t * t + a3 * t * t * t;
    return result;
}