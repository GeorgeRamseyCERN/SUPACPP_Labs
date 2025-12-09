// A setof classes for fucntions hwich inherit from the FiniteFunctions class
// GR 14/11/25


#pragma once
#include "FiniteFunctions.h"
#include <cmath>
#include <iostream>

// Normal Distribution
class NormalFunction : public FiniteFunction {
public:
    NormalFunction(double mu=0.0, double sigma=1.0)
        : m_mu(mu), m_sigma(sigma) {}

    double callFunction(double x) override {
        double coeff = 1.0 / (m_sigma * std::sqrt(2*M_PI));
        double expterm = std::exp(-0.5 * std::pow((x - m_mu)/m_sigma,2));
        return coeff * expterm;
    }

    void printInfo() override {
        printf("Normal Distribution: mu = %f, sigma= %f\n", m_mu, m_sigma);
        printf("Range: %f to %f\n", m_RMin, m_RMax);
        printf("Integral: %f\n", integral(1000));
    }

private:
    double m_mu;
    double m_sigma;
};

// Cauchy-Lorentz Distribution
class CauchyFunction : public FiniteFunction {
public:
    CauchyFunction(double x0=0.0, double gamma=1.0)
        : m_x0(x0), m_gamma(gamma) {}

    double callFunction(double x) override {
        return 1.0 / (M_PI * m_gamma * (1.0 + std::pow((x - m_x0)/m_gamma,2)));
    }

    void printInfo() override {
        printf("Cauchy-Lorentz: x0=%f, gamma=%f\n", m_x0, m_gamma);
        printf("Range: %f to %f\n", m_RMin,m_RMax);
        printf("Integral: %f \n",integral(1000));
    }

private:
    double m_x0;
    double m_gamma;
};

// Crystal Ball Distribution
class CrystalBallFunction : public FiniteFunction {
public:
    CrystalBallFunction(double alpha=1.5, double n=2.0, double mu=0.0, double sigma=1.0)
        : m_alpha(alpha), m_n(n), m_mu(mu), m_sigma(sigma) {}

    double callFunction(double x) override {
        double z = (x - m_mu)/m_sigma;
        double A = std::pow(m_n/abs(m_alpha), m_n) * std::exp(-0.5*std::pow(m_alpha,2));
        double B = m_n/abs(m_alpha) - abs(m_alpha);
        if (z > -m_alpha)
            return std::exp(-0.5*z*z);
        else
            return A * std::pow(B - z, -m_n);
    }

    void printInfo() override {
        printf("Crystal Ball: alpha= %f, n= %f,  mu= %f, sigma= %f\n", m_alpha, m_n, m_mu, m_sigma);
        printf( "Range: %f to %f \n", m_RMin, m_RMax);
        printf("Integral: %f \n", integral(1000));
    }

private:
    double m_alpha;
    double m_n;
    double m_mu;
    double m_sigma;
};


