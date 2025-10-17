/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package shape;

/**
 *
 * @author hongorzul
 */
public class Hexagon extends Shape {
    
    public Hexagon(Point c, int r) {
        super(c, r);
    }
    
    @Override
    public Point calcLeftBottom() {
        return new Point(this.getCenter().x-this.getRadiusSideLength(), this.getCenter().y-this.getRadiusSideLength());
    }
    
    @Override
    public Point calcRightBottom() {
        return new Point(this.getCenter().x+this.getRadiusSideLength(), this.getCenter().y+this.getRadiusSideLength());
    }
    
    @Override
    public Point calcLeftTop() {
        return new Point(this.getCenter().x-this.getRadiusSideLength(), this.getCenter().y+this.getRadiusSideLength());
    }
    
    @Override
    public Point calcRightTop() {
        return new Point(this.getCenter().x+this.getRadiusSideLength(), this.getCenter().y+this.getRadiusSideLength());
    }
}
