#include "boolean.h"
#include <stdio.h>
#include <math.h>
#include "matrix.h"

void createMatrix(int nRows, int nCols, Matrix *m){
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;
}

#define ROW_EFF(M) (M).rowEff
#define COL_EFF(M) (M).colEff
#define ELMT(M, i, j) (M).mem[(i)][(j)]

boolean isMatrixIdxValid(int i, int j){
    return (i >= 0 && j >= 0 && i < ROW_CAP && j < COL_CAP);
}
/* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType getLastIdxRow(Matrix m){
    return ROW_EFF(m) - 1;
}
/* Mengirimkan Index baris terbesar m */

IdxType getLastIdxCol(Matrix m){
    return COL_EFF(m) - 1;
}
/* Mengirimkan Index kolom terbesar m */

boolean isIdxEff(Matrix m, IdxType i, IdxType j){
    return (i >= 0 && i < ROW_EFF(m) && j >= 0 && j < COL_EFF(m));
}
/* Mengirimkan true jika i, j adalah Index efektif bagi m */

ElType getElmtDiagonal(Matrix m, IdxType i){
    return ELMT(m, i, i);
}
/* Mengirimkan elemen m(i,i) */

/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mOut){
    ROW_EFF(*mOut) = ROW_EFF(mIn);
    COL_EFF(*mOut) = COL_EFF(mIn);
    for (int i = 0; i < ROW_EFF(mIn); i++){
        for (int j = 0; j < COL_EFF(mIn); j++){
            ELMT(*mOut, i, j) = ELMT(mIn, i, j);
        }
    }
}
/* Melakukan assignment mOut <- mIn */

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol){
    createMatrix(nRow, nCol, m);
    for (int i = 0; i < nRow; i++){
        for (int j = 0; j < nCol; j++){
            scanf("%d", &ELMT(*m, i, j));
        }
    }
}
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/

void displayMatrix(Matrix m){
    for (int i = 0; i < ROW_EFF(m); i++){
        for (int j = 0; j < COL_EFF(m); j++){
            printf("%d", ELMT(m, i, j));
            if (j != COL_EFF(m) - 1){
                printf(" ");
            }
        }
        if (i != ROW_EFF(m) - 1){
            printf("\n");
        }
    }
}
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
Matrix addMatrix(Matrix m1, Matrix m2){
    Matrix m;
    createMatrix(ROW_EFF(m1), COL_EFF(m1), &m);
    for (int i = 0; i < ROW_EFF(m1); i++){
        for (int j = 0; j < COL_EFF(m1); j++){
            ELMT(m, i, j) = ELMT(m1, i, j) + ELMT(m2, i, j);
        }
    }
    return m;
}
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
Matrix subtractMatrix(Matrix m1, Matrix m2){
    Matrix m;
    createMatrix(ROW_EFF(m1), COL_EFF(m1), &m);
    for (int i = 0; i < ROW_EFF(m1); i++){
        for (int j = 0; j < COL_EFF(m1); j++){
            ELMT(m, i, j) = ELMT(m1, i, j) - ELMT(m2, i, j);
        }
    }
    return m;
}
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
Matrix multiplyMatrix(Matrix m1, Matrix m2){
    Matrix m;
    createMatrix(ROW_EFF(m1), COL_EFF(m2), &m);
    for (int i = 0; i < ROW_EFF(m1); i++){
        for (int j = 0; j < COL_EFF(m2); j++){
            ELMT(m, i, j) = 0;
            for (int k = 0; k < COL_EFF(m1); k++){
                ELMT(m, i, j) += ELMT(m1, i, k) * ELMT(m2, k, j);
            }
        }
    }
    return m;
}
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan m1 * m2 */
Matrix multiplyByConst(Matrix m, ElType x){
    Matrix mOut;
    createMatrix(ROW_EFF(m), COL_EFF(m), &mOut);
    for (int i = 0; i < ROW_EFF(m); i++){
        for (int j = 0; j < COL_EFF(m); j++){
            ELMT(mOut, i, j) = ELMT(m, i, j) * x;
        }
    }
    return mOut;
}
/* Mengirim hasil perkalian setiap elemen m dengan x */
void pMultiplyByConst(Matrix *m, ElType k){
    for (int i = 0; i < ROW_EFF(*m); i++){
        for (int j = 0; j < COL_EFF(*m); j++){
            ELMT(*m, i, j) *= k;
        }
    }
}
/* I.S. m terdefinisi, k terdefinisi */
/* F.S. Mengalikan setiap elemen m dengan k */

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isMatrixEqual(Matrix m1, Matrix m2){
    if (!isMatrixSizeEqual(m1, m2)){
        return false;
    }
    for (int i = 0; i < ROW_EFF(m1); i++){
        for (int j = 0; j < COL_EFF(m1); j++){
            if (ELMT(m1, i, j) != ELMT(m2, i, j)){
                return false;
            }
        }
    }
    return true;
}
/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
boolean isMatrixNotEqual(Matrix m1, Matrix m2){
    return !isMatrixEqual(m1, m2);
}
/* Mengirimkan true jika m1 tidak sama dengan m2 */
boolean isMatrixSizeEqual(Matrix m1, Matrix m2){
    return (ROW_EFF(m1) == ROW_EFF(m2) && COL_EFF(m1) == COL_EFF(m2));
}
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
/* yaitu RowEff(m1) = RowEff (m2) dan ColEff (m1) = ColEff (m2) */

/* ********** Operasi lain ********** */
int countElmt(Matrix m){
    return ROW_EFF(m) * COL_EFF(m);
}
/* Mengirimkan banyaknya elemen m */

/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m){
    return (ROW_EFF(m) == COL_EFF(m));
}
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
boolean isSymmetric(Matrix m){
    if (!isSquare(m)){
        return false;
    }
    for (int i = 0; i < ROW_EFF(m); i++){
        for (int j = 0; j < COL_EFF(m); j++){
            if (ELMT(m, i, j) != ELMT(m, j, i)){
                return false;
            }
        }
    }
    return true;
}
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
boolean isIdentity(Matrix m){
    if (!isSquare(m)){
        return false;
    }
    for (int i = 0; i < ROW_EFF(m); i++){
        for (int j = 0; j < COL_EFF(m); j++){
            if (i == j){
                if (ELMT(m, i, j) != 1){
                    return false;
                }
            } else {
                if (ELMT(m, i, j) != 0){
                    return false;
                }
            }
        }
    }
    return true;
}
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan 
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
boolean isSparse(Matrix m){
    int count = 0;
    for (int i = 0; i < ROW_EFF(m); i++){
        for (int j = 0; j < COL_EFF(m); j++){
            if (ELMT(m, i, j) != 0){
                count++;
            }
        }
    }
    return (count <= 0.05 * countElmt(m));
}
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
Matrix negation(Matrix m){
    Matrix mOut;
    createMatrix(ROW_EFF(m), COL_EFF(m), &mOut);
    for (int i = 0; i < ROW_EFF(m); i++){
        for (int j = 0; j < COL_EFF(m); j++){
            ELMT(mOut, i, j) = (-1) * ELMT(m, i, j);
        }
    }
    return mOut;
}
/* Menghasilkan salinan m dengan setiap elemen dinegasikan (dikalikan -1) */
void pNegation(Matrix *m){
    for (int i = 0; i < ROW_EFF(*m); i++){
        for (int j = 0; j < COL_EFF(*m); j++){
            ELMT(*m, i, j) *= (-1);
        }
    }
}
/* I.S. m terdefinisi */
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
float determinant(Matrix m){
    if (ROW_EFF(m) == 1){
        return ELMT(m, 0, 0);
    } else {
        float det = 0;
        for (int i = 0; i < ROW_EFF(m); i++){
            Matrix subMatrix;
            createMatrix(ROW_EFF(m) - 1, COL_EFF(m) - 1, &subMatrix);
            for (int j = 1; j < ROW_EFF(m); j++){
                for (int k = 0; k < COL_EFF(m); k++){
                    if (k < i){
                        ELMT(subMatrix, j - 1, k) = ELMT(m, j, k);
                    } else if (k > i){
                        ELMT(subMatrix, j - 1, k - 1) = ELMT(m, j, k);
                    }
                }
            }
            det += pow(-1, i) * ELMT(m, 0, i) * determinant(subMatrix);
        }
        return det;
    }
}
/* Prekondisi: isSquare(m) */
/* Menghitung nilai determinan m */
Matrix transpose(Matrix m){
    Matrix mOut;
    createMatrix(COL_EFF(m), ROW_EFF(m), &mOut);
    for (int i = 0; i < ROW_EFF(m); i++){
        for (int j = 0; j < COL_EFF(m); j++){
            ELMT(mOut, j, i) = ELMT(m, i, j);
        }
    }
    return mOut;
}
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. menghasilkan salinan transpose dari m, yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
void pTranspose(Matrix *m){
    Matrix mOut;
    createMatrix(COL_EFF(*m), ROW_EFF(*m), &mOut);
    for (int i = 0; i < ROW_EFF(*m); i++){
        for (int j = 0; j < COL_EFF(*m); j++){
            ELMT(mOut, j, i) = ELMT(*m, i, j);
        }
    }
    copyMatrix(mOut, m);
}
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
