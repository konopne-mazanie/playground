import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.Future
import scala.util.{Failure, Success}

object futures {
    def runTask(input: Int) : Future[Int] = Future {
        Thread.sleep(input * 1000)
        scala.util.Random.nextInt(input)
    }

    def main(args: Array[String]): Unit = {
        val res: Future[(Int, Int)] = for {
            res1 <- runTask(3)
            res2 <- runTask(2)
        } yield (res1, res2)

        res.onComplete {
            case Success(x) => println(s"$x")
            case Failure(exception) => println(s"$exception")
        }

        Thread.sleep(6000)
    }
}
