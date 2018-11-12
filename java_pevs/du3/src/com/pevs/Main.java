package com.pevs;

public class Main {

    public static void main(String[] args) {
        var mainViewModel = new AppViewModel();
        var mainView = new AppView(mainViewModel);
        mainView.setVisible(true);
    }
}
