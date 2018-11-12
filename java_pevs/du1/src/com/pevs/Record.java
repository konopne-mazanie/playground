package com.pevs;

public class Record {
    String name;
    String number;
    String streetName;
    String buildingID;
    String flatID;
    String balance;

    public Record() {}
    public Record(String name, String number, String streetName, String buildingID, String flatID, String balance) {
        this.name = name;
        this.number = number;
        this.streetName = streetName;
        this.buildingID = buildingID;
        this.flatID = flatID;
        this.balance = balance;
    }
}
