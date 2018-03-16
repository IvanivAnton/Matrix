#ifndef MATRIX_MATRIXES_HXX
#define MATRIX_MATRIXES_HXX

#include <iostream>
#include <string>
using namespace std;

class Matrix {

private:
    unsigned rows;
    unsigned cols;
    string name;
    int **mtrx;

    int ** crMatrix(unsigned int rows, unsigned int cols){

        mtrx = new int* [rows];
        for(int k=0;k<rows;k++){
            mtrx[k] = new int[cols];
        }
        return mtrx;
    }

    void freeMatrix(int **array, unsigned int rows){
        for (int i = 0; i < rows; i++) {
                delete array[i];
        }
        delete array;
    }

public:
    Matrix(){                                                                                       //пустой констрктор;

    }

    Matrix(unsigned int rows,unsigned int cols,string name): rows(rows),cols(cols),name(name){ // Конструктор принимающий cтроки,столбцы и имя
        int F0=0;
        int F1=1;
        int Fn=0;
        mtrx= crMatrix(rows, cols);
        for (int i = 0; i <rows ; i++) {
            for (int j = 0; j <cols; j++) {
                mtrx[i][j]=i+j;
                F0=F1;
                F1=Fn;
                Fn=F0+F1;
            }
        }
    }
    Matrix(Matrix &matrix) {                                                    // Копирующий конструктор
        setName(matrix.getName());
        setRows(matrix.getRows());
        setCols(matrix.getCols());
        mtrx= crMatrix(rows, cols);
        for (int i = 0; i <rows ; i++) {
            for (int j = 0; j < cols; j++) {
                mtrx[i][j]=matrix.mtrx[i][j];
            }
        }
    }

    void printMt(){
        string name=getName();
        int rows=getRows();
        int cols=getCols();
        int k=0;
        cout<<endl<<name;
        while(k<cols){
            if(k<100)
                cout<<"  "<<k<<"  ";
            if(k>100)
                cout<<' '<<k<<' ';
            k++;
        }
        cout<<endl;
        for (int i = 0; i < rows ; i++) {
            for (int j = 0; j < cols; j++) {
                if(j==0) cout<<""<<i<<"";
                if(mtrx[i][j]<10)
                    cout<<" ["<<mtrx[i][j]<<"] ";
                if(mtrx[i][j]>=10&&mtrx[i][j]<100){
                    cout<<" ["<<mtrx[i][j]<<"]";
                    if(mtrx[i][j+1]>=100) cout<<' ';
                }
                if(mtrx[i][j]>=100&&j==0)
                    cout<<" ["<<mtrx[i][j]<<"]";
                if(mtrx[i][j]>=100&&j!=0)
                    cout<<"["<<mtrx[i][j]<<"]";
                if(j==cols-1) cout<<endl;
            }
        }
        cout<<endl;
    }

    Matrix addition(Matrix &matrix1){
        if(rows!=matrix1.rows||cols!=matrix1.cols)
            throw string("Matrix not equals\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                    mtrx[i][j]=mtrx[i][j]+matrix1.mtrx[i][j];
            }
        }
        return *this;
    }

    Matrix multiplication(Matrix &matrix){
        if(cols!=matrix.rows){
            throw string("Matrix not equals\n");
        }
        for (int i = 0; i < rows;i++) {
            for (int j = 0; j < cols; j++) {
                double s=0;
                for(int k=0;k<rows;k++){
                    s=s+mtrx[i][k]+matrix.mtrx[k][j];
                    }
                mtrx[i][j]=s;
                }
            }
        return *this;
        }

    Matrix transpose() {
        unsigned int rows = getRows();
        unsigned int cols = getCols();
        Matrix matrixc(*this);
        freeMatrix(mtrx, rows);
        mtrx = crMatrix(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mtrx[i][j] = matrixc.mtrx[j][i];
            }
        }
            setRows(cols);
            setCols(rows);
            return *this;
    }

    int ** copyMt(Matrix &matrix){
        unsigned rows=matrix.rows;
        unsigned cols=matrix.cols;
        int ** mtrx1= crMatrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mtrx1[i][j] = matrix.mtrx[i][j];
            }
        }
        return mtrx1;

    }

    Matrix copy(Matrix &matrix){
        setName(matrix.getName());
        setRows(matrix.getRows());
        setCols(matrix.getCols());
        mtrx= crMatrix(rows, cols);
        for (int i = 0; i <rows ; i++) {
            for (int j = 0; j < cols; j++) {
                mtrx[i][j]=matrix.mtrx[i][j];
            }
        }
        return *this;
    }

    int determinant(){
        unsigned int rows=getRows();
        unsigned int cols=getCols();
        if(rows==3&&cols==3){
            cout<< this->determaminat3x3();
            return EXIT_SUCCESS;
        }

        //TODO Определитель
    }
    int determaminat3x3(){
//        unsigned int rows=matrix.rows;
//        unsigned int cols=matrix.cols;
        int Temp1=mtrx[0][0];
        int Temp2=mtrx[0][1];
        int Temp3=mtrx[0][2];
        int Temp4=mtrx[1][0];
        int Temp5=mtrx[1][1];
        int Temp6=mtrx[1][2];
        int Temp7=mtrx[2][0];
        int Temp8=mtrx[2][1];
        int Temp9=mtrx[2][2];
        int Temp;
        Temp = Temp1 * Temp5 * Temp9 + Temp2 * Temp6 * Temp7 + Temp4 * Temp3 * Temp8 -
               Temp3 * Temp5 * Temp7 - Temp2 * Temp4 * Temp9 - Temp1 * Temp6 * Temp8;
        return Temp;
   }


    Matrix division(){
        //TODO Деление
    }

    Matrix inverse(){
        //TODO Обратная матрица
    }
    Matrix multiAT(int nmbr){
        unsigned int rows=getRows();
        unsigned int cols=getCols();
        for(int k = 0; k < rows;k++){
            for (int i = 0; i < cols; i++) {
                mtrx[k][i]=mtrx[k][i]*nmbr;
            }
        }
        return *this;
        //TODO Умножение на число DONE
    }
    Matrix subtraction(Matrix &matrix){
        unsigned int rows=getRows();
        unsigned int cols=getCols();
        if(rows!=matrix.rows||cols!=matrix.cols)
            throw string("Matrix not equals\n");
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mtrx[i][j]=mtrx[i][j]-matrix.mtrx[i][j];
            }
        }
        //TODO Вычитание DONE
    }
    //TODO перегрузка операторов *,+,-,/,==
//Getters
     unsigned int getRows() const {
        return rows;
    }

    unsigned int getCols() const {
        return cols;
    }

    const string &getName() const {
        return name;
    }
//Setters
    void setRows(unsigned int rows) {
        Matrix::rows = rows;
    }

    void setCols(unsigned int cols) {
        Matrix::cols = cols;
    }

    void setName(const string &name) {
        Matrix::name = name;
    }
};


#endif //ARRAYS2XN_MATRIXES_HXX