package colorclicker;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

/**
 *
 * @author pinter
 */
public class ColorClickerGUI {
    private JFrame frame;
    private MatrixGUI matrixGUI;
    private final int BOARD_SIZE=3;

    public ColorClickerGUI() throws FileNotFoundException, EmptyFileException {
        frame = new JFrame("Pebble");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        matrixGUI = new MatrixGUI(BOARD_SIZE);
        frame.getContentPane().add(matrixGUI.getMatrixPanel(), BorderLayout.CENTER);
        frame.getContentPane().add(matrixGUI.getTurnLabel(), BorderLayout.SOUTH);
        
        JMenuBar menuBar = new JMenuBar();
        frame.setJMenuBar(menuBar);
        JMenu gameMenu = new JMenu("Game");
        menuBar.add(gameMenu);
        JMenu newMenu = new JMenu("Change board");
        gameMenu.add(newMenu);
        int[] boardSizes = new int[]{3,4,6};
        for (int boardSize : boardSizes) {
            JMenuItem sizeMenuItem = new JMenuItem(boardSize + "x" + boardSize);
            newMenu.add(sizeMenuItem);
            sizeMenuItem.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    frame.getContentPane().remove(matrixGUI.getMatrixPanel());
                    frame.getContentPane().remove(matrixGUI.getTurnLabel());
                    matrixGUI = new MatrixGUI(boardSize);
                    frame.getContentPane().add(matrixGUI.getMatrixPanel(),
                            BorderLayout.CENTER);
                    frame.getContentPane().add(matrixGUI.getTurnLabel(),
                            BorderLayout.SOUTH);
                    frame.pack();
                }
            });
        }
        
        JMenuItem exitMenuItem = new JMenuItem("Exit");
        gameMenu.add(exitMenuItem);
        exitMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                System.exit(0);
            }
        });

        frame.setResizable(false);
        frame.pack();
        frame.setVisible(true);
    }
}
