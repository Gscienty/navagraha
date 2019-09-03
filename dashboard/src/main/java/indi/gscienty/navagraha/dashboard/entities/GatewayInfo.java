package indi.gscienty.navagraha.dashboard.entities;

public class GatewayInfo {
    private String namespace;
    private String clusterIP;
    private String imageTag;

    public void setNamespace(String namespace) {
        this.namespace = namespace;
    }

    public String getNamespace() {
        return namespace;
    }

    public void setClusterIP(String clusterIP) {
        this.clusterIP = clusterIP;
    }

    public String getClusterIP() {
        return clusterIP;
    }

    public void setImageTag(String imageTag) {
        this.imageTag = imageTag;
    }

    public String getImageTag() {
        return imageTag;
    }
}
