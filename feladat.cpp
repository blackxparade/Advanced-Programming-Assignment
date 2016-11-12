// compile:
// g++ -std=c++11 -static -O2 -o feladat feladat.cpp


#include<iostream>
using namespace std;

/**
 * Az oszt�lysablon neve my_matrix.
 * A sablon param�terez�se:
 *   - T: a m�trix alapt�pusa
 *   - N: a m�trix sorainak sz�ma
 *   - M: a m�trix oszlopainak sz�ma
 * A sablonp�ld�ny a matrix_base oszt�lyb�l sz�rmazik (amely rendelkezik
 * default konstruktorral). A beadott feladatban a matrix_base oszt�lyt nem
 * kell (nem szabad) megval�s�tani!
 */
class matrix_base{};

template<class T, int N, int M, class Left, class Right>
class MatrixSum;

template<class T, int N, int M, class Left, class Right>
class MatrixSub;

template<class T, int N, int M, class Left, class Right>
class MatrixProd;

template<class T, int N, int M>
class my_matrix : matrix_base {
public:
    /** A sablonp�ld�ny rendelkezik default konstruktorral. */
    T data[N][M];
    my_matrix(){
      cout << "N: " << N << ", M: " << M << endl;
    }
    /**
     * A m�trix elemeihez val� hozz�f�r�st a k�tparam�teres f�ggv�nyh�v�s
     * oper�tor fel�ldefini�l�sa biztos�tja.
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

};


// template class for the matrix sum
template<class T, int N, int M, class Left, class Right>
class MatrixSum{
  const Left &left;
  const Right &right;
public:
  MatrixSum(const Left &l, const Right &r) : left(l), right(r) {}
  // operator[], amely visszaadja a bal es jobb operandus i-dik poz�ci�j�n lev� elem �sszeget
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
  // operator[], amely visszaadja a bal es jobb operandus i-dik poz�ci�j�n lev� elem �sszeget
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
  // operator[], amely visszaadja a bal es jobb operandus i-dik poz�ci�j�n lev� elem �sszeget
  T operator()(int i, int j) const { return left(i,j) * right(i,j); }
};


// case: mtx1 + mtx2
template<class T, int N, int M>
inline auto operator*(const my_matrix<T,N,M> &l, const my_matrix<T,N,M> &r) {
  return MatrixProd<T, N, M, my_matrix<T,N,M>, my_matrix<T,N,M> >(l,r);
}

// case: mtx1 + mtx2 + mtx3 (MatrixProd exists)
template<class T, int N, int M, class Left, class Right>
inline auto operator*(const MatrixProd<T,N,M,Left,Right> &l, const my_matrix<T,N,M> &r) {
  return MatrixProd<T, N, M, MatrixProd<T,N,M,Left,Right>, my_matrix<T,N,M> >(l,r);
}

// case: mtx1 + (mtx2 + mtx3)
template<class T, int N, int M, class Left, class Right>
inline auto operator*(const my_matrix<T,N,M> &l, const MatrixProd<T,N,M,Left,Right> &r) {
  return MatrixProd<T, N, M, my_matrix<T,N,M>, MatrixProd<T,N,M,Left,Right> >(l,r);
}


/**
 * P�lda a m�trix sablon egy felhaszn�l�s�ra. A beadott feladatban nem szabad
 * szerepelnie.
 */

int main() {
    my_matrix<int,2,2> mtx1;
    my_matrix<int,2,2> mtx2;

    my_matrix<int,2,2> mtx3;
    mtx1(1,1) = 55;
    mtx2(1,1) = 11;
    mtx3 = mtx1 - mtx2 - mtx1 - mtx2;
    cout << "mtx3: " << mtx3(1,1) << endl;


    return 0;
}