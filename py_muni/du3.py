import copy
win = ""


def strategy(state, mark):
    bestplace = []
    bestplace.append([])
    bestplace.append(0)
    for i in range(0, len(state)):
        for j in range(0, len(state)):
            if state[i][j] == " ":
                tempstate = copy.deepcopy(state)
                tempstate[i][j] = mark
                tempstate = check_state(tempstate, mark, [i, j])
                if win == mark:
                    return(i, j)
                elif countmark(tempstate, mark) > bestplace[1]:
                    bestplace[1] = countmark(tempstate, mark)
                    bestplace[0] = [i, j]
    return(bestplace[0])


def countmark(state, mark):
    count = 0
    for line in state:
        for place in line:
            if place == mark:
                count += 1
    return(count)


def check_state(state, mark, mcords):
    lenstat = len(state)
    i = mcords[0]
    j = mcords[1]
    state[i] = chech_seq(state[i], mark, lenstat, j)
    reverse = reverse_state(state)
    reverse[j] = chech_seq(reverse[j], mark, lenstat, i)
    state = reverse_state(reverse)
    state = diagonal_state(state, mark, mcords)
    return(state)


def reverse_state(state):
    rev = []
    for i in range(0, len(state)):
        part = []
        for j in range(0, len(state)):
            part.append(state[j][i])
        rev.append(part)
    return(rev)


def diagonal_state(state, mark, mcords):
    lenstat = len(state)
    for i in range(0, len(state)):
        for j in range(0, len(state)):
            m = i
            n = j
            subdiag = []
            subcords = []
            while True:
                try:
                    subdiag.append(state[m][n])
                    subcords.append([m, n])
                    m += 1
                    n += 1
                except IndexError:
                    break
            if len(subdiag) > 2 and (mcords in subcords):
                k = 0
                pos = (mcords[0]-subcords[0][0])
                for place in chech_seq(subdiag, mark, lenstat, pos):
                    state[(subcords[k][0])][(subcords[k][1])] = place
                    k += 1

            m = i
            n = j
            subdiag = []
            subcords = []
            while True:
                try:
                    subdiag.append(state[m][n])
                    subcords.append([m, n])
                    m += 1
                    n -= 1
                except IndexError:
                    break
            if len(subdiag) > 2 and (mcords in subcords):
                k = 0
                pos = (mcords[0]-subcords[0][0])
                for place in chech_seq(subdiag, mark, lenstat, pos):
                    state[(subcords[k][0])][(subcords[k][1])] = place
                    k += 1
    return(state)


def chech_seq(seq, mark, lenstat, mpos):
    global win
    for i in range(mpos, len(seq)-1):
        if seq[i] == " ":
            break
        elif seq[i] == mark:
            for j in range(mpos, i):
                seq[j] = mark
            break
    isempt = False
    for i in range(0, mpos):
        if seq[i] == mark:
            for j in range(i, mpos):
                if seq[j] == " ":
                    isempt = True
            if not isempt:
                for j in range(i, mpos):
                    seq[j] = mark
                break

    if len(seq) == lenstat:
        i = 0
        for place in seq:
            if place == mark:
                i += 1
        if i == lenstat:
            win = mark
    return(seq)


def gen_plan(size):
    plan = []
    for i in range(0, size):
        subp = []
        for j in range(0, size):
            subp.append(" ")
        plan.append(subp)
    return plan


def is_full(state):
    for line in state:
        if " " in line:
            return False
    return True


def print_state(state):
    lenstat = len(state)
    print(" ", end=" ")
    for i in range(0, lenstat):
        print(i, end=" ")
    print()
    for i in range(0, lenstat):
        for j in range(-1, lenstat):
            if j == -1:
                print(i, end=" ")
            else:
                print(state[i][j], end=" ")
        print()


def play(size, human_starts=True):
    global win
    state = gen_plan(size)
    print_state(state)
    while win == "":
        if not human_starts:
            print("My turn")
            nposx, nposy = strategy(state, "O")
            state[nposx][nposy] = "O"
            state = check_state(state, "O", [nposx, nposy])
            print_state(state)
        if win == "O":
            print("You loose.")
            break
        inp = input("""Your turn! Coordinates of new X "x,y": """)
        x = int(inp[0])
        y = int(inp[2:])
        if (x > len(state)-1) or (y > len(state)-1) or (state[x][y] != " "):
            print("What is this ... Type right coordinates!")
            continue
        state[x][y] = "X"
        state = check_state(state, "X", [x, y])
        print_state(state)
        if human_starts:
            print("My turn")
            nposx, nposy = strategy(state, "O")
            state[nposx][nposy] = "O"
            state = check_state(state, "O", [nposx, nposy])
            print_state(state)

        if is_full(state):
            print("Nobody won")
        elif win == "O":
            print("You loose")
        elif win == "X":
            print("You win")
