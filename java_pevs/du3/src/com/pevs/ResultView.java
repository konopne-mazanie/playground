package com.pevs;

import javax.swing.*;
import java.awt.*;

public class ResultView extends JFrame {
    private JLabel resTableLb = new JLabel();
    private JScrollPane resTableLbScroll;

    public ResultView(){
        setTitle("Find my Song - Result");
        setLayout(new BorderLayout());
        setResizable(true);
        setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);

        initComponents();
    }

    private void initComponents() {
        //layout
        resTableLbScroll = new JScrollPane(resTableLb);
        resTableLbScroll.setBorder(ViewCommon.insetsBorderFactory());
        add(resTableLbScroll, BorderLayout.CENTER);
        setContentPane(resTableLbScroll);
        //colors
        resTableLbScroll.setBackground(ViewCommon.windowBackground);
        resTableLb.setForeground(new Color(255,255,255));
        resTableLb.setOpaque(true);
        resTableLb.setBackground(ViewCommon.windowBackground);
    }

    public void setResult(String text) {
        resTableLb.setText(text);
        pack(); //sets size according to content
    }
}
