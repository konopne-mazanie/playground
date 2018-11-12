from random import randint, choice


def play(size, printing=True):
    position = 1
    money = 500
    round = 0
    throw = 0

    if printing is True:
        print_game(position, size, throw, round, money)

    while position != size:
        throw = throw_dice()
        position = (position+throw)
        while position > size:
            position -= size
            money += 200
        if position == size:
            money += 200

        if (position % 3) == 0:
            money += increase_money()
        if (position % 5) == 0:
            money += decrease_money()

        round += 1
        if printing is True:
            print_game(position, size, throw, round, money)

    return(round, money)


def print_game(position, size, throw, round, money):
    print("Position: " + str(position) + " Throw: " + str(throw) + " Round: " + str(round) + " Money: " + str(money) + " Size: " + str(size), end=" :: ")

    for pos in range(1, size+1):
        if pos == position:
            print(">", end="")
        elif pos == size:
            print("F", end="")
        elif pos == 1:
            print("S", end="")
        else:
            print(".", end="")
    print("")


def throw_dice():
    throw = randint(1, 6)
    if throw == 6:
        return(throw+throw_dice())
    return throw


def increase_money():
    def genmp(poc, prv):
        for i in range(poc):
            mprovkov.append(prv)

    mprovkov = []
    genmp(5, 0)
    genmp(35, 250)
    genmp(30, 400)
    genmp(20, 500)
    genmp(10, 1000)

    return(choice(mprovkov))


def decrease_money():
    def genmp(poc, prv):
        for i in range(poc):
            mprovkov.append(prv)

    mprovkov = []
    genmp(10, 0)
    genmp(20, -50)
    genmp(35, -100)
    genmp(30, -250)
    genmp(5, -400)

    return(choice(mprovkov))


def analyze_game(repeat, size):
    round = 0
    money = 0
    for i in range(repeat):
        game = play(size, printing=False)
        round += game[0]
        money += game[1]

    print("Averege number of rounds: " + str(int(round/repeat)))
    print("Average number of money: " + str(int(money/repeat)))

play(3)
