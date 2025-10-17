package SnakeGame;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

public class Main {
    private static JMenuItem scoreboardMenuItem = new JMenuItem("Scoreboard");
    private static JMenuItem restartMenuItem = new JMenuItem("Restart");
    private static JFrame frame = new JFrame();
    private static Gameplay gameplay;
    
    
    public static void main(String[] args) throws SQLException {
        gameplay = new Gameplay();
        frame.setTitle("Snake 1.0.0");
        frame.setBounds(10, 10, 905, 720);
        frame.setBackground(Color.WHITE);
        frame.setResizable(false);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(gameplay);
        
        JMenuBar menuBar = new JMenuBar();
        frame.setJMenuBar(menuBar);
        JMenu gameMenu = new JMenu("Menu");
        menuBar.add(gameMenu);
        
        
        gameMenu.add(scoreboardMenuItem);
        scoreboardMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                // show scoreboard
                gameplay.showScoreboard();
            }
        });
        
        
        gameMenu.add(restartMenuItem);
        restartMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                gameplay.restart();
            }
        });
    }
}
