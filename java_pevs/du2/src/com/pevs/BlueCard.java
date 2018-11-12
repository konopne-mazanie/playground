package com.pevs;

public class BlueCard implements CreditCard {
    private final String cardNumber;
    private final String cvc;
    private int credit;
    private final String owner;
    private int limit = 1000;

    public BlueCard(String cardNumber, String cvc, String owner, int credit) {
        this.cardNumber = cardNumber;
        this.cvc = cvc;
        this.owner = owner;
        this.credit = credit;
    }

    protected void changeLimit(int limit) {
        this.limit = limit;
    }

    public String getNumber() {
        return cardNumber;
    }

    public String getCvc() {
        return cvc;
    }

    public int getLimit() {
        return limit;
    }

    @Override
    public void uhradKredit(int amount) {
        credit+= amount;
        System.out.println("Card number: **** **** **** " + getNumber().substring(12) + " Increasing credit by: " + amount);
        zistiKredit();
    }

    @Override
    public void zistiKredit() {
        System.out.println("Card number: **** **** **** " + getNumber().substring(12) + " Owner: " + owner + " Current Credit: " + credit);
    }

    @Override
    public void vykonajPlatbu(int amount) {
        credit-= amount;
        System.out.println("Card number: **** **** **** " + getNumber().substring(12) + " Decreasing credit by: " + amount);
        zistiKredit();
    }
}
