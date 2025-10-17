package SnakeGame;

import java.awt.Image;
import javax.swing.ImageIcon;

/**
 *
 * @author Jens
 */
public class Apple {

    private int xposApple;
    private int yposApple;
    private Image appleImage;

    public Apple() {
        appleImage = new ImageIcon(getClass().getResource("Assets/food.png")).getImage();
    }

    public int getXposApple() {
        return xposApple;
    }

    public void setXposApple(int xposApple) {
        this.xposApple = xposApple;
    }

    public int getYposApple() {
        return yposApple;
    }

    public void setYposApple(int yposApple) {
        this.yposApple = yposApple;
    }

    public Image getAppleImage() {
        return appleImage;
    }

    public void setAppleImage(Image appleImage) {
        this.appleImage = appleImage;
    }
}
