import os


class Folder:
    def __init__(self, name, owner):
        self.name = name
        self.owner = owner
        self.content = []
        self.parent = None

    def __str__(self):
        return ("Folder: " + self.name)

    def setparent(self, parent):
        self.parent = parent
        parent.content.append(self)


class File:
    def __init__(self, name, extension, size):
        self.name = name
        self.extension = extension
        self.size = size
        self.parent = None

    def __str__(self):
        return ("File: " + self.name + "." + self.extension + " (" + str(self.size) + ")")

    def setparent(self, parent):
        self.parent = parent
        parent.content.append(self)


class Group:
    def __init__(self, name):
        self.name = name
        self.files = []

    def __str__(self):
        fnames = []
        for file in self.files:
            fnames.append(file.name)
        return("Group: " + self.name + ": " + str(fnames))

    def addfile(self, item):
        self.files.append(item)


def read_data(filename):
    files = {}
    folders = {}
    groups = {}
    infile = open(filename, mode="r")

    line = infile.readline()
    while line[0] != "#":
        divline = line.split(",")
        fold = Folder(divline[0].strip(), divline[1].strip())
        folders[(fold.name)] = fold
        line = infile.readline()

    line = infile.readline()
    while line[0] != "#":
        divline = line.split(",")
        fil = File(divline[0].strip(), divline[1].strip(), int(divline[2].strip()))
        files[(fil.name)] = fil
        line = infile.readline()

    line = infile.readline()
    while line[0] != "#":
        name1 = line.split("->")[0].strip()
        name2 = line.split("->")[1].strip()
        if name1 in folders:
            folders[name1].setparent(folders[name2])
        else:
            files[name1].setparent(folders[name2])
        line = infile.readline()

    line = infile.readline()
    while line != "":
        divline = line.split(":")
        gname = divline[0].strip()
        groups[gname] = Group(gname)

        divline = divline[1].split(",")
        if divline[0] != "\n":
            for fil in divline:
                groups[gname].addfile(files[fil.strip()])
        line = infile.readline()

    infile.close()
    return (files, folders, groups)


def find_closest_common_folder(file1, file2):
    fold1 = file1.parent
    fold2 = file2.parent

    if fold1 == fold2:
        return fold1

    while True:
        if fold2.parent == fold1:
            return fold1

        if fold1.parent:
            fold1 = fold1.parent
            if fold1 == fold2:
                return fold1
        if fold2.parent:
            fold2 = fold2.parent
            if fold1 == fold2:
                return fold1


def find_groups_all_files_has_same_extension(groups):
    names = []
    ext = []
    for group in groups:
        for fil in group.files:
            if fil.extension not in ext:
                ext.append(fil.extension)
        if not ((len(group.files) != 1) and (len(ext) > 1)):
            names.append(group.name)
        ext = []
    return names


def get_folder_sizes(folder):
    count = 0
    for item in folder.content:
        if type(item) == File:
            count += item.size
        else:
            count += get_folder_sizes(item)
    return(count)


def n_files_being_in_most_groups(groups, files, n):
    focc = {}
    for file in files:
        count = 0
        for group in groups:
            for fil in group.files:
                if fil.name == file.name:
                    count += 1
        if count == 0:
            continue
        focc[file.name] = count
    focc = sorted(focc, key=focc.get)
    return focc[:n]


def getpath(item):
    """
    Vstup je objekt suboru/priecinka.
    Rekurzivne najde a vrati cestu k suboru/adresaru
    v tvare /.../nadadresar/subor.
    """
    if type(item) == File:
        deinst = item.name + "." + item.extension
    else:
        deinst = item.name

    if item.parent:
        return getpath(item.parent) + "/" + deinst
    else:
        return "/" + deinst


def generate_tree_html(files, folders, groups):
    """
    BONUSOVA FUNKCIA
    Vstup zoznamy objektov suborov, adresarov a skupin.
    Priklad vstupu:
    ------------------
    folders = read_data("du_cvicko_4/in.txt")[1]
    files = read_data("du_cvicko_4/in.txt")[0]
    groups = read_data("du_cvicko_4/in.txt")[2]
    generate_tree_html(files.values(),
    folders.values(), groups.values())
    ------------------
    Funkcia za pouzitia rekurzivnej funkcie genpath
    vygeneruje subor output.html,
    po otvoreni tohto suboru v prehliadaci sa zobrazi
    stranka obsahujuca tabulku,
    kde je klikatelna cesta ku kazdemu suboru/adresaru,
    struktura je zoradena stromovo,
    dalej su zobrazene atributy ako velkost,
    vlastnik, skupina...
    """
    paths = {}
    for file in files:
        path = getpath(file)
        if file.parent.owner:
            own = file.parent.owner
        else:
            own = ""
        grp = "-"
        for group in groups:
            for fil in group.files:
                if fil.name == file.name:
                    grp = group.name
        paths[path] = "<td>" + own + "<td>" + grp + "<td>" + str(file.size)
    for folder in folders:
        path = getpath(folder)
        own = folder.owner
        paths[path] = "<td>" + own + "<td><td>" + str(get_folder_sizes(folder))

    with open("output.html", mode="w") as out:
        out.write("<!DOCTYPE html><html>\n<head>\n<meta charset='utf-8'>\n</head>\n<body>\n<table>\n<tr><td><b>Path</b><td><b>Owner</b><td><b>Group</b><td><b>Size</b>\n""")
        for item in sorted(paths.keys()):
            out.write("<tr><td><a href='" + item + "'>" + item + "</a>" + paths[item] + "\n")
        out.write("</table>\n</body>\n</html>\n")
