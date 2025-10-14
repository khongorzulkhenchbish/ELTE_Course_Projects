package SnakeGame;

import java.awt.Image;
import javax.swing.ImageIcon;


public class gameImages {

    private Image menuImage, diedImage, backgroundImage, titleImage;

    public gameImages() {
        menuImage = new ImageIcon(getClass().getResource("Assets/menu.png")).getImage();
        diedImage = new ImageIcon(getClass().getResource("Assets/diedscreen.png")).getImage();

    }

    public Image getMenuImage() {
        return menuImage;
    }


    public Image getDiedImage() {
        return diedImage;
    }


    public Image getBackgroundImage() {
        return backgroundImage;
    }


    public Image getTitleImage() {
        return titleImage;
    }


    
}
