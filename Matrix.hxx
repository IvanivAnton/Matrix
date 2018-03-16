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
    double **mtrx;

    double** array2d(unsigned int rows,unsigned int cols){

        mtrx = new double* [rows];
        for(int k=0;k<rows;k++){
            mtrx[k] = new double[cols];
        }
        return mtrx;
    }

    void freeArray2d(double **array,unsigned int rows){
        for (int i = 0; i < rows; i++) {
                delete array[i];
        }
        delete array;
    }

public:
    Matrix(){                                                                                       //пустой констрктор;

    }
    Matrix(unsigned int rows,unsigned int cols,string name): rows(rows),cols(cols),name(name){
//        int F0=0;
//        int F1=1;
//        int Fn=0;
        mtrx=array2d(rows,cols);
        for (int i = 0; i <rows ; i++) {
            for (int j = 0; j <cols; j++) {
                mtrx[i][j]=i+j;
//                F0=F1;
//                F1=Fn;
//                Fn=F0+F1;
            }
        }
    }// Конструктор принимающий cтроки,столбцы и имя
    Matrix(Matrix &matrix) {
        setName(matrix.getName());
        setRows(matrix.getRows());
        setCols(matrix.getCols());
        mtrx=array2d(rows,cols);
        for (int i = 0; i <rows ; i++) {
            for (int j = 0; j < cols; j++) {
                mtrx[i][j]=matrix.mtrx[i][j];
            }
        }
    }                                                                   // Копирующий конструктор

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
        double **mtrxC = copyMt(*this);
        freeArray2d(mtrx,rows);
        mtrx = array2d(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mtrx[i][j] = mtrxC[j][i];
            }
        }
            setRows(cols);
            setCols(rows);
            return *this;
    }

    double** copyMt(Matrix &matrix){
        unsigned rows=matrix.rows;
        unsigned cols=matrix.cols;
        double** mtrx1=array2d(rows,cols);
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
        mtrx=array2d(rows,cols);
        for (int i = 0; i <rows ; i++) {
            for (int j = 0; j < cols; j++) {
                mtrx[i][j]=matrix.mtrx[i][j];
            }
        }
        return *this;
    }

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