// compile:
// g++ -std=c++11 -static -O2 -o feladat feladat.cpp


#include<iostream>
using namespace std;

/**
 * Az osztálysablon neve my_matrix.
 * A sablon paraméterezése:
 *   - T: a mátrix alaptípusa
 *   - N: a mátrix sorainak száma
 *   - M: a mátrix oszlopainak száma
 * A sablonpéldány a matrix_base osztályból származik (amely rendelkezik
 * default konstruktorral). A beadott feladatban a matrix_base osztályt nem
 * kell (nem szabad) megvalósítani!
 */
class matrix_base{};

template<class T, int N, int M, class Left, class Right>
class MatrixSum;

template<class T, int N, int M, class Left, class Right>
class MatrixSub;

template<class T, int N, int M, class Left, class Right>
class MatrixProd;

template<class T, int N, int M, class Mtx>
class MatrixScalarProd;

template<class T, int N, int M>
class my_matrix : matrix_base {
public:
    /** A sablonpéldány rendelkezik default konstruktorral. */
    T data[N][M];
    my_matrix(){}
    /**
     * A mátrix elemeihez való hozzáférést a kétparaméteres függvényhívás
     * operátor felüldefiniálása biztosítja.
     */
    const T& operator()(int n, int m) const{
      return data[n][m];
    }
    T& operator()(const int &n, const int &m){
      return data[n][m];
    }

    template<class Left, class Right>
    my_matrix<T,N,M>& operator=(const MatrixSum<T,N,M,Left,Right>& v) {
      for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
          data[i][j] = v(i,j);
        }
      }
      return *this;
    }

    template<class Left, class Right>
    my_matrix<T,N,M>& operator=(const MatrixSub<T,N,M,Left,Right>& v) {
      for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
          data[i][j] = v(i,j);
        }
      }
      return *this;
    }

    template<class Left, class Right>
    my_matrix<T,N,M>& operator=(const MatrixProd<T,N,M,Left,Right>& v) {
      for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
          data[i][j] = v(i,j);
        }
      }
      return *this;
    }

    template<class Mtx>
    my_matrix<T,N,M>& operator=(const MatrixScalarProd<T,N,M,Mtx>& v) {
      for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
          data[i][j] = v(i,j);
        }
      }
      return *this;
    }

};


// template class for the matrix sum
template<class T, int N, int M, class Left, class Right>
class MatrixSum{
  const Left &left;
  const Right &right;
public:
  MatrixSum(const Left &l, const Right &r) : left(l), right(r) {}
  // operator[], amely visszaadja a bal es jobb operandus i-dik pozícióján levõ elem összeget
  T operator()(int i, int j) const { return left(i,j) + right(i,j); }
};


// case: mtx1 + mtx2
template<class T, int N, int M>
inline auto operator+(const my_matrix<T,N,M> &l, const my_matrix<T,N,M> &r) {
  return MatrixSum<T, N, M, my_matrix<T,N,M>, my_matrix<T,N,M> >(l,r);
}

// case: mtx1 + mtx2 + mtx3 (MatrixSum exists)
template<class T, int N, int M, class Left, class Right>
inline auto operator+(const MatrixSum<T,N,M,Left,Right> &l, const my_matrix<T,N,M> &r) {
  return MatrixSum<T, N, M, MatrixSum<T,N,M,Left,Right>, my_matrix<T,N,M> >(l,r);
}

// case: mtx1 + (mtx2 + mtx3)
template<class T, int N, int M, class Left, class Right>
inline auto operator+(const my_matrix<T,N,M> &l, const MatrixSum<T,N,M,Left,Right> &r) {
  return MatrixSum<T, N, M, my_matrix<T,N,M>, MatrixSum<T,N,M,Left,Right> >(l,r);
}








// template class for the matrix substract
template<class T, int N, int M, class Left, class Right>
class MatrixSub{
  const Left &left;
  const Right &right;
public:
  MatrixSub(const Left &l, const Right &r) : left(l), right(r) {}
  // operator[], amely visszaadja a bal es jobb operandus i-dik pozícióján levõ elem összeget
  T operator()(int i, int j) const { return left(i,j) - right(i,j); }
};


// case: mtx1 + mtx2
template<class T, int N, int M>
inline auto operator-(const my_matrix<T,N,M> &l, const my_matrix<T,N,M> &r) {
  return MatrixSub<T, N, M, my_matrix<T,N,M>, my_matrix<T,N,M> >(l,r);
}

// case: mtx1 + mtx2 + mtx3 (MatrixSub exists)
template<class T, int N, int M, class Left, class Right>
inline auto operator-(const MatrixSub<T,N,M,Left,Right> &l, const my_matrix<T,N,M> &r) {
  return MatrixSub<T, N, M, MatrixSub<T,N,M,Left,Right>, my_matrix<T,N,M> >(l,r);
}

// case: mtx1 + (mtx2 + mtx3)
template<class T, int N, int M, class Left, class Right>
inline auto operator-(const my_matrix<T,N,M> &l, const MatrixSub<T,N,M,Left,Right> &r) {
  return MatrixSub<T, N, M, my_matrix<T,N,M>, MatrixSub<T,N,M,Left,Right> >(l,r);
}













// template class for the matrix product
template<class T, int N, int M, class Left, class Right>
class MatrixProd{
  const Left &left;
  const Right &right;
public:
  MatrixProd(const Left &l, const Right &r) : left(l), right(r) {}
  // operator[], amely visszaadja a bal es jobb operandus i-dik pozícióján levõ elem összeget
  T operator()(int x, int y) const {
    int sum = 0;

    for (int i=0; i<M; i++){
      sum += left(x,i) * right(i,y);
    }

    return sum;
  }
};


// case: mtx1 * mtx2
template<class T, int N, int M, int K>
inline auto operator*(const my_matrix<T,N,M> &l, const my_matrix<T,M,K> &r) {
  return MatrixProd<T, N, K, my_matrix<T,N,M>, my_matrix<T,M,K> >(l,r);
}

template<class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const MatrixProd<T,N,M,Left,Right> &l, const my_matrix<T,M,K> &r) {
  return MatrixProd<T, N, K, MatrixProd<T,N,M,Left,Right>, my_matrix<T,M,K> >(l,r);
}

template<class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const my_matrix<T,N,M> &l, const MatrixProd<T,M,K,Left,Right> &r) {
  return MatrixProd<T, N, K, my_matrix<T,N,M>, MatrixProd<T,M,K,Left,Right> >(l,r);
}












 template<class T, int N, int M, class Mtx>
 class MatrixScalarProd{
   const Mtx &mtx;
   const T &scalar;
 public:
   MatrixScalarProd(const Mtx &m, const T &s) : mtx(m), scalar(s) {}

   T operator()(int i, int j) const { return scalar * mtx(i,j); }
 };

 template<class T, int N, int M>
 inline auto operator*(const my_matrix<T,N,M> &m, const T &s) {
   return MatrixScalarProd<T, N, M, my_matrix<T,N,M> >(m,s);
 }

 template<class T, int N, int M>
 inline auto operator*(const T &s, const my_matrix<T,N,M> &m) {
   return MatrixScalarProd<T, N, M, my_matrix<T,N,M> >(m,s);
 }

 template<class T, int N, int M, class Mtx>
 inline auto operator*(const MatrixScalarProd<T,N,M,Mtx> &m, const T &s) {
   return MatrixScalarProd<T, N, M, MatrixScalarProd<T,N,M,Mtx> >(m,s);
 }

 template<class T, int N, int M, class Mtx>
 inline auto operator*(const T &s, const MatrixScalarProd<T,N,M,Mtx> &m) {
   return MatrixScalarProd<T, N, M, MatrixScalarProd<T,N,M,Mtx> >(m,s);
 }







int main() {
    my_matrix<int,2,2> mtx1;
    my_matrix<int,2,2> mtx2;

    my_matrix<int,2,2> mtx3;
    my_matrix<int,2,3> mtx4;
    mtx1(1,1) = 55;
    mtx2(1,1) = 11;

    mtx3 = mtx1 - mtx2 - mtx1 - mtx2;
    cout << "mtx3: " << mtx3(1,1) << endl;

    mtx3 = 5 * mtx3;
    cout << "mtx3: " << mtx3(1,1) << endl;

    mtx3 = mtx1 * mtx2;
    cout << "mtx3: " << mtx3(1,1) << endl;


    return 0;
}
