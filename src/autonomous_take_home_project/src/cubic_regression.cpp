#include "cubic_regression.hpp"
#include <eigen3/Eigen/Dense>

void CubicRegression::fit(const std::vector<uint64_t> &time, const std::vector<double> &value)
{
    // Ensure the input vectors are of the same size
    if (time.size() != value.size())
    {
        throw std::invalid_argument("Time and value vectors must be of the same length");
    }

    // Number of data points
    size_t n = time.size();

    // Construct the Vandermonde matrix
    Eigen::MatrixXd A(n, 4);
    Eigen::VectorXd b(n);

    for (size_t i = 0; i < n; ++i)
    {
        double t = static_cast<double>(time[i]);
        A(i, 0) = 1.0;
        A(i, 1) = t;
        A(i, 2) = t * t;
        A(i, 3) = t * t * t;
        b(i) = value[i];
    }

    // Solve for the coefficients using least squares
    Eigen::VectorXd coeffs_x = A.colPivHouseholderQr().solve(b);

    // Store the coefficients
    a0 = coeffs_x(0);
    a1 = coeffs_x(1);
    a2 = coeffs_x(2);
    a3 = coeffs_x(3);
}

double CubicRegression::predict(uint64_t time)
{
    double t = static_cast<double>(time);
    return a0 + a1 * t + a2 * t * t + a3 * t * t * t;
}