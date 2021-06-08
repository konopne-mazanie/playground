package MyPackage

class ClassWCompanion private {
    var x = ""
    var y = 0
}

object ClassWCompanion {
    def apply(x: String): ClassWCompanion = {
        val ret = new ClassWCompanion
        ret.x = x
        return ret
    }

    def apply(x: String, y: Int): ClassWCompanion = {
        val ret = new ClassWCompanion
        ret.x = x
        ret.y = y
        return ret
    }

    def unapply(classWCompanion: ClassWCompanion): (String, Int) = (classWCompanion.x, classWCompanion.y)
}
