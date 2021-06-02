import scala.collection.mutable.ArrayBuffer

object collections {
    def main(args: Array[String]): Unit = {
        val intArray = ArrayBuffer[Int](1,2)
        intArray += 3 += 4
        intArray ++= List(5, 6)
        intArray(2) = 4
        println(intArray)


    }
}
