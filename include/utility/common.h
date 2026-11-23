#pragma once
#include <complex>
#include <vector>

int GetTerminalWidth(int fallback = 80);

std::vector<std::complex<double>>              Real2Complex(const std::vector<double>& vec);
std::vector<std::vector<std::complex<double>>> Real2Complex(const std::vector<std::vector<double>>& vec);

std::vector<double>              Complex2Real(const std::vector<std::complex<double>>& complexs);
std::vector<std::vector<double>> Complex2Real(const std::vector<std::vector<std::complex<double>>>& complexs);
