# FELADATKIÍRÁS #

A feladat olyan osztálysablon írása, amely kétdimenziós, dimenziónként 
tetszőleges méretű (NxM-es) mátrixot reprezentál. Az osztály sablonparaméterei
határozzák meg a mátrix alaptípusát és méreteit. A mátrix elemeihez való 
hozzáférést (indexelést) biztosítani kell.

A matematikai szabályoknak megfelelően paraméterezett sablonpéldányok 
objektumai között meg kell valósítani az összeadás és kivonás műveleteket 
(NxM-es mátrixok között), a szorzás műveletet (NxK és KxM-es mátrixok között), 
valamint a konstanssal (azaz a mátrix alaptípusával) való szorzást. A 
műveleteket a megfelelő (+, -, *) C++ operátorok felüldefiniálásával kell 
megvalósítani.

A műveletek megvalósításának olyannak kell lennie, hogy bonyolult 
mátrix-kifejezések során se keletkezzenek felesleges temporális mátrixok. 
(ld. Kifejezés sablonok - Expression templates)

Az osztálysablon publikus interfésze (a sablon neve, a sablonparaméterezése, a 
publikus metódusainak szignatúrája) kötött, azaz legalább az alábbiaknak meg
kell felelnie (de amennyiben a feladatkiírás szükségessé teszi további publikus
metódusokkal, belső típusokkal bővíthető, valamint az osztály törzsén kívül is 
szerepelhetnek további típusok, metódusok):


```
#!c++

// === MEGVALÓSÍTANDÓ ===

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
template<class T, int N, int M>
class my_matrix : matrix_base {
public:
    /** A sablonpéldány rendelkezik default konstruktorral. */
    my_matrix();
    /** 
     * A mátrix elemeihez való hozzáférést a kétparaméteres függvényhívás 
     * operátor felüldefiniálása biztosítja.
     */
    const T& operator()(int n, int m) const;
    T& operator()(int n, int m);
};

// === MEGVALÓSÍTÁS VÉGE ===

/** 
 * Példa a mátrix sablon egy felhasználására. A beadott feladatban nem szabad 
 * szerepelnie. 
 */
int main() {
    my_matrix<int,2,2> mtx1;
    my_matrix<int,2,2> mtx2;
    my_matrix<int,2,2> mtx3;
    my_matrix<int,2,2> mtx4;
    
    mtx4 = mtx1 + mtx2 + mtx3;
    
    return 0;
}
```
