package colorclicker;

import java.awt.Point;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author pinter
 */
public class Matrix {

    private final Field[][] matrix;
    private final int matrixSize;
    


    public Matrix(int matrixSize) {
        this.matrixSize = matrixSize;
        matrix = new Field[this.matrixSize][this.matrixSize];
        for (int i = 0; i < this.matrixSize; ++i) {
            for (int j = 0; j < this.matrixSize; ++j) {
                matrix[i][j]=new Field();
            }
        }
    }

    public Field get(int x, int y) {
        return matrix[x][y];
    }
    
    public Field get(Point point) {
        int x = (int)point.getX();
        int y = (int)point.getY();
        return get(x, y);
    }

    public int getMatrixSize() {
        return matrixSize;
    }

}
