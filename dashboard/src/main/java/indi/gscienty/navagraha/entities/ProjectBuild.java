package indi.gscienty.navagraha.entities;

import java.util.function.Consumer;

public class ProjectBuild {
    private String name;
    private String version;
    private String path;
    private Consumer<String> consumer;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    public String getVersion() {
        return version;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public String getPath() {
        return path;
    }

    public void setConsumer(Consumer<String> consumer) {
        this.consumer = consumer;
    }

    public Consumer<String> getConsumer() {
        return consumer;
    }
}
