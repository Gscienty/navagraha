package indi.gscienty.navagraha.dashboard.services;

import java.util.function.Consumer;

public interface IActionListener {

    public String createTopic();

    public boolean pushMessage(String topic, String message);

    public boolean removeTopic(String topic);

    public boolean listenTopic(String topic, Consumer<String> consumer);

    public boolean leaveTopic(String topic, Consumer<String> consumer);

}
