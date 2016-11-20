/**
 * @file   feladat.cpp
 * @date   November, 2016
 * @brief  Fejlett Programozas kotelezo program.
 *
 * @section DESCRIPTION
 * A feladat olyan osztalysablon irasa, amely ketdimenzios, dimenzionkent
 * tetszoleges meretu (NxM-es) matrixot reprezental. Az osztaly sablonparameterei
 * hatarozzák meg a matrix alaptipusat es mereteit. A matrix elemeihez valo
 * hozzaferest (indexelest) biztositani kell.
*/


// compile:
// g++ -std=c++11 -static -O2 -o feladat feladat.cpp

/*
#include<iostream>
#include <stdlib.h>
using namespace std;


 * Az osztálysablon neve my_matrix.
 * A sablon paraméterezése:
 *   - T: a mátrix alaptípusa
 *   - N: a mátrix sorainak száma
 *   - M: a mátrix oszlopainak száma
 * A sablonpéldány a matrix_base osztályból származik (amely rendelkezik
 * default konstruktorral). A beadott feladatban a matrix_base osztályt nem
 * kell (nem szabad) megvalósítani!
 */

//class matrix_base{};
/**
*  @brief Segedosztaly.
*/
template<class T, int N, int M, class Left, class Right>
class MatrixSum;
/**
*  @brief Segedosztaly.
*/
template<class T, int N, int M, class Left, class Right>
class MatrixSub;
/**
*  @brief Segedosztaly.
*/
template<class T, int N, int M, class Left, class Right>
class MatrixProd;
/**
*  @brief Segedosztaly.
*/
template<class T, int N, int M, class Mtx>
class MatrixScalarProd;

/**
*  @brief A my_matrix sablont leiro osztaly.
*/
template<class T, int N, int M>
class my_matrix : matrix_base {
public:

    T data[N][M]; /**< A matrix elemeit tartalmazo tomb. */
    my_matrix(){}
    ~my_matrix(){}

    /**
    *   @brief  () operator overloading.
    *
    *   @param  n index
    *   @param  m index
    *   @return the data 2D array
    */
    const T& operator()(int n, int m) const{
      return data[n][m];
    }
    /**
    *   @brief  () operator overloading.
    *
    *   @param  n index
    *   @param  m index
    *   @return the data 2D array
    */
    T& operator()(const int &n, const int &m){
        return data[n][m];
    }

    /**
    *   @brief  = operator overloading.
    *
    *   @param  v a MatrixSum object
    *   @return the data 2D array
    */
    template<class Left, class Right>
    my_matrix<T,N,M>& operator=(const MatrixSum<T,N,M,Left,Right>& v) {
      for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
          data[i][j] = v(i,j);
        }
      }
      return *this;
    }

    /**
    *   @brief  = operator overloading.
    *
    *   @param  v a MatrixSub object
    *   @return the data 2D array
    */
    template<class Left, class Right>
    my_matrix<T,N,M>& operator=(const MatrixSub<T,N,M,Left,Right>& v) {
      for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
          data[i][j] = v(i,j);
        }
      }
      return *this;
    }

    /**
    *   @brief  = operator overloading.
    *
    *   @param  v a MatrixProd object
    *   @return the data 2D array
    */
    template<class Left, class Right>
    my_matrix<T,N,M>& operator=(const MatrixProd<T,N,M,Left,Right>& v) {
      for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
          data[i][j] = v(i,j);
        }
      }
      return *this;
    }

    /**
    *   @brief  = operator overloading.
    *
    *   @param  v a MatriScalarProd object
    *   @return the data 2D array
    */
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

































/**
*  @brief A MatrixSum sablont leiro osztaly.
*/

template<class T, int N, int M, class Left, class Right>
class MatrixSum{
  const Left &left; /**< bal oldalon allo ertek */
  const Right &right; /**< jobb oldalon allo ertek */
public:
  /**
  *   @brief  Default konstruktor.
  *
  *   @param  l bal tag
  *   @param  r jobb tag
  */
  MatrixSum(const Left &l, const Right &r) : left(l), right(r) {}
  ~MatrixSum(){}

  /**
  *   @brief  () operator overloading.
  *
  *   @param  i index
  *   @param  j index
  *   @return az osszeg erteke
  */
  T operator()(int i, int j) const { return left(i,j) + right(i,j); }
};


/**
*   @brief  + operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb matrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M>
inline auto operator+(const my_matrix<T,N,M> &l, const my_matrix<T,N,M> &r) {
  return MatrixSum<T, N, M, my_matrix<T,N,M>, my_matrix<T,N,M> >(l,r);
}

/**
*   @brief  + operator overloading.
*
*   @param  l bal matrixosszeg
*   @param  r jobb matrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator+(const MatrixSum<T,N,M,Left,Right> &l, const my_matrix<T,N,M> &r) {
  return MatrixSum<T, N, M, MatrixSum<T,N,M,Left,Right>, my_matrix<T,N,M> >(l,r);
}

/**
*   @brief  + operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb matrixosszeg
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator+(const my_matrix<T,N,M> &l, const MatrixSum<T,N,M,Left,Right> &r) {
  return MatrixSum<T, N, M, my_matrix<T,N,M>, MatrixSum<T,N,M,Left,Right> >(l,r);
}

/**
*   @brief  + operator overloading.
*
*   @param  l bal matrixosszeg
*   @param  r jobb matrixosszeg
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator+(const MatrixSum<T,N,M,Left,Right> &l, const MatrixSum<T,N,M,Left_,Right_> &r) {
  return MatrixSum<T, N, M, MatrixSum<T,N,M,Left,Right>, MatrixSum<T,N,M,Left_,Right_> >(l,r);
}

















/**
*   @brief  + operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb matrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator+(const MatrixSub<T,N,M,Left,Right> &l, const my_matrix<T,N,M> &r) {
  return MatrixSum<T, N, M, MatrixSub<T,N,M,Left,Right>, my_matrix<T,N,M> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator+(const my_matrix<T,N,M> &l, const MatrixSub<T,N,M,Left,Right> &r) {
  return MatrixSum<T, N, M, my_matrix<T,N,M>, MatrixSub<T,N,M,Left,Right> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator+(const MatrixSub<T,N,M,Left,Right> &l, const MatrixSub<T,N,M,Left_,Right_> &r) {
  return MatrixSum<T, N, M, MatrixSub<T,N,M,Left,Right>, MatrixSub<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator+(const MatrixSub<T,N,M,Left,Right> &l, const MatrixSum<T,N,M,Left_,Right_> &r) {
  return MatrixSum<T, N, M, MatrixSub<T,N,M,Left,Right>, MatrixSum<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator+(const MatrixSum<T,N,M,Left,Right> &l, const MatrixSub<T,N,M,Left_,Right_> &r) {
  return MatrixSum<T, N, M, MatrixSum<T,N,M,Left,Right>, MatrixSub<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator+(const MatrixSub<T,N,M,Left,Right> &l, const MatrixProd<T,N,M,Left_,Right_> &r) {
  return MatrixSum<T, N, M, MatrixSub<T,N,M,Left,Right>, MatrixProd<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator+(const MatrixProd<T,N,M,Left,Right> &l, const MatrixSub<T,N,M,Left_,Right_> &r) {
  return MatrixSum<T, N, M, MatrixProd<T,N,M,Left,Right>, MatrixSub<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator+(const MatrixSub<T,N,M,Left,Right> &l, const MatrixScalarProd<T,N,M,Mtx> &r) {
  return MatrixSum<T, N, M, MatrixSub<T,N,M,Left,Right>, MatrixScalarProd<T,N,M,Mtx> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator+(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixSub<T,N,M,Left,Right> &r) {
  return MatrixSum<T, N, M, MatrixScalarProd<T,N,M,Mtx>, MatrixSub<T,N,M,Left,Right> >(l,r);
}


/**
*   @brief  + operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb matrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator+(const MatrixProd<T,N,M,Left,Right> &l, const my_matrix<T,N,M> &r) {
  return MatrixSum<T, N, M, MatrixProd<T,N,M,Left,Right>, my_matrix<T,N,M> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb szorzatmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator+(const my_matrix<T,N,M> &l, const MatrixProd<T,N,M,Left,Right> &r) {
  return MatrixSum<T, N, M, my_matrix<T,N,M>, MatrixProd<T,N,M,Left,Right> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator+(const MatrixProd<T,N,M,Left,Right> &l, const MatrixProd<T,N,M,Left_,Right_> &r) {
  return MatrixSum<T, N, M, MatrixProd<T,N,M,Left,Right>, MatrixProd<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator+(const MatrixProd<T,N,M,Left,Right> &l, const MatrixSum<T,N,M,Left_,Right_> &r) {
  return MatrixSum<T, N, M, MatrixProd<T,N,M,Left,Right>, MatrixSum<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator+(const MatrixSum<T,N,M,Left,Right> &l, const MatrixProd<T,N,M,Left_,Right_> &r) {
  return MatrixSum<T, N, M, MatrixSum<T,N,M,Left,Right>, MatrixProd<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator+(const MatrixProd<T,N,M,Left,Right> &l, const MatrixScalarProd<T,N,M,Mtx> &r) {
  return MatrixSum<T, N, M, MatrixProd<T,N,M,Left,Right>, MatrixScalarProd<T,N,M,Mtx> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator+(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixProd<T,N,M,Left,Right> &r) {
  return MatrixSum<T, N, M, MatrixScalarProd<T,N,M,Mtx>, MatrixProd<T,N,M,Left,Right> >(l,r);
}




/**
*   @brief  + operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb matrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Mtx>
inline auto operator+(const MatrixScalarProd<T,N,M,Mtx> &l, const my_matrix<T,N,M> &r) {
  return MatrixSum<T, N, M, MatrixScalarProd<T,N,M,Mtx>, my_matrix<T,N,M> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Mtx>
inline auto operator+(const my_matrix<T,N,M> &l, const MatrixScalarProd<T,N,M,Mtx> &r) {
  return MatrixSum<T, N, M, my_matrix<T,N,M>, MatrixScalarProd<T,N,M,Mtx> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Mtx, class Mtx_>
inline auto operator+(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixScalarProd<T,N,M,Mtx_> &r) {
  return MatrixSum<T, N, M, MatrixScalarProd<T,N,M,Mtx>, MatrixScalarProd<T,N,M,Mtx_> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator+(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixSum<T,N,M,Left,Right> &r) {
  return MatrixSum<T, N, M, MatrixScalarProd<T,N,M,Mtx>, MatrixSum<T,N,M,Left,Right> >(l,r);
}
/**
*   @brief  + operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixSum tipusu osszeg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator+(const MatrixSum<T,N,M,Left,Right> &l, const MatrixScalarProd<T,N,M,Mtx> &r) {
  return MatrixSum<T, N, M, MatrixSum<T,N,M,Left,Right>, MatrixScalarProd<T,N,M,Mtx> >(l,r);
}






























/**
*  @brief A MatrixSub sablont leiro osztaly.
*/
template<class T, int N, int M, class Left, class Right>
class MatrixSub{
  const Left &left; /**< bal oldalon allo ertek */
  const Right &right; /**< jobb oldalon allo ertek */
public:
  /**
  *   @brief  Default konstruktor.
  *
  *   @param  l bal tag
  *   @param  r jobb tag
  */
  MatrixSub(const Left &l, const Right &r) : left(l), right(r) {}
  ~MatrixSub(){}
  /**
  *   @brief  () operator overloading.
  *
  *   @param  i index
  *   @param  j index
  *   @return a kulonbsseg erteke
  */
  T operator()(int i, int j) const { return left(i,j) - right(i,j); }
};


/**
*   @brief  - operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb matrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M>
inline auto operator-(const my_matrix<T,N,M> &l, const my_matrix<T,N,M> &r) {
  return MatrixSub<T, N, M, my_matrix<T,N,M>, my_matrix<T,N,M> >(l,r);
}

/**
*   @brief  - operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb matrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator-(const MatrixSub<T,N,M,Left,Right> &l, const my_matrix<T,N,M> &r) {
  return MatrixSub<T, N, M, MatrixSub<T,N,M,Left,Right>, my_matrix<T,N,M> >(l,r);
}

/**
*   @brief  - operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator-(const my_matrix<T,N,M> &l, const MatrixSub<T,N,M,Left,Right> &r) {
  return MatrixSub<T, N, M, my_matrix<T,N,M>, MatrixSub<T,N,M,Left,Right> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator-(const MatrixSub<T,N,M,Left,Right> &l, const MatrixSub<T,N,M,Left_,Right_> &r) {
  return MatrixSub<T, N, M, MatrixSub<T,N,M,Left,Right>, MatrixSub<T,N,M,Left_,Right_> >(l,r);
}



/**
*   @brief  - operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb matrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator-(const MatrixSum<T,N,M,Left,Right> &l, const my_matrix<T,N,M> &r) {
  return MatrixSub<T, N, M, MatrixSum<T,N,M,Left,Right>, my_matrix<T,N,M> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb osszegmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator-(const my_matrix<T,N,M> &l, const MatrixSum<T,N,M,Left,Right> &r) {
  return MatrixSub<T, N, M, my_matrix<T,N,M>, MatrixSum<T,N,M,Left,Right> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator-(const MatrixSum<T,N,M,Left,Right> &l, const MatrixSum<T,N,M,Left_,Right_> &r) {
  return MatrixSub<T, N, M, MatrixSum<T,N,M,Left,Right>, MatrixSum<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator-(const MatrixSum<T,N,M,Left,Right> &l, const MatrixSub<T,N,M,Left_,Right_> &r) {
  return MatrixSub<T, N, M, MatrixSum<T,N,M,Left,Right>, MatrixSub<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator-(const MatrixSub<T,N,M,Left,Right> &l, const MatrixSum<T,N,M,Left_,Right_> &r) {
  return MatrixSub<T, N, M, MatrixSub<T,N,M,Left,Right>, MatrixSum<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator-(const MatrixSum<T,N,M,Left,Right> &l, const MatrixProd<T,N,M,Left_,Right_> &r) {
  return MatrixSub<T, N, M, MatrixSum<T,N,M,Left,Right>, MatrixProd<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator-(const MatrixProd<T,N,M,Left,Right> &l, const MatrixSum<T,N,M,Left_,Right_> &r) {
  return MatrixSub<T, N, M, MatrixProd<T,N,M,Left,Right>, MatrixSum<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator-(const MatrixSum<T,N,M,Left,Right> &l, const MatrixScalarProd<T,N,M,Mtx> &r) {
  return MatrixSub<T, N, M, MatrixSum<T,N,M,Left,Right>, MatrixScalarProd<T,N,M,Mtx> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator-(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixSum<T,N,M,Left,Right> &r) {
  return MatrixSub<T, N, M, MatrixScalarProd<T,N,M,Mtx>, MatrixSum<T,N,M,Left,Right> >(l,r);
}


/**
*   @brief  - operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb matrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator-(const MatrixProd<T,N,M,Left,Right> &l, const my_matrix<T,N,M> &r) {
  return MatrixSub<T, N, M, MatrixProd<T,N,M,Left,Right>, my_matrix<T,N,M> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb szorzatmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right>
inline auto operator-(const my_matrix<T,N,M> &l, const MatrixProd<T,N,M,Left,Right> &r) {
  return MatrixSub<T, N, M, my_matrix<T,N,M>, MatrixProd<T,N,M,Left,Right> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator-(const MatrixProd<T,N,M,Left,Right> &l, const MatrixProd<T,N,M,Left_,Right_> &r) {
  return MatrixSub<T, N, M, MatrixProd<T,N,M,Left,Right>, MatrixProd<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator-(const MatrixProd<T,N,M,Left,Right> &l, const MatrixSub<T,N,M,Left_,Right_> &r) {
  return MatrixSub<T, N, M, MatrixProd<T,N,M,Left,Right>, MatrixSub<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Left_, class Right_>
inline auto operator-(const MatrixSub<T,N,M,Left,Right> &l, const MatrixProd<T,N,M,Left_,Right_> &r) {
  return MatrixSub<T, N, M, MatrixSub<T,N,M,Left,Right>, MatrixProd<T,N,M,Left_,Right_> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator-(const MatrixProd<T,N,M,Left,Right> &l, const MatrixScalarProd<T,N,M,Mtx> &r) {
  return MatrixSub<T, N, M, MatrixProd<T,N,M,Left,Right>, MatrixScalarProd<T,N,M,Mtx> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator-(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixProd<T,N,M,Left,Right> &r) {
  return MatrixSub<T, N, M, MatrixScalarProd<T,N,M,Mtx>, MatrixProd<T,N,M,Left,Right> >(l,r);
}



/**
*   @brief  - operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb matrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Mtx>
inline auto operator-(const MatrixScalarProd<T,N,M,Mtx> &l, const my_matrix<T,N,M> &r) {
  return MatrixSub<T, N, M, MatrixScalarProd<T,N,M,Mtx>, my_matrix<T,N,M> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Mtx>
inline auto operator-(const my_matrix<T,N,M> &l, const MatrixScalarProd<T,N,M,Mtx> &r) {
  return MatrixSub<T, N, M, my_matrix<T,N,M>, MatrixScalarProd<T,N,M,Mtx> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Mtx, class Mtx_>
inline auto operator-(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixScalarProd<T,N,M,Mtx_> &r) {
  return MatrixSub<T, N, M, MatrixScalarProd<T,N,M,Mtx>, MatrixScalarProd<T,N,M,Mtx_> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator-(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixSub<T,N,M,Left,Right> &r) {
  return MatrixSub<T, N, M, MatrixScalarProd<T,N,M,Mtx>, MatrixSub<T,N,M,Left,Right> >(l,r);
}
/**
*   @brief  - operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixSub tipusu kulonbseg.
*/
template<class T, int N, int M, class Left, class Right, class Mtx>
inline auto operator-(const MatrixSub<T,N,M,Left,Right> &l, const MatrixScalarProd<T,N,M,Mtx> &r) {
  return MatrixSub<T, N, M, MatrixSub<T,N,M,Left,Right>, MatrixScalarProd<T,N,M,Mtx> >(l,r);
}































/**
*  @brief A MatrixProd sablont leiro osztaly.
*/
template<class T, int N, int M, class Left, class Right>
class MatrixProd{
  const Left &left; /**< bal oldalon allo ertek */
  const Right &right; /**< jobb oldalon allo ertek */
  int k; /**< a koztes dimenziot eltarolo ertek */
public:
  /**
  *   @brief  Default konstruktor.
  *
  *   @param  l bal tag
  *   @param  r jobb tag
  *   @param  k koztes dimenzio 
  */
  MatrixProd(const Left &l, const Right &r, const int &k) : left(l), right(r), k(k) {}
  ~MatrixProd(){}
  /**
  *   @brief  () operator overloading.
  *
  *   @param  x index
  *   @param  y index
  *   @return a szorzat erteke
  */
  T operator()(int x, int y) const {

    T sum = left(x,0) * right(0,y); /**< az osszeget eltartolo valtozo */

    for (int i=1; i<k; i++)
        sum = sum + left(x,i) * right(i,y);



    return sum;
  }
};


/**
*   @brief  * operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb matrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K>
inline auto operator*(const my_matrix<T,N,M> &l, const my_matrix<T,M,K> &r) {
  return MatrixProd<T, N, K, my_matrix<T,N,M>, my_matrix<T,M,K> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb matrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const MatrixProd<T,N,M,Left,Right> &l, const my_matrix<T,M,K> &r) {
  return MatrixProd<T, N, K, MatrixProd<T,N,M,Left,Right>, my_matrix<T,M,K> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb szorzatmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const my_matrix<T,N,M> &l, const MatrixProd<T,M,K,Left,Right> &r) {
  return MatrixProd<T, N, K, my_matrix<T,N,M>, MatrixProd<T,M,K,Left,Right> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Left_, class Right_>
inline auto operator*(const MatrixProd<T,N,M,Left,Right> &l, const MatrixProd<T,M,K,Left_,Right_> &r) {
  return MatrixProd<T, N, K, MatrixProd<T,N,M,Left,Right>, MatrixProd<T,M,K,Left_,Right_> >(l,r,M);
}



/**
*   @brief  * operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb matrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const MatrixSum<T,N,M,Left,Right> &l, const my_matrix<T,M,K> &r) {
  return MatrixProd<T, N, K, MatrixSum<T,N,M,Left,Right>, my_matrix<T,M,K> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb osszegmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const my_matrix<T,N,M> &l, const MatrixSum<T,M,K,Left,Right> &r) {
  return MatrixProd<T, N, K, my_matrix<T,N,M>, MatrixSum<T,M,K,Left,Right> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Left_, class Right_>
inline auto operator*(const MatrixSum<T,N,M,Left,Right> &l, const MatrixSum<T,M,K,Left_,Right_> &r) {
  return MatrixProd<T, N, K, MatrixSum<T,N,M,Left,Right>, MatrixSum<T,M,K,Left_,Right_> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Left_, class Right_>
inline auto operator*(const MatrixSum<T,N,M,Left,Right> &l, const MatrixProd<T,M,K,Left_,Right_> &r) {
  return MatrixProd<T, N, K, MatrixSum<T,N,M,Left,Right>, MatrixProd<T,M,K,Left_,Right_> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Left_, class Right_>
inline auto operator*(const MatrixProd<T,N,M,Left,Right> &l, const MatrixSum<T,M,K,Left_,Right_> &r) {
  return MatrixProd<T, N, K, MatrixProd<T,N,M,Left,Right>, MatrixSum<T,M,K,Left_,Right_> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Left_, class Right_>
inline auto operator*(const MatrixSum<T,N,M,Left,Right> &l, const MatrixSub<T,M,K,Left_,Right_> &r) {
  return MatrixProd<T, N, K, MatrixSum<T,N,M,Left,Right>, MatrixSub<T,M,K,Left_,Right_> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Left_, class Right_>
inline auto operator*(const MatrixSub<T,N,M,Left,Right> &l, const MatrixSum<T,M,K,Left_,Right_> &r) {
  return MatrixProd<T, N, K, MatrixSub<T,N,M,Left,Right>, MatrixSum<T,M,K,Left_,Right_> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal osszegmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Mtx>
inline auto operator*(const MatrixSum<T,N,M,Left,Right> &l, const MatrixScalarProd<T,M,K,Mtx> &r) {
  return MatrixProd<T, N, K, MatrixSum<T,N,M,Left,Right>, MatrixScalarProd<T,M,K,Mtx> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb osszegmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Mtx>
inline auto operator*(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixSum<T,M,K,Left,Right> &r) {
  return MatrixProd<T, N, K, MatrixScalarProd<T,N,M,Mtx>, MatrixSum<T,M,K,Left,Right> >(l,r,M);
}




/**
*   @brief  * operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb matrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const MatrixSub<T,N,M,Left,Right> &l, const my_matrix<T,M,K> &r) {
  return MatrixProd<T, N, K, MatrixSub<T,N,M,Left,Right>, my_matrix<T,M,K> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const my_matrix<T,N,M> &l, const MatrixSub<T,M,K,Left,Right> &r) {
  return MatrixProd<T, N, K, my_matrix<T,N,M>, MatrixSub<T,M,K,Left,Right> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Left_, class Right_>
inline auto operator*(const MatrixSub<T,N,M,Left,Right> &l, const MatrixSub<T,M,K,Left_,Right_> &r) {
  return MatrixProd<T, N, K, MatrixSub<T,N,M,Left,Right>, MatrixSub<T,M,K,Left_,Right_> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Left_, class Right_>
inline auto operator*(const MatrixSub<T,N,M,Left,Right> &l, const MatrixProd<T,M,K,Left_,Right_> &r) {
  return MatrixProd<T, N, K, MatrixSub<T,N,M,Left,Right>, MatrixProd<T,M,K,Left_,Right_> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Left_, class Right_>
inline auto operator*(const MatrixProd<T,N,M,Left,Right> &l, const MatrixSub<T,M,K,Left_,Right_> &r) {
  return MatrixProd<T, N, K, MatrixProd<T,N,M,Left,Right>, MatrixSub<T,M,K,Left_,Right_> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal kulonbsegmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Mtx>
inline auto operator*(const MatrixSub<T,N,M,Left,Right> &l, const MatrixScalarProd<T,M,K,Mtx> &r) {
  return MatrixProd<T, N, K, MatrixSub<T,N,M,Left,Right>, MatrixScalarProd<T,M,K,Mtx> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb kulonbsegmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Mtx>
inline auto operator*(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixSub<T,M,K,Left,Right> &r) {
  return MatrixProd<T, N, K, MatrixScalarProd<T,N,M,Mtx>, MatrixSub<T,M,K,Left,Right> >(l,r,M);
}



/**
*   @brief  * operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb matrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Mtx>
inline auto operator*(const MatrixScalarProd<T,N,M,Mtx> &l, const my_matrix<T,M,K> &r) {
  return MatrixProd<T, N, K, MatrixScalarProd<T,N,M,Mtx>, my_matrix<T,M,K> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal matrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Mtx>
inline auto operator*(const my_matrix<T,N,M> &l, const MatrixScalarProd<T,M,K,Mtx> &r) {
  return MatrixProd<T, N, K, my_matrix<T,N,M>, MatrixScalarProd<T,M,K,Mtx> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Mtx, class Mtx_>
inline auto operator*(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixScalarProd<T,M,K,Mtx_> &r) {
  return MatrixProd<T, N, K, MatrixScalarProd<T,N,M,Mtx>, MatrixScalarProd<T,M,K,Mtx_> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal skalarszorzatmatrix
*   @param  r jobb szorzatmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Mtx>
inline auto operator*(const MatrixScalarProd<T,N,M,Mtx> &l, const MatrixProd<T,M,K,Left,Right> &r) {
  return MatrixProd<T, N, K, MatrixScalarProd<T,N,M,Mtx>, MatrixProd<T,M,K,Left,Right> >(l,r,M);
}
/**
*   @brief  * operator overloading.
*
*   @param  l bal szorzatmatrix
*   @param  r jobb skalarszorzatmatrix
*   @return MatrixProd tipusu szorzat.
*/
template<class T, int N, int M, int K, class Left, class Right, class Mtx>
inline auto operator*(const MatrixProd<T,N,M,Left,Right> &l, const MatrixScalarProd<T,M,K,Mtx> &r) {
  return MatrixProd<T, N, K, MatrixProd<T,N,M,Left,Right>, MatrixScalarProd<T,M,K,Mtx> >(l,r,M);
}


































/**
*  @brief A MatrixScalarProd sablont leiro osztaly.
*/
 template<class T, int N, int M, class Mtx>
 class MatrixScalarProd{
   const Mtx &mtx; /**< a muvelet matrixa */
   const T &scalar; /**< a muvelet skalarja */

 public:
   /**
   *   @brief  Default konstruktor.
   *
   *   @param  m bal matrix
   *   @param  s jobb skalar
   */
   MatrixScalarProd(const Mtx &m, const T &s) : mtx(m), scalar(s) {}
   ~MatrixScalarProd(){}
   /**
   *   @brief  () operator overloading.
   *
   *   @param  i index
   *   @param  j index
   *   @return a skalarszorzat erteke
   */
   T operator()(int i, int j) const { return scalar * mtx(i,j); }
 };
 /**
 *   @brief  * operator overloading.
 *
 *   @param  m bal matrix
 *   @param  s jobb skalar
 *   @return MatrixScalarProd tipusu skalarszorzat.
 */
 template<class T, int N, int M>
 inline auto operator*(const my_matrix<T,N,M> &m, const T &s) {
   return MatrixScalarProd<T, N, M, my_matrix<T,N,M> >(m,s);
 }
 /**
 *   @brief  * operator overloading.
 *
 *   @param  s bal skalar
 *   @param  m jobb matrix
 *   @return MatrixScalarProd tipusu skalarszorzat.
 */
 template<class T, int N, int M>
 inline auto operator*(const T &s, const my_matrix<T,N,M> &m) {
   return MatrixScalarProd<T, N, M, my_matrix<T,N,M> >(m,s);
 }
 /**
 *   @brief  * operator overloading.
 *
 *   @param  m bal skalarszorzatmatrix
 *   @param  s jobb skalar
 *   @return MatrixScalarProd tipusu skalarszorzat.
 */
 template<class T, int N, int M, class Mtx>
 inline auto operator*(const MatrixScalarProd<T,N,M,Mtx> &m, const T &s) {
   return MatrixScalarProd<T, N, M, MatrixScalarProd<T,N,M,Mtx> >(m,s);
 }
 /**
 *   @brief  * operator overloading.
 *
 *   @param  s bal skalar
 *   @param  m jobb skalarszorzatmatrix
 *   @return MatrixScalarProd tipusu skalarszorzat.
 */
 template<class T, int N, int M, class Mtx>
 inline auto operator*(const T &s, const MatrixScalarProd<T,N,M,Mtx> &m) {
   return MatrixScalarProd<T, N, M, MatrixScalarProd<T,N,M,Mtx> >(m,s);
 }

 /**
 *   @brief  * operator overloading.
 *
 *   @param  m bal osszegmatrix
 *   @param  s jobb skalar
 *   @return MatrixScalarProd tipusu skalarszorzat.
 */
 template<class T, int N, int M, class Left, class Right>
 inline auto operator*(const MatrixSum<T,N,M,Left,Right> &m, const T &s) {
   return MatrixScalarProd<T, N, M, MatrixSum<T,N,M,Left,Right> >(m,s);
 }
 /**
 *   @brief  * operator overloading.
 *
 *   @param  s bal skalar
 *   @param  m jobb osszegmatrix
 *   @return MatrixScalarProd tipusu skalarszorzat.
 */
 template<class T, int N, int M, class Left, class Right>
 inline auto operator*(const T &s, const MatrixSum<T,N,M,Left,Right> &m) {
   return MatrixScalarProd<T, N, M, MatrixSum<T,N,M,Left,Right> >(m,s);
 }

 /**
 *   @brief  * operator overloading.
 *
 *   @param  m bal kulonbsegmatrix
 *   @param  s jobb skalar
 *   @return MatrixScalarProd tipusu skalarszorzat.
 */
 template<class T, int N, int M, class Left, class Right>
 inline auto operator*(const MatrixSub<T,N,M,Left,Right> &m, const T &s) {
   return MatrixScalarProd<T, N, M, MatrixSub<T,N,M,Left,Right> >(m,s);
 }
 /**
 *   @brief  * operator overloading.
 *
 *   @param  s bal skalar
 *   @param  m jobb kulonbsegmatrix
 *   @return MatrixScalarProd tipusu skalarszorzat.
 */
 template<class T, int N, int M, class Left, class Right>
 inline auto operator*(const T &s, const MatrixSub<T,N,M,Left,Right> &m) {
   return MatrixScalarProd<T, N, M, MatrixSub<T,N,M,Left,Right> >(m,s);
 }

 /**
 *   @brief  * operator overloading.
 *
 *   @param  m bal szorzatmatrix
 *   @param  s jobb skalar
 *   @return MatrixScalarProd tipusu skalarszorzat.
 */
 template<class T, int N, int M, class Left, class Right>
 inline auto operator*(const MatrixProd<T,N,M,Left,Right> &m, const T &s) {
   return MatrixScalarProd<T, N, M, MatrixProd<T,N,M,Left,Right> >(m,s);
 }
 /**
 *   @brief  * operator overloading.
 *
 *   @param  s bal skalar
 *   @param  m jobb szorzatmatrix
 *   @return MatrixScalarProd tipusu skalarszorzat.
 */
 template<class T, int N, int M, class Left, class Right>
 inline auto operator*(const T &s, const MatrixProd<T,N,M,Left,Right> &m) {
   return MatrixScalarProd<T, N, M, MatrixProd<T,N,M,Left,Right> >(m,s);
 }



































/*
int main() {


    my_matrix<int,3,5> mtx1;
    my_matrix<int,5,8> mtx2;
    my_matrix<int,8,2> mtx4;
    my_matrix<int,2,1> mtx5;

    cout << "mtx1: " << endl;
    for(int i=0;i<3;i++){
      for(int j=0; j<5; j++){
          mtx1(i,j) = rand() % 5 + 1;
          cout << mtx1(i,j) << " ";
      }
      cout << endl;
    }
    cout << endl;

    cout << "mtx2: " << endl;
    for(int i=0;i<5;i++){
      for(int j=0; j<8; j++){
          mtx2(i,j) = rand() % 5 + 1;
          cout << mtx2(i,j) << " ";
      }
      cout << endl;
    }
    cout << endl;

    cout << "mtx4: " << endl;
    for(int i=0;i<8;i++){
      for(int j=0; j<2; j++){
          mtx4(i,j) = rand() % 5 + 1;
          cout << mtx4(i,j) << " ";
      }
      cout << endl;
    }
    cout << endl;

    cout << "mtx5: " << endl;
    for(int i=0;i<2;i++){
      for(int j=0; j<1; j++){
          mtx5(i,j) = rand() % 5 + 1;
          cout << mtx5(i,j) << " ";
      }
      cout << endl;
    }
    cout << endl;




    my_matrix<int,3,8> mtx3;
    for(int i=0;i<3;i++){
      for(int j=0; j<8; j++){
          mtx3(i,j) = 0;
      }
    }

    mtx3 = mtx1 * mtx2;


    cout << "mtx3: " << endl;
    for(int i=0;i<3;i++){
      for(int j=0; j<8; j++){
          //mtx3(i,j) = rand() % 100 + 1;
          cout << mtx3(i,j) << " ";
      }
      cout << endl;
    }
    cout << endl;


my_matrix<int,5,3> mtx0;
my_matrix<int,5,3> mtx1;
my_matrix<int,5,3> mtx2;
my_matrix<int,5,3> mtx3;
my_matrix<int,5,3> mtx4;
my_matrix<int,5,3> mtx5;
my_matrix<int,5,3> mtx6;

cout << "mtx1: " << endl;
for(int i=0;i<5;i++){
  for(int j=0; j<3; j++){
      mtx1(i,j) = rand() % 5 + 1;
      mtx2(i,j) = rand() % 5 + 1;
      mtx3(i,j) = rand() % 5 + 1;
      mtx4(i,j) = rand() % 5 + 1;
      mtx5(i,j) = rand() % 5 + 1;
      mtx6(i,j) = rand() % 5 + 1;
      cout << mtx1(i,j) << " ";
  }
  cout << endl;
}
cout << endl;

cout << "mtx2: " << endl;
for(int i=0;i<5;i++){
  for(int j=0; j<3; j++){
      mtx0(i,j) = 0;
      cout << mtx2(i,j) << " ";
  }
  cout << endl;
}
cout << endl;

mtx0 = (mtx1 + (mtx2 + mtx3)) + ((mtx4 + mtx5) + mtx6);

cout << "mtx0: " << endl;
for(int i=0;i<5;i++){
  for(int j=0; j<3; j++){
      cout << mtx0(i,j) << " ";
  }
  cout << endl;
}
cout << endl;



    return 0;
}
*/
