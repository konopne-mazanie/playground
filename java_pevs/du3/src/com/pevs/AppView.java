package com.pevs;

import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;

public class AppView extends JFrame {
    private JPanel contentPanel = new JPanel(new BorderLayout());
    private final String TAB_HTML = "&nbsp;&nbsp;&nbsp;&nbsp;";
    private JLabel txtAreaLabel = new JLabel("<html>" + TAB_HTML + "Type part of<br><br>" + TAB_HTML + TAB_HTML +
            "Song Lyrics<br><br>" + TAB_HTML + TAB_HTML
            + "Artist Name<br><br>" + TAB_HTML + TAB_HTML
            + "Song Name" + TAB_HTML + TAB_HTML + "<html>");
    private JTextArea txtArea = new JTextArea();
    private JScrollPane txtAreaScroll;

    private JPanel bottomPanel = new JPanel(new BorderLayout()); //pin toolbar to the bottom
    private JPanel bottomInnerPanel = new JPanel(new FlowLayout()); //pin toolbar to the right, container
    private JButton exitButton  = new JButton("Exit");
    private JButton actionButton = new JButton("Find It!");
    private AppViewModel viewModel;

    public AppView(AppViewModel viewModel){
        setTitle("Find my Song");
        setSize(800,350);
        setLayout(new BorderLayout());
        setResizable(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        this.viewModel = viewModel;
        initComponents();
    }

    private void initComponents() {
        //layout
        bottomInnerPanel.add(exitButton);
        bottomInnerPanel.add(actionButton);
        bottomPanel.add(bottomInnerPanel, BorderLayout.EAST);
        contentPanel.setBorder(ViewCommon.insetsBorderFactory());
        txtAreaScroll = new JScrollPane(txtArea);
        contentPanel.add(txtAreaLabel, BorderLayout.WEST);
        contentPanel.add(txtAreaScroll, BorderLayout.CENTER);
        contentPanel.add(bottomPanel, BorderLayout.SOUTH);
        add(contentPanel, BorderLayout.NORTH);
        setContentPane(contentPanel);
        //colors
        contentPanel.setBackground(ViewCommon.windowBackground);
        bottomPanel.setBackground(ViewCommon.windowBackground);
        bottomInnerPanel.setBackground(ViewCommon.windowBackground);
        txtAreaScroll.setBackground(ViewCommon.windowBackground);
        txtAreaLabel.setForeground(new Color(255,255,255));
        txtArea.setBackground(ViewCommon.windowBackground);
        txtArea.setForeground(new Color(255,255,255));
        txtArea.setCaretColor(new Color(255,255,255));
        txtAreaScroll.setBorder(BorderFactory.createLineBorder(new Color(255, 117, 26), 2, true));
        //set actions so viewModel class can execute them
        exitButton.addActionListener(viewModel);
        exitButton.setActionCommand("exitAction");
        actionButton.addActionListener(viewModel);
        actionButton.setActionCommand("actionAction");
        txtArea.getDocument().addDocumentListener(viewModel);
        txtArea.requestFocus();
    }
}
