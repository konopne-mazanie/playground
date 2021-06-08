package MyPackage

import MyPackage.ClassWCompanion.unapply

object ClassWCompanionTest {
    def main(args: Array[String]): Unit = {
        val test = ClassWCompanion("test")
        val test1 = ClassWCompanion("test", 1)
        val (test1x, test1y) = unapply(test1)
        println(test1x, test1y)
    }
}
