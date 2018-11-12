package com.pevs;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.Method;
import java.util.regex.Pattern;

public class AppViewModel implements ActionListener, DocumentListener {
    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        var command = actionEvent.getActionCommand();
        try {
            Method action = AppViewModel.class.getDeclaredMethod(command);
            action.setAccessible(true);
            action.invoke(this);
        } catch (Exception e) {
            showError(e);
        }
    }

    @Override
    public void insertUpdate(DocumentEvent documentEvent) { updateSearchTerm(documentEvent); }
    @Override
    public void removeUpdate(DocumentEvent documentEvent) { updateSearchTerm(documentEvent); }
    @Override
    public void changedUpdate(DocumentEvent documentEvent) { updateSearchTerm(documentEvent); }

    private void updateSearchTerm(DocumentEvent documentEvent) {
        var doc = documentEvent.getDocument();
        try {
            searchTerm = doc.getText(doc.getStartPosition().getOffset(), doc.getEndPosition().getOffset());
        } catch (Exception e) {
            searchTerm = "";
        }
    }

    private void showError(Exception e) {
        JOptionPane.showMessageDialog(null, e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
    }


    /*  Properties  */
    private String searchTerm = "";
    private ResultView resultView = new ResultView();
    /*  Actions  */
    private void exitAction() {
        System.exit(0);
    }

    private void actionAction() {
        if (searchTerm.equals("")) {
            showError(new Exception("No Input!"));
            return;
        }
        if (!Pattern.compile("^[\\w|,|.|?|!|\\s]+$").matcher(searchTerm).find()) {
            showError(new Exception("Invalid Input, please use only alphabet characters, numbers, spaces and ?!.,"));
            return;
        }

        try {
            resultView.setResult(JsonToHtmlDto.convert(Api.getSong(searchTerm)));
            if (resultView.isVisible()) resultView.requestFocus();
            else resultView.setVisible(true);
        } catch (Exception e) {
            showError(e);
        }
    }
}
