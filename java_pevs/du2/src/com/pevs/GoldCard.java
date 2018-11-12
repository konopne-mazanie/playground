package com.pevs;

public class GoldCard extends BlueCard {
    public GoldCard(String cardNumber, String cvc, String owner, int credit) {
        super(cardNumber, cvc, owner, credit);
        changeLimit(5000);
    }

}
