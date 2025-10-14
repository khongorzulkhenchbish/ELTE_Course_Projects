package SnakeGame;

import java.awt.Graphics;
import java.awt.Image;
import javax.swing.ImageIcon;

public class Snake {

    private int[] snakeXLength = new int[750];
    private int[] snakeYLength = new int[750];
    private Image rightMouth, leftMouth, downMouth, upMouth, snakeImage;
    private boolean left = false, right = false, up = false, down = false;
    private int lengthOfSnake;
    private boolean moves;
    private boolean dead;

    public Snake() {
        lengthOfSnake = 2;
        
        snakeXLength[2] = 50;
        snakeXLength[1] = 75;
        snakeXLength[0] = 100;
        snakeYLength[2] = 100;
        snakeYLength[1] = 100;
        snakeYLength[0] = 100;
        
        dead = false;
        moves = false;
        left = false;
        right = false;
        up = false;
        down = false;
        
        snakeImage = new ImageIcon(getClass().getResource("Assets/snakeimage.png")).getImage();
        rightMouth = new ImageIcon(getClass().getResource("Assets/rightmouth.png")).getImage();
        leftMouth = new ImageIcon(getClass().getResource("Assets/leftmouth.png")).getImage();
        upMouth = new ImageIcon(getClass().getResource("Assets/upmouth.png")).getImage();
        downMouth = new ImageIcon(getClass().getResource("Assets/downmouth.png")).getImage();
    }
    
    public void paintSnake(Graphics g) {
        for (int i = 0; i < getLengthOfSnake(); i++) {
            if (i == 0) {
                if (isRight()) {
                    g.drawImage(getRightMouth(), getSnakeXLength(i), getSnakeYLength(i), null);
                } else if (isLeft()) {
                    g.drawImage(getLeftMouth(), getSnakeXLength(i), getSnakeYLength(i), null);
                } else if (isDown()) {
                    g.drawImage(getDownMouth(), getSnakeXLength(i), getSnakeYLength(i), null);
                } else if (isUp()) {
                    g.drawImage(getUpMouth(), getSnakeXLength(i), getSnakeYLength(i), null);
                }
            } else {
                g.drawImage(getSnakeImage(), getSnakeXLength(i), getSnakeYLength(i), null);
            }
        }
    }
    
    public void checkDead(Graphics g) {}

    public int getSnakeXLength(int index) {
        return snakeXLength[index];
    }

    public int getSnakeYLength(int index) {
        return snakeYLength[index];
    }

    public Image getRightMouth() {
        return rightMouth;
    }

    public Image getLeftMouth() {
        return leftMouth;
    }

    public Image getDownMouth() {
        return downMouth;
    }

    public Image getUpMouth() {
        return upMouth;
    }

    public Image getSnakeImage() {
        return snakeImage;
    }

    public boolean isLeft() {
        return left;
    }

    public boolean isRight() {
        return right;
    }

    public boolean isUp() {
        return up;
    }

    public boolean isDown() {
        return down;
    }

    public int getLengthOfSnake() {
        return lengthOfSnake;
    }

    public boolean isMoves() {
        return moves;
    }

    public boolean isDead() {
        return dead;
    }

    public void setSnakeXLength(int index, int value) {
        this.snakeXLength[index] = value;
    }

    public void setSnakeYLength(int index, int value) {
        this.snakeYLength[index] = value;
    }

    public void setRightMouth(Image rightMouth) {
        this.rightMouth = rightMouth;
    }

    public void setLeftMouth(Image leftMouth) {
        this.leftMouth = leftMouth;
    }

    public void setDownMouth(Image downMouth) {
        this.downMouth = downMouth;
    }

    public void setUpMouth(Image upMouth) {
        this.upMouth = upMouth;
    }

    public void setSnakeImage(Image snakeImage) {
        this.snakeImage = snakeImage;
    }

    public void setLeft(boolean left) {
        this.left = left;
    }

    public void setRight(boolean right) {
        this.right = right;
    }

    public void setUp(boolean up) {
        this.up = up;
    }

    public void setDown(boolean down) {
        this.down = down;
    }

    public void setLengthOfSnake(int lengthOfSnake) {
        this.lengthOfSnake = lengthOfSnake;
    }

    public void setMoves(boolean moves) {
        this.moves = moves;
    }

    public void setDead(boolean dead) {
        this.dead = dead;
    }

}
