package nava.enter;

import com.sun.net.httpserver.HttpServer;

import java.net.InetSocketAddress;

import nava.enter.InvokeHandler;
import nava.function.Handler;

public class Enter {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);

        InvokeHandler handler = new InvokeHandler(new Handler());


        server.setExecutor(null);
        server.createContext("/", handler);
        server.start();
    }
}
