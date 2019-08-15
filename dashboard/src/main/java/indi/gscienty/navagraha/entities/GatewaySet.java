package indi.gscienty.navagraha.entities;

public class GatewaySet {
    private String namespace;
    private String policy;
    private int replicas;
    private String image;

    public void setNamespace(String namespace) {
        this.namespace = namespace;
    }

    public String getNamespace() {
        return namespace;
    }

    public void setPolicy(String policy) {
        this.policy = policy;
    }

    public String getPolicy() {
        return policy;
    }

    public void setReplicas(int replicas) {
        this.replicas = replicas;
    }

    public int getReplicas() {
        return replicas;
    }

    public void setImage(String image) {
        this.image = image;
    }

    public String getImage() {
        return image;
    }
}
