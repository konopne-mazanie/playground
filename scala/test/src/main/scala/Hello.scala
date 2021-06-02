
object Hello {
    def testInt(x: Int) : Boolean = x match {
        case x if (x < 3) => true
        case 3 | 4 => false
        case _ => true
    }

    def main(args: Array[String]) = {
        println("Hello, world")
        val x = for (i <- 1 to 5) yield i * 2
        val y = x match {
            case a: List[String] => { a + "is sttring" }
            case b: List[Int] => { b + "is int" }
            case _ => "other"
        }
        println(y)

        val dbl: Double = 2.1
        println(s"dbl is $dbl")

        val myMap = Map(
            "key1" -> "val1",
            "key2" -> "val2",
            "n" -> "valn"
        )

        for ((key, value) <- myMap) println(s"val of $key is $value")

        val filteredMap : Map[String, String]
            = for ((key, value) <- myMap if (key.contains("key")))
                yield (key, value)
        println(filteredMap)

        println(testInt(10))

        class MyClass(var name: String, var testVal: Int);
        val myObject = new MyClass("test", 1);
        println(myObject);
        class MyImmutableClass(val name: String, val testVal: Int);

        class MyToStringOvrrideClass() {
            override def toString: String = "hey"
        }
        println(new MyToStringOvrrideClass())

    }
}
