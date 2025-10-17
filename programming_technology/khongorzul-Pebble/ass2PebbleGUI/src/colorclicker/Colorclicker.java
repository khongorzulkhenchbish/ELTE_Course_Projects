package colorclicker;

import java.io.FileNotFoundException;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author pinter
 */
public class Colorclicker {

    /**
     * @param args the command line arguments
     * @throws java.io.FileNotFoundException
     * @throws colorclicker.EmptyFileException
     */
    public static void main(String[] args) throws FileNotFoundException, EmptyFileException {
        ColorClickerGUI gui = new ColorClickerGUI();
    }
    
}
