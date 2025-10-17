package colorclicker;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Collections;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 *
 * @author pinter
 */
public class MatrixGUI {

    private final JButton[][] buttons;
    private final Matrix matrix;
    private final JPanel matrixPanel;
    private final ArrayList<Color> colors = new ArrayList<>();
    private int turn = 0;
    private Integer prevX;
    private Integer prevY;
    private final Color white = Color.white;
    private final Color black = Color.black;
    private Color prevColor = null;
    private int whiteCount;
    private int blackCount;
    private final JLabel turnLabel;
    

    // constructor for MatrixGUI
    public MatrixGUI(int matrixSize) {
        matrix = new Matrix(matrixSize);
        matrixPanel = new JPanel();
        this.whiteCount = matrixSize;
        this.blackCount = matrixSize;
        Color btnColor;
        matrixPanel.setLayout(new GridLayout(matrix.getMatrixSize(), matrix.getMatrixSize()));
        buttons = new JButton[matrix.getMatrixSize()][matrix.getMatrixSize()];
        
        for(int i=0; i<matrixSize*matrixSize; ++i) {
            if(whiteCount>0) {btnColor=white; whiteCount--;}
            else if (blackCount>0) {btnColor=black; blackCount--;}
            else {btnColor=null;}
            colors.add(btnColor);
        }
        
        Collections.shuffle(colors);
        
        int index=0;
        for (int i = 0; i < matrix.getMatrixSize(); ++i) {
            for (int j = 0; j < matrix.getMatrixSize(); ++j) {
                JButton button = new JButton();
                button.addActionListener(new ButtonListener(i, j));
                button.setPreferredSize(new Dimension(60, 60));
                buttons[i][j] = button;
                buttons[i][j].setBackground(colors.get(index)); index++;
                matrixPanel.add(button);
            }
        }
        
        turnLabel = new JLabel(" ");
        turnLabel.setHorizontalAlignment(JLabel.RIGHT);
        turnLabel.setText(calcTurn() + " turn");
    }
    
    public final String calcTurn() {
        return this.turn%2==0 ? "white" : "black";
    }
    
    public final Color turnColor() {
        if(this.turn%2==0) {
            return white;
        } else {
            return black;
        }
    }
    
    public boolean isOver() {
        if(this.turn==matrix.getMatrixSize()*5) {
            return true;
        } else {
            blackCount=0;
            whiteCount=0;
            for(int i=0; i<matrix.getMatrixSize(); ++i) {
                for(int j=0; j<matrix.getMatrixSize(); ++j) {
                    if(buttons[i][j].getBackground()==black) blackCount++;
                    if(buttons[i][j].getBackground()==white) whiteCount++;
                }
            }
            return  blackCount == 0 || whiteCount == 0;
        }
    }
    
    
    public void refresh() {
        String winner;
        if(isOver()) {
            if(blackCount > whiteCount) {
                winner = "black";
            } else if(blackCount < whiteCount) {
                winner = "white";
            } else {
                winner = "draw";
            }
            JOptionPane.showMessageDialog(matrixPanel, winner, "Game over, winner:",
                    JOptionPane.PLAIN_MESSAGE);
        } else {
            turnLabel.setText(calcTurn() + " turn");
        }
    }

    public JPanel getMatrixPanel() {
        return matrixPanel;
    }
    
    public JLabel getTurnLabel() {
        return turnLabel;
    }
    
    public void recursiveRight(int x, int y, Color prevColor) {
        if(y < matrix.getMatrixSize()) {
            if(prevColor!=white && prevColor!=black) {
                System.out.println("Stop here right");
            } else {
                Color currentColor = buttons[x][y].getBackground();
                buttons[x][y].setBackground(prevColor);
                prevY=y;
                recursiveRight(x, y+1, currentColor);
            }
        }
    }
    
    public void recursiveLeft(int x, int y, Color prevColor) {
        if(y >= 0) {
            if(prevColor!=white && prevColor!=black) {
                System.out.println("Stop here left");
            } else {
                Color currentColor = buttons[x][y].getBackground();
                buttons[x][y].setBackground(prevColor);
                prevY=y;
                recursiveLeft(x, y-1, currentColor);
            }
        }
    }
    
    public void recursiveBottom(int x, int y, Color prevColor) {
        if(x < matrix.getMatrixSize()) {
            if(prevColor!=white && prevColor!=black) {
                System.out.println("Stop here bottom");
            } else {
                Color currentColor = buttons[x][y].getBackground();
                buttons[x][y].setBackground(prevColor);
                prevX=x;
                recursiveBottom(x+1, y, currentColor);
            }
        }
    }
    
    public void recursiveTop(int x, int y, Color prevColor) {
        if(x >= 0) {
            if(prevColor!=white && prevColor!=black) {
                System.out.println("Stop here top");
            } else {
                Color currentColor = buttons[x][y].getBackground();
                buttons[x][y].setBackground(prevColor);
                prevX=x;
                recursiveBottom(x-1, y, currentColor);
            }
        }
    }
    
    class ButtonListener implements ActionListener {
        private int x, y;
        public ButtonListener(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            //System.out.println("("+prevX+","+prevY+")->"+"("+x+","+y+")");
            if(prevX == null && prevY == null) {
                //  the next move havent chosen yet
                    prevX=x;
                    prevY=y;
            } else if (isDifferent() && (y-prevY==1 && prevX==x)) {
                    changeBack();
                    recursiveRight(x, y+1, prevColor);
                    setPrev();
                    
            } else if (isDifferent() && (prevY-y==1 && prevX==x)) {
                    changeBack();
                    recursiveLeft(x, y-1, prevColor);
                    setPrev();
                    
            } else if (isDifferent() && (x-prevX==1 && prevY==y)) {
                    changeBack();
                    recursiveBottom(x+1, y, prevColor);
                    setPrev();
                    
            } else if (isDifferent() && (prevX-x==1 && prevY==y)) {
                    changeBack();
                    recursiveTop(x-1, y, prevColor);
                    setPrev();
                    
            } 
//            else if(calcTurn()==buttons[prevX][prevY].getBackground()) {
//            }
            else {
                JOptionPane.showMessageDialog(matrixPanel, "Move is invalid, try again!", "Alert!", JOptionPane.PLAIN_MESSAGE);
                setPrev(); turn--;
            }
            refresh();
        }
        
        public void setPrev() {
            prevX=null;
            prevY=null;
            turn++;
        }
        
        public void changeBack() {
            if(turnColor()!=buttons[prevX][prevY].getBackground()) {
                JOptionPane.showMessageDialog(matrixPanel, "Not your turn," + ((turnColor()==Color.WHITE) ? "white" : "black") + " player should move try again!", "Alert!", JOptionPane.PLAIN_MESSAGE);
            } else {
            prevColor = buttons[x][y].getBackground();
            buttons[x][y].setBackground(buttons[prevX][prevY].getBackground());
            buttons[prevX][prevY].setBackground(null);
            }
        }
        
        public boolean isDifferent() {
            return (prevX != x || y != prevY) && (buttons[x][y].getBackground() != buttons[prevX][prevY].getBackground());
        }
    }
    
}

