import scala.util.{Try, Success, Failure}

object functional {
    val myfn : Any => String = {
        case _ : List[Any] => "list"
        case _ : Vector[Any] => "Vc"
        case _ => "other"
    }

    val toInt: String => Option[Int] = (input : String) => {
        try {
            Some(Integer.parseInt(input))
        } catch {
            case _: Throwable => None
        }
    }

    val toInt2 : String => Try[Int] = (s : String) => Try { Integer.parseInt(s) }
    val toInt2Try : Try[Int] => String = {
        case Success(i) => s"Got Int $i"
        case Failure(f) => s"Error: $f"
    }

    def main(args: Array[String]): Unit = {
        println(myfn(Vector(1, 2)))
        println(toInt("abc"))
        println(
            toInt2Try(
                for {
                    a <- toInt2("1")
                    b <- toInt2("2")
                } yield a + b
            )
        )
    }
}
