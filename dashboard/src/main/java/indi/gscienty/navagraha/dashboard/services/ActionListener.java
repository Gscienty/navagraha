package indi.gscienty.navagraha.dashboard.services;

import java.util.concurrent.ConcurrentHashMap;

import java.util.UUID;
import java.util.function.Consumer;

import indi.gscienty.navagraha.dashboard.services.IActionListener;
import org.springframework.stereotype.Service;

@Service
public class ActionListener implements IActionListener {

    public String createTopic() {
        return ActionListenerSingleton.instance.createTopic();
    }

    public boolean pushMessage(String topic, String message) {
        return ActionListenerSingleton.instance.pushMessage(topic, message);
    }

    public boolean removeTopic(String topic) {
        return ActionListenerSingleton.instance.removeTopic(topic);
    }

    public boolean listenTopic(String topic, Consumer<String> consumer) {
        return ActionListenerSingleton.instance.listenTopic(topic, consumer);
    }

    public boolean leaveTopic(String topic, Consumer<String> consumer) {
        return ActionListenerSingleton.instance.leaveTopic(topic, consumer);
    }

    private enum ActionListenerSingleton {
        instance;

        private ConcurrentHashMap<String, Consumer<String>> topics;

        private ActionListenerSingleton() {
            this.topics = new ConcurrentHashMap<String, Consumer<String>>();
        }

        public String createTopic() {
            String topic = UUID.randomUUID().toString();
            while (this.topics.containsKey(topic) == true) {
                topic = UUID.randomUUID().toString();
            }
            this.topics.put(topic, m -> { });
            return topic;
        }

        public boolean pushMessage(String topic, String message) {
            synchronized (this) {
                if (this.topics.containsKey(topic) == false) {
                    return false;
                }
                this.topics.get(topic).accept(message);
                return true;
            }
        }

        public boolean removeTopic(String topic) {
            this.topics.remove(topic);
            return true;
        }

        public boolean listenTopic(String topic, Consumer<String> consumer) {
            synchronized (this) {
                if (this.topics.containsKey(topic) == false) {
                    return false;
                }

                this.topics.remove(topic);
                this.topics.put(topic, consumer);
                return true;
            }
        }

        public boolean leaveTopic(String topic, Consumer<String> consumer) {
            return true;
        }
    }
}
