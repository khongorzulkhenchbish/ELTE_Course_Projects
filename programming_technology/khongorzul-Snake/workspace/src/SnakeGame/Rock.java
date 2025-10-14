/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package SnakeGame;

import java.awt.Image;
import javax.swing.ImageIcon;

/**
 *
 * @author hongorzul
 */
public class Rock {

    private int xposRock;
    private int yposRock;
    private Image rockImage;

    public Rock() {
        rockImage = new ImageIcon(getClass().getResource("Assets/yellow.png")).getImage();
    }

    public int getXposRock() {
        return xposRock;
    }

    public void setXposRock(int xposRock) {
        this.xposRock = xposRock;
    }

    public int getYposRock() {
        return yposRock;
    }

    public void setYposRock(int yposRock) {
        this.yposRock = yposRock;
    }

    public Image getRockImage() {
        return rockImage;
    }

    public void setRockImage(Image rockImage) {
        this.rockImage = rockImage;
    }
}
