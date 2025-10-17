/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package shape;

/**
 *
 * @author hongorzul
 */
public class BoundingBox {
    Point leftTop;
    Point rightTop;
    Point leftBottom;
    Point rightBottom;
    
    public BoundingBox() {
        leftTop = new Point(0,0);
        rightTop = new Point(0,0);
        leftBottom = new Point(0,0);
        rightBottom = new Point(0,0);
    }
    
    public Point getLeftTop() { return leftTop; }
    public Point getRightTop() { return rightTop; }
    public Point getLeftBottom() { return leftBottom; }
    public Point getRightBottom() { return rightBottom; }
    
    public void setLeftTop(Point p) { leftTop=p; } 
    public void setRightTop(Point p) { rightTop=p; } 
    public void setLeftBottom(Point p) { leftBottom=p; } 
    public void setRightBottom(Point p) {  rightBottom=p; } 
}
