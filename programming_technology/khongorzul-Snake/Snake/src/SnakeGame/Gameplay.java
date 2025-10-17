/*
 * Copyright 20019 (C) Jens Maes
 * 
 * Created on : 20/05/2019
 * Author     : Jens Maes
 *
*/
package SnakeGame;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.Timer;

/**
 *
 * @author Jens
 */
public class Gameplay extends JPanel implements KeyListener, ActionListener {
    
    private Random rand = new Random();
    private Snake s = new Snake();
    private Apple e = new Apple();
    private ArrayList<Rock> rocks = new ArrayList();
    private gameImages gi = new gameImages();
    private HighScores highScores = new HighScores(10);
    private boolean isHitLevel;
    private long startTime;
    private int level = 1;
    
    private int score = 0;
    private Timer timer;
    private int delay = 300;
    private int savedDelay;

    public Gameplay() throws SQLException {
        //KeyListener & Timer
        addKeyListener(this);
        setFocusable(true);
        setFocusTraversalKeysEnabled(false);
        
        init();
        initTimer(delay);
    }

    private void initTimer(int delay) {
        timer = new Timer(delay, this);
        timer.start();
    }

    // When we start the game, or die, we call the init function to put everything back to its starting position. 
    private void init() {
        s = new Snake();
        this.isHitLevel = false;
        score = 0;
        
        
        level = Integer.parseInt(JOptionPane.showInputDialog("Which level would you like to play? [1-10]"));
        int num_of_rocks = level*3;
        
        // randomly put the rocks
        rocks = new ArrayList();
        for(int i = 0; i < num_of_rocks; ++i) {
            Rock r = new Rock();
            r.setXposRock(25 + (rand.nextInt(34) * 25));
            r.setYposRock(75 + (rand.nextInt(23) * 25));
            rocks.add(r);
        }
        // randomly put thr food
        e = new Apple();
        e.setXposApple(25 + (rand.nextInt(34) * 25));
        e.setYposApple(75 + (rand.nextInt(23) * 25));
        //if(s.isMoves()) startTime = System.currentTimeMillis();
       
    }

    public long elapsedTime() {
        return System.currentTimeMillis() - startTime;
    }
    
    // it is called on every move of the snake
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.fillRect(0,0, getParent().getWidth(), getParent().getHeight());
        // we draw the border of the header
        g.setColor(Color.WHITE);
        g.drawRect(24, 0, 851, 65);
        // sign the header
        g.drawImage(gi.getTitleImage(), 25, 11, null);
        // drawing background
        g.drawRect(24, 74, 851, 576);
        g.drawImage(gi.getBackgroundImage(), 25, 75, null);
        //g.fillRect(25, 75, 850, 575);
        //draw the beginning of the snake
        g.drawImage(s.getRightMouth(), s.getSnakeXLength(0), s.getSnakeYLength(0), null);
        // draw the menu image if we are not moving yet
        if (!s.isMoves()) {
            g.drawImage(gi.getMenuImage(), 25, 100, null);
        }
        s.paintSnake(g);
        
        if (e.getXposApple() == s.getSnakeXLength(0) && e.getYposApple() == s.getSnakeYLength(0)) {
            // Eating the food
            score++;
            s.setLengthOfSnake(s.getLengthOfSnake() + 1);
            
            // Drawing Food on the sand randomly each time paintComponent is called.
            e.setXposApple(25 + (rand.nextInt(34) * 25));
            e.setYposApple(75 + (rand.nextInt(23) * 25));
            
            //speed logic
//            if (score % 10 == 0 && delay > 50) {
//                delay -= 20;
//                timer.stop();
//                initTimer(delay);
//            }
        }
        
        // Food will be changed each drawing
        g.drawImage(e.getAppleImage(), e.getXposApple(), e.getYposApple(), null);
        
        // Rocks will be at the same position
        for(Rock r : rocks) {
            g.drawImage(r.getRockImage(), r.getXposRock(), r.getYposRock(), null);
        }
        
        /* 
        check if the snake collides with itself
        check if the snake hits the wall 
        check if the snake hits the rock
        then reset the timer and draw an image "you died"
        */
        for (int i = 1; i < s.getLengthOfSnake(); i++) {
            if (isHitLevel || 
                isHitRock(s.getSnakeXLength(0), s.getSnakeYLength(0)) || 
                (s.getSnakeXLength(0) == s.getSnakeXLength(i) && 
                 s.getSnakeYLength(0) == s.getSnakeYLength(i))) 
            {
                s.setDead(true);            
                g.drawImage(gi.getDiedImage(), 25,50, null);
                
                // no idea
                delay = 300;
                timer.stop();
                initTimer(delay);
            }
        }
        
        
        // Drawing the score and time
        g.setColor(Color.white);
        g.setFont(new Font("", Font.PLAIN, 20));
        
        if(s.isMoves()) {
            long elapsedSeconds = elapsedTime() / 1000;
            long secondsDisplay = elapsedSeconds % 60;
            long elapsedMinutes = elapsedSeconds / 60;
            g.drawString("Score: "+score+", Time "+elapsedMinutes+":"+secondsDisplay,  100, 45);
        }
        else {
            g.drawString("Score: "+score+", Time 0:0",  100, 45);
        }
        g.dispose();
    }
    
    
    public boolean isHitRock(int x, int y) {
        for(Rock rock : rocks) {
            if(rock.getXposRock()==x && rock.getYposRock()==y) {
                return true;
            }
        }
        return false;
    }

    @Override
    public void keyTyped(KeyEvent e) {

    }

    @Override
    public void keyPressed(KeyEvent e) {

        if (!s.isDead()) {
            if (e.getKeyCode() == KeyEvent.VK_RIGHT && !s.isLeft()) {
                s.setRight(true);
                s.setUp(false);
                s.setDown(false);
            } else if (e.getKeyCode() == KeyEvent.VK_LEFT && !s.isRight()) {
                s.setLeft(true);
                s.setUp(false);
                s.setDown(false);
            } else if (e.getKeyCode() == KeyEvent.VK_UP && !s.isDown()) {
                s.setRight(false);
                s.setUp(true);
                s.setLeft(false);
            } else if (e.getKeyCode() == KeyEvent.VK_DOWN && !s.isUp()) {
                s.setRight(false);
                s.setLeft(false);
                s.setDown(true);
            }
        } 
//        else {
//            if (e.getKeyCode() == KeyEvent.VK_R) {
//                
//                //pop up shows and takes the user name and score
//                
//            }
//        }

//        if (!s.isDead()) {
//            if (e.getKeyCode() == KeyEvent.VK_SPACE) {
//                savedDelay = delay;
//                delay = 50;
//                timer.stop();
//                initTimer(delay);
//                
//            }
//        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
        if (!s.isDead()) {
            if (e.getKeyCode() == KeyEvent.VK_SPACE) {
                //still no idea
                delay = savedDelay;
                timer.stop();
                initTimer(delay);
            }
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (s.isMoves() && !s.isDead()) {
            if (s.isRight()) {
                for (int i = s.getLengthOfSnake() - 1; i >= 0; i--) {
                    s.setSnakeYLength(i + 1, s.getSnakeYLength(i));
                }
                for (int i = s.getLengthOfSnake(); i >= 0; i--) {
                    if (i == 0) {
                        s.setSnakeXLength(i, s.getSnakeXLength(i) + 25);
                    } else {
                        s.setSnakeXLength(i, s.getSnakeXLength(i - 1));
                    }
                    if (s.getSnakeXLength(i) > 850) {
                        //die
                        this.isHitLevel = true;
//                        s.setSnakeXLength(i, 25);
                    }
                }

            } else if (s.isLeft()) {
                for (int i = s.getLengthOfSnake() - 1; i >= 0; i--) {
                    s.setSnakeYLength(i + 1, s.getSnakeYLength(i));
                }
                for (int i = s.getLengthOfSnake(); i >= 0; i--) {
                    if (i == 0) {
                        s.setSnakeXLength(i, s.getSnakeXLength(i) - 25);
                    } else {
                        s.setSnakeXLength(i, s.getSnakeXLength(i - 1));
                    }
                    if (s.getSnakeXLength(i) < 25) {
                        //die
                        this.isHitLevel = true;
                        //s.setSnakeXLength(i, 850);
                    }
                }

            } else if (s.isUp()) {
                for (int i = s.getLengthOfSnake() - 1; i >= 0; i--) {
                    s.setSnakeXLength(i + 1, s.getSnakeXLength(i));
                }
                for (int i = s.getLengthOfSnake(); i >= 0; i--) {
                    if (i == 0) {
                        s.setSnakeYLength(i, s.getSnakeYLength(i) - 25);
                    } else {
                        s.setSnakeYLength(i, s.getSnakeYLength(i - 1));
                    }
                    if (s.getSnakeYLength(i) < 75) {
                        //die
                        this.isHitLevel = true;
                        //s.setSnakeYLength(i, 625);
                    }
                }

            } else if (s.isDown()) {
                for (int i = s.getLengthOfSnake() - 1; i >= 0; i--) {
                    s.setSnakeXLength(i + 1, s.getSnakeXLength(i));
                }
                for (int i = s.getLengthOfSnake(); i >= 0; i--) {
                    if (i == 0) {
                        s.setSnakeYLength(i, s.getSnakeYLength(i) + 25);
                    } else {
                        s.setSnakeYLength(i, s.getSnakeYLength(i - 1));
                    }
                    if (s.getSnakeYLength(i) > 625) {
                        //die
                        this.isHitLevel = true;
                        //s.setSnakeYLength(i, 75);
                    }
                }
            }
        } else if (s.isLeft() | s.isRight() | s.isUp() | s.isDown()) {
            s.setMoves(true);
            startTime = System.currentTimeMillis();
        }
        repaint();
    }

    void showScoreboard() {
        String message = new String();
        try {
            HighScores hs = new HighScores(10);
            ArrayList<HighScore> scoreboard = hs.getHighScores();
            for(HighScore score : scoreboard) {
                message += score.toString();
            }
            JFrame frame = new JFrame();
            JOptionPane.showMessageDialog(frame, message);
        } catch (SQLException ex) {
            Logger.getLogger(Gameplay.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    void restart() {
        String name = (String)JOptionPane.showInputDialog("Enter username: ");
                try {
                    highScores.putHighScore(name, score);
                    System.out.println(score);
                } catch (SQLException ex) {
                    Logger.getLogger(Gameplay.class.getName()).log(Level.SEVERE, null, ex);
        }
        init();
    }
}
