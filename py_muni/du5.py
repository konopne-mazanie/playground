import math
from random import randint
from PIL import Image


class Turtle:
    def __init__(self):
        self.x = 50
        self.y = 50
        self.heading = 0  # in degrees
        self.lines = []  # list of tuple (x1, y1, x2, y2)

    def left(self, angle):
        self.heading -= angle

    def right(self, angle):
        self.heading += angle

    def forward(self, d):
        nx = self.x + d * math.cos(self.heading * math.pi / 180)
        ny = self.y + d * math.sin(self.heading * math.pi / 180)
        self.lines.append((self.x, self.y, nx, ny))
        self.x, self.y = nx, ny

    def turn_to_turtle(self, turtle):
        vec1 = ((turtle.x-self.x), (turtle.y-self.y))
        vec1sz = math.sqrt(((vec1[0])**2 + (vec1[1])**2))
        nx = self.x + vec1sz * math.cos(self.heading * math.pi / 180)
        ny = self.y + vec1sz * math.sin(self.heading * math.pi / 180)
        vec2 = (nx-self.x, ny-self.y)
        ang = math.acos(((vec1[0]*vec2[0])+(vec1[1]*vec2[1]))/((vec1sz)**2))
        if (ang >= 0):
            self.left(ang)
        else:
            self.right(ang)

    def connect_turtles(self, turtle):
        self.lines.append((self.x, self.y, turtle.x, turtle.y))


def save(filename, turtles):
    with open(filename, mode="w") as out:
        out.write("<svg xmlns='http://www.w3.org/2000/svg'>\n")
        for turtle in turtles:
            for line in turtle.lines:
                out.write("<line x1='" + str(line[0]) + "' y1='" + str(line[1]) + "' x2='" + str(line[2]) + "' y2='" + str(line[3]) + "' stroke='black' stroke-width='1'/>" + "\n")
        out.write("</svg>\n")


def draw_svg_image1():
    """
    Vykesli geometricky utvar ktory ma po kazdej strane dalsie utvary,
    okolo toho je dalsi utvar ktory kresli druha korytnacka,
    v hranach sa korytnacky prepajaju.
    """
    turtle1 = Turtle()
    turtle2 = Turtle()
    turtle1.x = 220
    turtle1.y = 310
    turtle2.x = 170
    turtle2.y = 465
    turtle1.connect_turtles(turtle2)
    nang = 360/10
    mang = 360/10
    for i in range(0, 10):
        turtle1.forward(50)
        turtle2.forward(150)
        turtle2.left(36)
        turtle1.connect_turtles(turtle2)
        for i in range(0, 10):
            turtle1.right(mang)
            turtle1.forward(50)
        turtle1.left(nang)
    save("image1.svg", [turtle2, turtle1])


def draw_svg_image2():
    """
    Vykresli nieco ako tie veci co davame na vrch stromceka(hviezdu),
    kreslia korytnacky celkom dve.
    #vianocna_tematika #MoznoBudeBonus
    Co sa tyka tvaru trosku som sa inspiroval netom - prikladmi pre normalne korytnacky,
    ale okopirovane to nie je, resp nikde nenajdes ten isty kod.
    """
    sp1 = Turtle()
    sp1.x = 100
    sp1.y = 100
    sp2 = Turtle()
    sp2.x = 100
    sp2.y = 100

    for i in range(20):
        sp1.forward(i * 10)
        sp2.forward(i * 10)
        sp1.right(144)
        sp2.left(144)

    save("image2.svg", [sp1, sp2])


def transform(image_path):
    """
    Filter spravi z obrazka ciernobiely a potom este prechod, kde prava strana ja tmavsia.
    Obrazok FI s tym vyzera celkom gut.
    """
    im = Image.open(image_path).convert("RGB")
    imout = Image.new("RGB", im.size)

    for i in range(0, im.size[0]):
        for j in range(0, im.size[1]):
            pix = im.getpixel((i, j))
            npix = int((pix[0]+pix[1]+pix[2])/3)
            npix -= i//5
            imout.putpixel((i, j), (npix, npix, npix))
    imout.save(image_path[:-4]+"_modified.png")


def rhymes_with(word, file_path):
    words = {}
    infile = open(file_path, mode="r")
    line = infile.readline()
    line = line.strip()
    line = line[::-1]
    word = word[::-1]
    while line != "":
        if line[0] == word[0]:
            count = 1
            if len(line) < len(word):
                qt = len(line)
            else:
                qt = len(word)
            for i in range(1, qt):
                if line[i] == word[i]:
                    count += 1
            if (words == {}) or (len(words) < 5):
                if count in words.keys():
                    words[count].append(line[::-1])
                else:
                    words[count] = [line[::-1]]
            else:
                replace = False
                for size in words.keys():
                    if count > size:
                        replace = True
                        break
                    elif count == size:
                        words[count].append(line[::-1])
                if replace:
                    words.pop(size)
                    words[count] = [line[::-1]]
        line = infile.readline()
        line = line.strip()
        line = line[::-1]
    outp = []
    i = 0
    for key in sorted(words.keys())[::-1]:
        for wrd in words[key]:
            outp.append(wrd)
            i += 1
            if i == 5:
                break
        if i == 5:
            break
    return outp
