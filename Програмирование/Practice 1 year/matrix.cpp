#include <cstdlib>
#include <cmath>

//bool
template<typename T>
bool Matrix<T>::isSquare() const{
	return m != n ? false : true;
}

template<typename T>
bool Matrix<T>::isSymmetric() const{
	if(m != n) throw std::logic_error("Invalid matrix size\n");
	for(std::size_t i = 0; i < n; i++){
		for(std::size_t j = 0; j < n; j++){
			if(i == j) continue;
			if(data[i][j] != data[j][i]) return false;
		}
	}
	return true;
}

template<typename T>
bool Matrix<T>::isUpperTriangular() const{
	if(m != n) throw std::logic_error("Invalid matrix size\n");
	for(std::size_t i = 0; i < n; i++){
		for(std::size_t j = i + 1; j < n; j++){
			if(data[j][i] != 0) return false;
		}
	}
	return true;
}

template<typename T>
bool Matrix<T>::isLowerTriangular() const{
	if(m != n) throw std::logic_error("Invalid matrix size\n");
	for(std::size_t i = 0; i < n; i++){
		for(std::size_t j = i + 1; j < n; j++){
			if(data[i][j] != 0) return false;
		}
	}
	return true;
}

template<typename T>
bool Matrix<T>::isDiagonal() const{
	if(m != n) throw std::logic_error("Invalid matrix size\n");
	for(std::size_t i = 0; i < n; i++){
		for(std::size_t j = i + 1; j < n; j++){
			if(data[i][j] != 0 || data[j][i] != 0) return false;
		}
	}
	return true;
}

template<typename T>
bool Matrix<T>::isOrthognal() const{
 if(m != n) throw std::logic_error("Invalid matrix size\n");
 Matrix<T> first(*this);
 Matrix<T> second = first.getTransposed();
 first = first.getInversedMatrix();
 if(first == second) return true;
 return false;
}

template<typename T>
T Matrix<T>::getNorm() const{
	T q = 0;
	for(std::size_t i = 0; i < n; i++){
		for(std::size_t j = 0; j < n; j++){
			q += data[i][j] * data[i][j];
		}
	}
	return sqrt(q);
}

template<typename T>
T Matrix<T>::getTrace() const{
	if (m != n) throw std::logic_error("Invalid matrix size\n");
	T trace = data[0][0];
	for(std::size_t i = 1; i < n; i++){
		trace += data[i][i];
	}
	return trace;
}

template<typename T>
T Matrix<T>::getDet() const{
	if (m != n) throw std::logic_error("Invalid matrix size\n");
	Matrix<T> temp(*this);
	temp = temp.getGauss_method_upper();
	T res = temp.data[0][0];
	for(std::size_t i = 1; i < m; i++){
		res *= temp.data[i][i];
	}
	return res;
}

//static methods
template<typename T>
Matrix<T> Matrix<T>::IdentityMatrix(std::size_t n) {
	T a = 0;
	Matrix<T> res(n, n, a);
	for (std::size_t i = 0; i < n; i++) {
		res.data[i][i] = 1;
	}
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::RotationMatrix(std::size_t n, std::size_t i, std::size_t j, const T& phi) {
	Matrix<T> res = IdentityMatrix(n);
	res.data[i][i] = std::cos(phi);
	res.data[i][j] = -std::sin(phi);
	res.data[j][i] = std::sin(phi);
	res.data[j][j] = std::cos(phi);
	return res;
}

// Constructors

template<typename T>
Matrix<T>::Matrix(std::size_t m, std::size_t n, T** data) : m(m), n(n) {
	this->data = std::vector<std::vector<T>>(m);
	for(std::size_t i = 0; i < m; i++){
		this->data[i] = std::vector<T>(n);
		if(data != nullptr){
			for(std::size_t j = 0; j < n; j++){
				this->data[i][j] = data[i][j];
			}
		}
	}
}

template<typename T>
Matrix<T>::Matrix() : m(0), n(0) {}

template<typename T>
Matrix<T>::Matrix(std::size_t m, std::size_t n, const T& value) : m(m), n(n) {
	data = std::vector<std::vector<T>>(m);
	for (std::size_t i{}; i < m; i++) {
		data[i] = std::vector<T>(n, value);
	}
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& other) {
	m = other.size();
	data = std::vector<std::vector<T>>();
	for (const auto& row : other) {
		data.push_back(row);
	}
	n = data[0].size();
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : m(other.m), n(other.n), data(other.data) {}

// Assignment

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
	m = other.m;
	n = other.n;
	data = other.data;
	return *this;
}

// Get size

template<typename T>
std::vector<T> Matrix<T>::getRow(std::size_t i) const{
	return data[i];
}

template<typename T>
std::vector<T> Matrix<T>::getCol(std::size_t i) const{
	std::vector<T> x(m);
	for(std::size_t j = 0; j < m; j++){
		x[j] = data[j][i];
	}
	return x;
}

template<typename T>
std::size_t Matrix<T>::rowsCount() const {
	return m;
}

template<typename T>
std::size_t Matrix<T>::colsCount() const {
	return n;
}

// Element Access

template<typename T>
std::vector<T>& Matrix<T>::operator[](std::size_t pos) {
	return data[pos];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](std::size_t pos) const {
	return data[pos];
}


// Matrix transformations

template<typename T>
Matrix<T> Matrix<T>::getInversedMatrix() const{
	Matrix temp(*this);
	temp.appendMatrixToRight(IdentityMatrix(m));
	for(std::size_t i = 0; i < temp.m; i++){
		T q = temp.data[i][i];
		for(std::size_t j = i; j < temp.n; j++){
			temp.data[i][j] /= q;
		}
		for(std::size_t j = i + 1; j < temp.m; j++){
			if(!temp.data[j][i]) continue;
			q = temp.data[j][i] / temp.data[i][i];
			for(std::size_t k = i; k < temp.n; k++){
				temp.data[j][k] -= temp.data[i][k] * q;
			}
		}
	}
	for(int i = temp.m - 1; i >= 0; i--){
		for(int j = i - 1; j >= 0; j--){
			T q = temp.data[j][i] / temp.data[i][i];
			for(int k = i; k < temp.n; k++){
				temp.data[j][k] -= temp.data[i][k] * q;
			}
		}
	}
	Matrix res(this->m, this->n, 1);
	for(std::size_t i = 0; i < res.m; i++){
		for(std::size_t j = 0; j < res.n; j++){
			res.data[i][j] = temp.data[i][j + n];
		}
	}
	return res;
}

template<typename T>
void Matrix<T>::appendMatrixToRight(const Matrix<T>& right){
	for(std::size_t i = 0; i < m; i++){
		for(std::size_t j = 0; j < right.n; j++){
			data[i].push_back(right.data[i][j]);
		}
	}
	n += right.n;
}

template<typename T>
void Matrix<T>::appendRow(const std::vector<T>& a){
	data.push_back(a);
	m++;
}

template<typename T>
void Matrix<T>::appendCol(std::size_t i){
	T q = 0.0;
	for(std::size_t k = 0; k < i; k++){
		for(std::size_t j = 0; j < m; j++){
			data[j].push_back(q);
		}
	}
	this -> n += i;
}

template<typename T>
Matrix<T> Matrix<T>::getTransposed() const {
	Matrix res(n, m, 1);
	for (std::size_t i = 0; i < m; i++) {
		for (std::size_t j = 0; j < n; j++) {
			res.data[j][i] = data[i][j];
		}
	}
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::getGauss_method_lower(){
	Matrix temp(*this);
	for(std::size_t i = 0; i < m; i++){
		T pivot = temp.data[i][i];
		std::size_t max_pos = i + 1;
		if(!pivot){
			T max {};
			for(std::size_t j = i + 1; j < n; j++){
				if(abs(temp.data[i][j]) > max){
					max = temp.data[i][j];
					max_pos = j;
				}
				pivot = max;
				swapCols(i, max_pos);
			}
		}
		for(std::size_t j = i + 1; j < n; j++){
			if(!temp.data[j][i]) continue;
			T q = temp.data[i][j] / temp.data[i][i];
			for(std::size_t k = i; k < n; k++){
				temp.data[k][j] -= temp.data[k][i] * q;
			}
		}
	}
	return temp;
}

template<typename T>
void Matrix<T>::swapCols(std::size_t i, std::size_t j){
	for(std::size_t k = 0; k < m; k++){
		T temp = data[k][i];
		data[k][i] = data[k][j];
		data[k][j] = temp;
	}
}

template<typename T>
Matrix<T> Matrix<T>::getGauss_method_upper(){
	Matrix temp(*this);
	for(std::size_t i = 0; i < m; i++){
		T pivot = temp.data[i][i];
		if(!pivot){
			T max {};
			std::size_t max_pos = i + 1;
			for(std::size_t j = i + 1; j < m; j++){
				if(abs(temp.data[j][i]) > max){
					max = temp.data[j][i];
					max_pos = j;
				}
				pivot = max;
				swapRows(i, max_pos);
			}
		}
		for(std::size_t j = i + 1; j < m; j++){
			if(!temp.data[j][i]) continue;
			T q = temp.data[j][i] / temp.data[i][i];
			for(std::size_t k = i; k < n; k++){
				temp.data[j][k] -= temp.data[i][k] * q;
			}
		}
	}
	return temp;
}

template<typename T>
void Matrix<T>::swapRows(std::size_t i, std::size_t j){
	std::vector<T> temp(data[i]);
	data[i] = data[j];
	data[j] = temp;
}
//Matrix decompositions

template<typename T>
Matrix<T> Matrix<T>::getCholeskyDecomposition() const{
	for(std::size_t i = 0; i < n; i++){
        T sum_1 = 0;
        for(std:size_t k = 0; k < i ; k++)
            sum_1 += data[i][k] * data[i][k];
        data[i][i] = sqrt(data[i][i] - sum_1);
        for(std::size_t j = i + 1; j < n; j++){
            T sum_2 = 0;
            for(std::size_t k = 0; k < i-1; k++){
                sum_2 = data[j][k] * data[i][k];
            }
            data[i][j] = (data[i][j] - sum_2)/data[i][i];
        }
    }
    return *this;
}

template<typename T>
std::pair<Matrix<T>, Matrix<T>> Matrix<T>::getLUDecomposition() const{
	T a = 0;
	Matrix<T> U(m, n, a);
	Matrix<T> L(m, n, a);
	for(std::size_t i = 0; i < n; i++){
		T result = 0;
		for(std::size_t j = 0; j < i ; j++){
			result += L.data[i][j] * U.data[j][i];
		}
		U.data[i][i] = data[i][i] - result;
		L.data[i][i] = 1;
		for(std::size_t j = i + 1; j < n; j++){
			T result1 {}, result2 {};
			for(std::size_t k = 0; k < j - 1; k++){
				result1 += L.data[i][k] * U.data[k][j];
			}
			U.data[i][j] = data[i][j] - result1;
			for(std::size_t k = 0; k < i; k++){
				result2 += L.data[j][k] * U.data[k][i];
			}
			L.data[j][i] = (data[j][i] - result2)/U.data[i][i];
		}
	}
	return std::make_pair(L, U);
}

template<typename T>
std::pair<Matrix<T>, Matrix<T>> Matrix<T>::getQRDecomposition() const {
	Matrix R(*this);
	Matrix Q = IdentityMatrix(n);
	std::cout << *this << "\n";
	for (std::size_t j = 0; j < n - 1; j++) {
		for (std::size_t i = j + 1; i < n; i++) {
			Matrix V = RotationMatrix(n, i, j, std::atan2(R.data[i][j], R.data[j][j]));
			R = V * R;
			Q = V * Q;
		}
	}
	Q = Q.getTransposed();
	std::cout << Q << "\n" << R << "\n";
	std::cout << Q * R << "\n";
	return std::make_pair(R, R);
}

//Matrix operations
template<typename T>
Matrix<T>& operator+=(const Matrix<T>& B){
	for(std::size_t i = 0; i < B.m; i++){
		for(std::size_t j = 0; j B.n; j++){
			A[i][j] += B[i][j];
		}
	}
	return A;
}

template<typename T>
Matrix<T>& operator-=(const Matrix<T>& B){
	for(std::size_t i = 0; i < B.m; i++){
		for(std::size_t j = 0; j B.n; j++){
			A[i][j] -= B[i][j];
		}
	}
	return A;
}

template<typename T>
Matrix<T>& operator*=(const Matrix<T>& B){
	T a = 0;
	Matrix<T> res(n, B.m, a);
	for (std::size_t i = 0; i < m; i++) {
		for (std::size_t j = 0; j < B.n; j++) {
			for (std::size_t k = 0; k < n; k++) {
				res.data[i][j] += data[i][k] * B.data[k][j];
			}
		}
	}
	return res;
}
	
template<typename T>
Matrix<T>& operator*=(const T& alpha){
	for(std::size_t i = 0; i < m; i++){
		for(std::size_t j = 0; j < n; j++){
			data[i][j] *= alpha;
		}
	}
	return *this;
}

template<typename T>
Matrix<T>& operator/=(const T& B){
	for(std::size_t i = 0; i < m; i++){
		for(std::size_t j = 0; j < n; j++){
			data[i][j] /= alpha;
		}
	}
	return *this;
}

template<typename T>
bool operator == (const Matrix<T>& left, const Matrix<T>& right){
	for(std::size_t i = 0; i < left.m; i++){
		for(std::size_t j = 0; j < left.n; j++){
			if(left.data[i][j] != right.data[i][j])
				return false;
		}
	}
	return true;
}

template<typename T>
bool operator != (const Matrix<T>& left, const Matrix<T>& right){
	for(std::size_t i = 0; i < left.m; i++){
		for(std::size_t j = 0; j < left.n; j++){
			if(left.data[i][j] != right.data[i][j])
				return true;
		}
	}
	return false;
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B){
	if (A.n != B.n || A.m != B.m){
		throw std::logic_error("Invlid size of operands");
	}
	T arr = 0;
	Matrix<T> temp(A.m, A.n, arr);
	for (std::size_t i = 0; i < A.m; i++) {
		for (std::size_t j = 0; j < A.n; j++) {
			temp[i][j] = A[i][j] + B[i][j];
		}
	}
	return temp;

template<typename T>
Matrix<T> operator-(const Matrix<T>& A, const Matrix<V>& B){
	if (A.n != B.n || A.m != B.m){
		throw std::logic_error("Invlid size of operands");
	}
	T arr = 0;
	Matrix<T> temp(A.m, A.n, arr)
	for (std::size_t i = 0; i < A.m; i++) {
		for (std::size_t j = 0; j < A.n; j++) {
			temp[i][j] = A[i][j] - B[i][j];
		}
	}
	return temp;
	
template<typename T>
Matrix<T> operator*(const Matrix<T>& left, const Matrix<T>& right) {
	if (left.n != right.m) {
		throw std::runtime_error("Invlid size of operands");
	}
	T a = 0;
	Matrix<T> res(left.n, right.m, a);
	for (std::size_t i = 0; i < left.m; i++) {
		for (std::size_t j = 0; j < right.n; j++) {
			for (std::size_t k = 0; k < left.n; k++) {
				res.data[i][j] += left.data[i][k] * right.data[k][j];
			}
		}
	}
	return res;
}

template<typename T>
std::vector<T> operator*(const Matrix<T>& mat, const std::vector<T>& vec) {
	if (mat.n != vec.size()) {
		throw std::runtime_error("Invalid size of operands");
	}

	std::vector<T> res(mat.m);

	for (std::size_t i = 0; i < mat.m; i++) {
		for (std::size_t j = 0; j < mat.n; j++) {
			res[i] += mat.data[i][j] * vec[j];
		}
	}
	return res;
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& vec, const Matrix<T>& mat) {
	if (mat.m != vec.size()) {
		throw std::runtime_error("Invalid size of operands");
	}

	std::vector<T> res(mat.n);

	for (std::size_t j = 0; j < mat.n; j++) {
		for (std::size_t i = 0; i < mat.m; i++) {
			res[j] += vec[i] * mat.data[i][j];
		}
	}
	return res;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& mat, const T& value){
	T a = 0;
	Matrix<T> res(mat.m, mat.n, a);
	for(std::size_t i = 0; i < mat.m; i++){
		for(std::size_t j = 0; j < mat.n; j++){
			res.data[i][j] = mat.data[i][j] * value;
		}
	}
	return res;
}

template<typename T>
Matrix<T> operator*(const T& value, const Matrix<T>& mat){
	T a = 0;
	Matrix<T> res(mat.m, mat.n, a);
	for(std::size_t i = 0; i < mat.m; i++){
		for(std::size_t j = 0; j < mat.n; j++){
			res.data[i][j] = mat.data[i][j] * value;
		}
	}
	return res;
}

template<typename T>
Matrix<T> operator/(const Matrix<T>& mat, const T& value){
	T a = 0;
	Matrix<T> res(mat.m, mat.n, a);
	for(std::size_t i = 0; i < mat.m; i++){
		for(std::size_t j = 0; j < mat.n; j++){
			res.data[i][j] = mat.data[i][j] / value;
		}
	}
	return res;
}
// In/Out operators

template<typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& self) {
	for (auto& row : self.data) {
		for (auto& elem : row) {
			in >> elem;
		}
	}
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& self) {
	for (const auto& row : self.data) {
		for (const auto& elem : row) {
			out << elem << " ";
		}
		out << std::endl;
	}
	return out;
}

