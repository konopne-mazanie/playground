object case_classes {
    def main(args: Array[String]): Unit = {
        trait MyTraitForCase {
            val val1: Int
        }
        case class MyCaseClass(val1: Int, val2: String) extends MyTraitForCase
        case class MyCaseClass2(val1: Int) extends MyTraitForCase

        val printCaseClass : MyTraitForCase => String = {
            case MyCaseClass(val1, val2) => s"val1 is $val1, val2 is $val2"
            case MyCaseClass2(val1) => s"val1 is $val1"
        }
        println(printCaseClass(MyCaseClass2(1)))

        val myCaseClassInstance = MyCaseClass(1, "test")
        println(myCaseClassInstance.copy(val2 = "test1")) // update as you copy

        println(MyCaseClass2(1) == MyCaseClass2(1))

        val MyCaseClass(x, y) = MyCaseClass(1, "test")
        println(s"$x .. $y")
    }
}
