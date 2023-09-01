#pragma once
#include <vector>
#include "matrix.hpp"

template<typename T>
class SOLE {
public:
	SOLE(std::size_t, const Matrix<T>&, const std::vector<T>&);
public:
	std::vector<T> GaussSolve() const;
	std::vector<T> LUSolve() const;
	std::vector<T> CholeskySolve() const;
	std::vector<T> InversedSolve() const;
	std::vector<T> CramerSolve() const;
	std::vector<T> ThomasAlgorithm() const;
public:
	std::vector<T> JacobiIteration(const std::vector<T>&, double) const;
	std::vector<T> GausSeidelIteration(const std::vector<T>&, double) const;
	std::vector<T> UpperRelaxationIteration(const std::vector<T>&, double, const T&) const;
	std::vector<T> SimpleIteration(const std::vector<T>&, double, const T&) const;
private:
	std::size_t n;
	Matrix<T> A;
	std::vector<T> b;
};
#include "sole.cpp"
