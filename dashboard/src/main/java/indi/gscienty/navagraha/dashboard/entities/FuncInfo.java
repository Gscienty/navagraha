package indi.gscienty.navagraha.dashboard.entities;

public class FuncInfo {
    private String namespace;
    private String name;
    private boolean stateful;
    private String imageTag;
    private int replicas;
    private int available;
    private int unavailable;

    public void setNamespace(String namespace) {
        this.namespace = namespace;
    }

    public String getNamespace() {
        return namespace;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setStateful(boolean stateful) {
        this.stateful = stateful;
    }

    public boolean getStateful() {
        return stateful;
    }

    public void setImageTag(String imageTag) {
        this.imageTag = imageTag;
    }

    public String getImageTag() {
        return imageTag;
    }

    public void setReplicas(int replicas) {
        this.replicas = replicas;
    }

    public int getReplicas() {
        return replicas;
    }

    public void setAvailable(int available) {
        this.available = available;
    }

    public int getAvailable() {
        return available;
    }

    public void setUnavailable(int unavailable) {
        this.unavailable = unavailable;
    }

    public int getUnavailable() {
        return unavailable;
    }
}
