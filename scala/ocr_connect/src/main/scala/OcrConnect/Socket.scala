package OcrConnect

import java.io.File
import java.net.Socket

class Socket {
    private val SOCKET_PATH = "/tmp/test.sock"
    try { new File(SOCKET_PATH).delete() } catch { case _ : Throwable => ; }

    // https://github.com/kohlschutter/junixsocket/blob/master/junixsocket-demo/src/main/java/org/newsclub/net/unix/demo/SimpleTestClient.java
}
