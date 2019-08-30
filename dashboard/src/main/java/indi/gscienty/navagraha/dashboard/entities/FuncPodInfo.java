package indi.gscienty.navagraha.dashboard.entities;

public class FuncPodInfo {
    private String namespace;
    private String name;
    private String status;
    private String imageTag;
    private String policy;
    private String node;

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

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return status;
    }

    public void setPolicy(String policy) {
        this.policy = policy;
    }

    public String getPolicy() {
        return policy;
    }

    public void setNode(String node) {
        this.node = node;
    }

    public String getNode() {
        return node;
    }

    public void setImageTag(String imageTag) {
        this.imageTag = imageTag;
    }

    public String getImageTag() {
        return imageTag;
    }
}
