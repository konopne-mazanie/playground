package com.pevs;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.function.Consumer;

public class Main {

	private static void forEachLine(String file, Consumer<String[]> function) {
		try {
			var scanner = new Scanner(new File(file));
			while (scanner.hasNextLine()) {
				String line = scanner.nextLine();
				if ((line.length() > 0) && line.charAt(0) != '#') function.accept(line.split(","));
			}
			scanner.close();
		} catch (Exception e) {
			System.out.println("Error while reading File: " + e.getMessage());
		}
	}

    public static void main(String[] args) {
	if (args.length < 1) {
	    System.out.println("No cards file specified");
    }

	var cards = new ArrayList<CreditCard>();
	forEachLine(args[0], (String[] parsed) -> {
		if (parsed.length != 5) {
			System.out.println("Invalid line length:  " + parsed.length);
			return;
		}
		if (parsed[0].equals("g")) cards.add(new GoldCard(parsed[1], parsed[2], parsed[3], Integer.parseInt(parsed[4])));
		else if (parsed[0].equals("b")) cards.add(new BlueCard(parsed[1], parsed[2], parsed[3], Integer.parseInt(parsed[4])));
		else {
			System.out.println("Unknown type of card, " +
					"please extend program of class representing card");
		}
	});

	System.out.println(cards.size() + " cards loaded");

	while (true) {
		System.out.println("Please enter transactions file or type exit: ");
		String input = new Scanner(System.in).nextLine();
		if (input.toLowerCase().equals("exit")) return;
		forEachLine(input, (String[] parsed) -> {
			if (parsed.length != 3) {
				System.out.println("Invalid line length:  " + parsed.length);
				return;
			}
			CreditCard foundCard = null;
			for (CreditCard card : cards) if (card.getNumber().equals(parsed[0])) foundCard = card;
			if (foundCard == null) {
				System.out.println("Unknown card number: " + parsed[0]);
				return;
			}
			if (!foundCard.getCvc().equals(parsed[2])) {
				System.out.println("Failed CVC attempt for: **** **** **** " + foundCard.getNumber().substring(12));
				foundCard.zistiKredit();
				return;
			}
			int amount = Integer.parseInt(parsed[1]);
			if (amount < 0) {
				foundCard.uhradKredit(amount*(-1));
				return;
			}
			if (amount > foundCard.getLimit()) {
				System.out.println("Failed Limit attempt for: **** **** **** " + foundCard.getNumber().substring(12));
				foundCard.zistiKredit();
				return;
			}
			foundCard.vykonajPlatbu(amount);
		});
	}

    }
}
