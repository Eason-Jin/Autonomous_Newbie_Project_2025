#ifndef CUBIC_REGRESSION_HPP
#define CUBIC_REGRESSION_HPP

#include <vector>
#include <cstdint>

class CubicRegression {
public:
    void fit(const std::vector<uint64_t>& x, const std::vector<double>& y);
    double predict(uint64_t x) const;

private:
    double a = 0; // Coefficient for x^3
    double b = 0; // Coefficient for x^2
    double c = 0; // Coefficient for x
    double d = 0; // Constant term
};

#endif