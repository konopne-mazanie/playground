package OcrConnect

import java.io.File
import java.net.Socket

class Socket {
    private val SOCKET_PATH = "/tmp/test.sock"
    try { new File(SOCKET_PATH).delete() } catch { case _ : Throwable => ; }
}
