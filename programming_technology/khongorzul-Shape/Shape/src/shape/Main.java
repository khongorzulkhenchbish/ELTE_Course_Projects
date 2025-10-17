/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package shape;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author hongorzul
 */
public class Main {
    //Collecion
    private static int number_of_shapes;
    private static final List<Shape> shapeCollection = new ArrayList();
    private static BoundingBox boundingBox = new BoundingBox();
    
    public static void main(String[] args) throws FileNotFoundException, EmptyFileException {
        // TODO code application logic here
        // read the input line by line
        readShapeCollection();
        printShapeCollection();
        findBoundingBox();
        printResult();
        
        }
    
    public static void readShapeCollection() throws FileNotFoundException, EmptyFileException {
        File input = new File("empty-input.txt");
        Scanner sc = new Scanner(input);
        
        try {
            number_of_shapes = Integer.parseInt(sc.nextLine());

            for(int i = 0; i < number_of_shapes; i++) {
                String[] line = sc.nextLine().split(" ");
                String type = (line[0]);

                Point p = new Point(Integer.parseInt(line[1]), Integer.parseInt(line[2]));
                int r = Integer.parseInt(line[3]);


                if("C".equals(type)) {
                    Circle circle = new Circle(p, r);
                    shapeCollection.add(circle);
                } 
                if("T".equals(type)) {
                    Triangle triangle = new Triangle(p, r);
                    shapeCollection.add(triangle);
                } 
                if("S".equals(type)) {
                    Square square = new Square(p, r);
                    shapeCollection.add(square);
                } 
                if("H".equals(type)) {
                    Hexagon hexagon = new Hexagon(p, r);
                    shapeCollection.add(hexagon);
                } 
            }
        } catch(Exception e) {
            throw new EmptyFileException("File is empty!");
        }
    }
    
    
    public static void printShapeCollection() {
        
        for (int i = 0; i < shapeCollection.size(); i++) {
          
            System.out.println(shapeCollection.get(i));
            
        }
    }
    
    public static void findBoundingBox() {
     
        if(number_of_shapes>0) {
            
            System.out.println(shapeCollection.size());
            boundingBox.setLeftBottom(shapeCollection.get(0).calcLeftBottom());    
            boundingBox.setLeftTop(shapeCollection.get(0).calcLeftTop());
            boundingBox.setRightBottom(shapeCollection.get(0).calcRightBottom());
            boundingBox.setRightTop(shapeCollection.get(0).calcRightTop());


            for(int i=1; i<number_of_shapes; i++) {

                Shape current = shapeCollection.get(i);
                int x, y, a, b;
                a = Math.abs(boundingBox.getLeftBottom().x);
                b = Math.abs(boundingBox.getLeftBottom().y);
                x = Math.abs(current.calcLeftBottom().x);
                y = Math.abs(current.calcLeftBottom().y);


                boundingBox.setLeftBottom(new Point(-Math.max(a,x), -Math.max(b,y)));

                a = Math.abs(boundingBox.getLeftTop().x);
                b = Math.abs(boundingBox.getLeftTop().y);
                x = Math.abs(current.calcLeftTop().x);
                y = Math.abs(current.calcLeftTop().y);

                boundingBox.setLeftTop(new Point(-Math.max(a,x), Math.max(b,y)));

                a = Math.abs(boundingBox.getRightBottom().x);
                b = Math.abs(boundingBox.getRightBottom().y);
                x = Math.abs(current.calcRightBottom().x);
                y = Math.abs(current.calcRightBottom().y);

                boundingBox.setRightBottom(new Point(Math.max(a,x), -Math.max(b,y)));

                a = Math.abs(boundingBox.getRightTop().x);
                b = Math.abs(boundingBox.getRightTop().y);
                x = Math.abs(current.calcRightTop().x);
                y = Math.abs(current.calcRightTop().y);

                boundingBox.setRightTop(new Point(Math.max(a,x), Math.max(b,y)));

            }
        }
    }
    
    public static void printResult() {
        
        System.out.println("left bottom: ("+boundingBox.getLeftBottom().x+", "+boundingBox.getLeftBottom().y+")");
        System.out.println("right bottom: ("+boundingBox.getRightBottom().x+", "+boundingBox.getRightBottom().y+")");
        System.out.println("left top: ("+boundingBox.getLeftTop().x+", "+boundingBox.getLeftTop().y+")");
        System.out.println("right top: ("+boundingBox.getRightTop().x+", "+boundingBox.getRightTop().y+")");
        
    }
}

