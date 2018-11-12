package com.pevs;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

public class Main {

    public static String randomString(int n) {
        return randomString(n, false);
    }

    public static String randomString(int n, boolean numeric)
    {
        String base = "0123456789";
        if (!numeric) base += "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvxyz";
        StringBuilder sb = new StringBuilder(n);
        for (int i = 0; i < n; i++) {
            int index = (int)(base.length() * Math.random());
            sb.append(base.charAt(index));
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        boolean generate = false;
        boolean aboveZero = false;
        StringBuilder aboveZeroResult = new StringBuilder();
        boolean underZero = false;
        StringBuilder underZeroResult = new StringBuilder();
        boolean mobile = false;
        StringBuilder mobileResult = new StringBuilder();
        String file = null;

	    for (String arg : args) {
	        if (arg.equals("d")) underZero = true;
	        else if (arg.equals("p")) aboveZero = true;
	        else if (arg.equals("m")) mobile = true;
            else if (arg.equals("g")) generate = true;
	        else file = arg;
        }

	    if (file == null) {
	        System.out.println("No File specified");
	        return;
        }

	    if (generate) {
	        int count = Integer.parseInt(file);
            try {
                FileWriter out = new FileWriter("out.csv");
                for (int i = 0; i < count; i++) {
                    Record rec = new Record();
                    rec.name = randomString(5) + randomString(5);
                    rec.number = randomString(10, true);
                    rec.streetName = randomString(5);
                    rec.buildingID = randomString(2, true);
                    rec.flatID = randomString(1, true);
                    rec.balance = Integer.toString(new Random().nextInt((500 + 100) + 1) - 100);
                    out.write(String.format("%s,%s,%s,%s,%s,%s", rec.name,rec.number,rec.streetName,rec.buildingID,rec.flatID,rec.balance) + System.getProperty("line.separator"));
                }
                out.close();
            }
	        catch (IOException e) {
	            System.out.println("Unable to write output");
            }
	        return;
        }

        try {
            Scanner scanner = new Scanner(new File(file));
            while (scanner.hasNextLine()) {
                String rawRec = scanner.nextLine();
                String[] parsed = rawRec.split(",");
                if (parsed.length < 6) {
                    System.out.println("Invalid record: " + rawRec);
                    continue;
                }

                Record record = new Record(parsed[0], parsed[1], parsed[2], parsed[3], parsed[4], parsed[5]);
                String formated = String.format("%20s     %10s     %20s     %3s     %3s     %5s\n", record.name, record.number, record.streetName, record.buildingID, record.flatID, record.balance);
                if (underZero && (Integer.parseInt(record.balance) < 0)) underZeroResult.append(formated);
                if (aboveZero && (Integer.parseInt(record.balance) > 0)) aboveZeroResult.append(formated);
                if (mobile && (record.number.charAt(0) == '0') && (record.number.charAt(1) == '9')) mobileResult.append(formated);
                if (!aboveZero && !underZero && !mobile) System.out.println(formated);
            }
            scanner.close();
        } catch (Exception e) {
            System.out.println("Error while reading Input File" + e.getMessage());
        }

        if (aboveZero) {
            System.out.println("V Preplatku: ");
            System.out.println(aboveZeroResult.toString());
        }

        if (underZero) {
            System.out.println("V Dlhu: ");
            System.out.println(underZeroResult.toString());
        }

        if (mobile) {
            System.out.println("S mobilom: ");
            System.out.println(mobileResult.toString());
        }

    }
}
