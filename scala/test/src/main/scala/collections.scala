import scala.collection.mutable.ArrayBuffer
import scala.collection.mutable.Map

object collections {
    def main(args: Array[String]): Unit = {
        val intArray = ArrayBuffer[Int](1,2)
        intArray += 3 += 4
        intArray ++= List(5, 6)
        intArray(2) = 4
        println(intArray)

        val charList = List('a', 'b', 'c') // linked list
        println(charList(1)) // slow, not indexed sequence (use vector)
        val charList2 = 'y' +: charList // can be charList :+ 'y'
        val charList3 = List('x', 'z') ++: charList2
        println(charList3)
        val strList = "lol" :: "omg" :: List()
        println(strList)
        val strList2 = "xD" :: Nil
        println(strList2 :: strList)
        println(5 :: strList2 :: strList :: Nil)

        println(Vector('a', 1) :++ List("xz"))

        val myMap = collection.mutable.Map( // type not necessary
            'x' -> 15,
            1 -> 27,
            "o" -> 'b',
            5 -> new MyFullClass(5)
        )
        myMap += Tuple2('c', 'd')
        myMap ++= Map('e' -> 'f')
        myMap -= (1, 'x') // remove theese keys
        println(myMap)

        myMap.foreach {
            case(key : Char, value : Char) => println(s"found pair char - char : $key, $value")
            case _ => println("other pair")
        }
    }
}
