package OcrConnect

import java.io.File
import akka.stream.alpakka.unixdomainsocket.scaladsl.UnixDomainSocket
import akka.actor.ActorSystem
import akka.stream.scaladsl.{Flow, Keep, Sink, Source}
import akka.testkit.TestKit
import akka.util.ByteString

object OcrConnect extends TestKit(ActorSystem("UnixDomainSocketSpec")) {
    def main(args: Array[String]): Unit = {
        println("start")
        val path: java.nio.file.Path = new File("/tmp/test.socket").toPath
        val sendBytes = ByteString("Hello")
        Source.single(sendBytes).via(UnixDomainSocket().outgoingConnection(path))
    }
}
