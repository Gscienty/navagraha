package indi.gscienty.navagraha.dashboard.websocket;

import java.io.IOException;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.CopyOnWriteArraySet;

import javax.websocket.OnClose;
import javax.websocket.OnOpen;
import javax.websocket.Session;
import javax.websocket.server.PathParam;
import javax.websocket.server.ServerEndpoint;

import org.springframework.stereotype.Component;

@Component
@ServerEndpoint("/api/ws-topic/{topic}")
public class WebSocketService {
    
    private String topic;
    private Session session;

    private static ConcurrentMap<String, CopyOnWriteArraySet<WebSocketService>> wsSocket = new ConcurrentHashMap<String, CopyOnWriteArraySet<WebSocketService>>();

    @OnOpen
    public void onOpen(Session session, @PathParam("topic") String topic) {
        this.topic = topic;
        this.session = session;

        if (WebSocketService.wsSocket.containsKey(topic) == false) {
            WebSocketService.wsSocket.put(topic, new CopyOnWriteArraySet<WebSocketService>());
        }

        WebSocketService.wsSocket.get(topic).add(this);
    }

    @OnClose
    public void onClose() {
        WebSocketService.wsSocket.get(this.topic).remove((Object) this.session);
        if (WebSocketService.wsSocket.get(this.topic).isEmpty()) {
            WebSocketService.wsSocket.remove(this.topic);
        }
    }

    public void sendMessage(String message) throws IOException {
        this.session.getBasicRemote().sendText(message);
    }

    public static void sendInfo(String topic, String message) {
        for (WebSocketService ws : WebSocketService.wsSocket.get(topic)) {
            try {
                ws.sendMessage(message);
            }
            catch (Exception ex) { }
        }
    }

    public static void topicOffline(String topic) {
        for (WebSocketService ws : WebSocketService.wsSocket.get(topic)) {
            try {
                ws.session.close();
            }
            catch (Exception ex) { }
        }
        WebSocketService.wsSocket.remove(topic);
    }
}
