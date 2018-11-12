package com.pevs;

public interface CreditCard {
    void zistiKredit();
    void vykonajPlatbu(int amount);
    void uhradKredit(int amount);

    String getNumber();
    String getCvc();
    int getLimit();
}
