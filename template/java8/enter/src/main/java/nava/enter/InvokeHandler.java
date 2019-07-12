package nava.enter;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import nava.model.IHandler;
import nava.model.IRequest;
import nava.model.IResponse;
import nava.model.Request;

public class InvokeHandler implements HttpHandler {
    private IHandler handler;

    InvokeHandler(IHandler handler) {
        this.handler = handler;
    }

    public void handle(HttpExchange e) throws IOException {
        String body = "";

        InputStream is = e.getRequestBody();
        int len;
        byte[] buf = new byte[1024];
        ByteArrayOutputStream result = new ByteArrayOutputStream();

        while ((len = is.read(buf)) != -1) {
            result.write(buf, 0, len);
        }

        body = result.toString("UTF-8");

        IRequest req = new Request(body);
        IResponse res = this.handler.handle(req);

        String resBody = res.getBody();
        byte[] resBodyBytes = resBody.getBytes("UTF-8");

        e.getResponseHeaders().set("Content-Type", "application/octent-stream");
        e.sendResponseHeaders(200, resBodyBytes.length);

        OutputStream os = e.getResponseBody();
        os.write(resBodyBytes);
        os.close();
        System.out.println("Request / " + Integer.toString(resBodyBytes.length) +" bytes written.");
    }
}
