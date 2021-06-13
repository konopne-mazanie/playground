package OcrConnect

import java.io.File

import scala.concurrent.{Future, Promise}

import akka.stream.OverflowStrategy
import akka.stream.alpakka.unixdomainsocket.scaladsl.UnixDomainSocket
import akka.stream.scaladsl.{Flow, Sink, Source}
import akka.util.ByteString

object OcrConnect {
    def main(args: Array[String]): Unit = {
        //val socket = new Socket()
        val path: java.nio.file.Path = new File("/tmp/test.sock").toPath
        val received = Promise[ByteString]

        val serverSideFlow = Flow[ByteString]
            .buffer(1, OverflowStrategy.backpressure)
            .wireTap(bytes => received.success(bytes))

        //#binding
        val binding: Future[UnixDomainSocket.ServerBinding] =
            UnixDomainSocket().bindAndHandle(serverSideFlow, path)
        //#binding

        //#outgoingConnection
        val sendBytes = ByteString("Hello")
        binding.flatMap { _ => // connection
            Source
                .single(sendBytes)
                .via(UnixDomainSocket().outgoingConnection(path))
                .runWith(Sink.ignore)
        }
    }
}
