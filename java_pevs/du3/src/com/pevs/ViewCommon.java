package com.pevs;

import javax.swing.border.Border;
import java.awt.*;

public class ViewCommon {
    public static final Color windowBackground = new Color(42, 42, 42);
    public static Border insetsBorderFactory() {
        return (new Border() { //just creates padding
            @Override
            public void paintBorder(Component component, Graphics graphics, int i, int i1, int i2, int i3) { }
            @Override
            public Insets getBorderInsets(Component component) {
                return new Insets(10,10,10,10);
            }
            @Override
            public boolean isBorderOpaque() {
                return true;
            }
        });
    }
}
