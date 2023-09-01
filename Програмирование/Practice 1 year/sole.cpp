#include <cmath>
#include <unistd.h>

template<typename T>
SOLE<T>::SOLE(std::size_t n, const Matrix<T>& A, const std::vector<T>& b) : n(n), A(A), b(b) {}

template<typename T>
double norm(const std::vector<T>& vec) {
	double sum = 0;
	for (const auto& elem : vec) {
		sum += elem * elem;
	}
	return std::sqrt(sum);
}

template<typename T>
std::vector<T> operator+(const std::vector<T>& left, const std::vector<T>& right) {
	if (left.size() != right.size()) {
		throw std::runtime_error("Invalid size of operands");
	}

	std::vector<T> res(left);
	for (std::size_t i = 0; i < res.size(); i++) {
		res[i] += right[i];
	}
	return res;
}

template<typename T>
std::vector<T> operator-(const std::vector<T>& left, const std::vector<T>& right) {
	if (left.size() != right.size()) {
		throw std::runtime_error("Invalid size of operands");
	}

	std::vector<T> res(left);
	for (std::size_t i = 0; i < res.size(); i++) {
		res[i] -= right[i];
	}
	return res;
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& vec, const T& scalar) {
	std::vector<T> res(vec);
	for (auto& elem : res) {
		elem *= scalar;
	}
	return res;
}

//Methods
template<typename T>
std::vector<T> SOLE<T>::GaussSolve() const{
	Matrix<T> G = A;
	G.appendCol(1);
	for(std::size_t i = 0; i < n; i++){
		G[i][n] = b[i];
	}
	G = G.getGauss_method_upper();
	std::vector<T> x(n);
	for(int i = n - 1; i >= 0; i--){
		T sum {};
		for(std::size_t j = i + 1; j < n; j++){
			sum += G[i][j] * x[j];
		}
		x[i] = (G[i][n] - sum) / G[i][i];
	}
	return x;
}

template<typename T>
std::vector<T> SOLE<T>::LUSolve() const{
	std::pair<Matrix<T>, Matrix<T>> LU = A.getLUDecomposition();
	std::vector<T> y(n);
	for(std::size_t i = 0; i < n; i++){
		T sum {};
		for(std::size_t j = 0; j < n; j++){
			sum += LU.first[i][j] * y[j];
		}
		y[i] = b[i] - sum;
	}
	std::vector<T> x(n);
	for(int i = n - 1; i >= 0; i--){
		T sum {};
		for(std::size_t j = i + 1; j < n; j++){
			sum += LU.second[i][j] * x[j];
		}
		x[i] = (y[i] - sum)/LU.second[i][i];
	}
	return x;
}

template<typename T>
std::vector<T> SOLE<T>::CholeskySolve() const{
	Matrix<T> C1 = A.getCholeskyDecomposition();
	Matrix<T> C2 = C1.getTransposed();
	std::vector<T> y(n);
	for(std::size_t i = 0; i < n; i++){
		T sum {};
		for(std::size_t j = 0; j < n; j++){
			sum += C1[i][j] * y[j];
		}
		y[i] = (b[i] - sum) / C1[i][i];
	}
	std::vector<T> x(n);
	for(int i = n - 1; i >= 0; i--){
		T sum {};
		for(std::size_t j = i + 1; j < n; j++){
			sum += C2[i][j] * x[j];
		}
		x[i] = (y[i] - sum) / C2[i][i];
	}
	return x;
}

template<typename T>
std::vector<T> SOLE<T>::InversedSolve() const{
	std::vector<T> x(n);
	for(std::size_t i = 0; i < n; i++){
		for(std::size_t j = 0; j < n; j++){
			x[i] += A[i][j] * b[j];
		}
	}
	return x;
}

template<typename T>
std::vector<T> SOLE<T>::CramerSolve(){
	if(!A.determinant()) throw std::logic_error("matrix is singular\n");
	T q = A.determinant();
	std::vector<T> x(n);
	for(std::size_t i = 0; i < n; i++){
		Matrix<T> temp = A;
		for(std::size_t j = 0; j < n; j++){
			temp[j][i] = b[j];
		}
		x[i] = temp.determinant() / q;
	}
	return x;
}

template <typename T>
std::vector<T> SOLE<T>::ThomasAlgorithm() const
{
	if (!A.determinant()) {
		throw std::logic_error("matrix is singular\n");
	}
	if (!A[0][0]) {
		throw std::logic_error("vse ploho\n");
	}
	std::vector<T> x(n);
	std::vector<T> alpha(n + 1);
	std::vector<T> beta(n + 1);
	alpha[1] = -A[0][1] / A[0][0];
	beta[1] = b[0] / A[0][0];
	for (std::size_t i = 1; i < n; i++) {
		beta[i+1] = (b[i] - A[i][i - 1] * beta[i]) / (A[i][i - 1] * alpha[i] + A[i][i]);
		alpha[i+1] = -A[i][i + 1] / (A[i][i - 1] * alpha[i] + A[i][i]);
	}
	x[n - 1] = beta[n];
	for (long i = n - 2; i >= 0; i--) {
		x[i] = alpha[i+1]*x[i+1] + beta[i + 1];
	}
	return x;
}

//Iteration methods
template<typename T>
std::vector<T> SOLE<T>::jacobiIteration(const std::vector<T>& x, double eps) const {
	std::vector<T> x(x);
	std::vector<T> xk(x);
	while(1){
		for (int i = 0; i < n; i++) {
			xk[i] = b[i];
			for (int j = 0; j < n; j++) {
				if (i != j)
					xk[i] -= A[i][j] * x[j];
			}
			xk[i] /= A[i][i];
		}
		if(norm(xk - x) < eps)
			break;
		x = xk;
	}
	return x;
}

template <typename T>//предпологается, что матрица с диагональным преобладанием
std::vector<T> SOLE<T> GausSeidelIteration(const std::vector<T>& x, double eps) const{
	std::vector<T> x(x);
	std::vector<T> xk(x);
	while(1){
		for (int i = 0; i < n; i++) {
		xk[i] = b[i];
		for (int j = 0; j < n; j++) {
			if (i < j)
				xk[i] -= A[i][j] * x[j];
			}else
				xk[i] -= A[i][j] * xk[j];
		xk[i] /= A[i][i];
		}		
	if(norm(xk - x) < eps)
		break;
	x = xk;
	}
	return x;
}

template <typename T>
std::vector<T> UpperRelaxationIteration(const std::vector<T>& x0, double eps, const T& tau) const{
	std::vector<T> x(x);
	std::vector<T> xk(x);
	std::vector<T> xnew(x);
	std::vector<T> xknew(x);
	while(1){
	for (int i = 0; i < n; i++) {
		xk[i] = b[i];
		for (int j = 0; j < n; j++) {
			if (i < j)
				xk[i] -= A[i][j] * x[j];
		}else
			xk[i] -= A[i][j] * xk[j];
		xk[i] /= A[i][i];
	}
	xknew = tau*xk + (1-tau)*x;
	if(norm(xknew - xnew) < eps)
		break;
	x = xk;
	xnew = xknew;
	}
	return x;
}

template<typename T>
std::vector<T> SOLE<T>::SimpleIteration(const std::vector<T>& x0, double eps, const T& tau) const {

	std::vector<T> x(x0);
	std::vector<T> xk(x0);
	while(true) {
		xk = x - (A*x - b)*tau;
		sleep(1);
		std::cout << norm(xk - x) << "\n";
		if (norm(xk - x) < eps) {
			break;
		}
		x = xk;
	}
	return x;
}
