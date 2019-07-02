import javax.swing.*;
import java.awt.*;

public class Solution {
    public static void main(String[] args) {
        JFrame jFrame = new JFrame(){};
        jFrame.setVisible(true);
        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension dimension = toolkit.getScreenSize();
        jFrame.setBounds(dimension.width/2-250, dimension.height/2 - 250, 500, 500);
        jFrame.setTitle("Программа для изменения типа доступа к ТПА Engel");
    }
}
