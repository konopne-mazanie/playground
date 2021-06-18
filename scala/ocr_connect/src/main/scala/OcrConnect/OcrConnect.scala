package OcrConnect

import akka.actor.ActorSystem
import akka.stream.Materializer
import akka.stream.alpakka.unixdomainsocket.scaladsl.UnixDomainSocket
import akka.stream.scaladsl.Source
import akka.testkit.TestKit
import akka.util.ByteString

import java.io.File
import scala.concurrent.ExecutionContext
import scala.util.{Failure, Success}

object OcrConnect extends TestKit(ActorSystem("UnixDomainSocketSpec")) {
    def main(args: Array[String]): Unit = {
        println("start")
        val path: java.nio.file.Path = new File("/tmp/test.socket").toPath

        implicit val ma: Materializer = Materializer(system)
        implicit val ec: ExecutionContext = system.dispatcher

        val socketFlow = UnixDomainSocket().outgoingConnection(path)
        val out = Source.single(ByteString("Hello")).via(socketFlow).map(s => println(s.utf8String)).run
        out.onComplete {
            case Success(_) => println("sent")
            case Failure(exception) => println(s"failed: $exception")
        }

    }
}
