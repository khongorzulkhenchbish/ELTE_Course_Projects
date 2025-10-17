/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package shape;
/**
 *
 * @author hongorzul
 */

public class Shape {
    private final Point center;
    private final int radius_side_length;
    
    public int getRadiusSideLength() { return radius_side_length; }
    public Point getCenter() { return center; }
    public Point calcLeftTop() { return center; } 
    public Point calcRightTop() { return center; } 
    public Point calcLeftBottom() { return center; } 
    public Point calcRightBottom() { return center; } 
    
    
    public Shape (Point c, int r) {
        this.center = c;
        this.radius_side_length = r;
    }
    
}
