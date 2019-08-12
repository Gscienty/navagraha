package indi.gscienty.navagraha.entities;

public class FuncUp {
    private String name;
    private String policy;
    private String image;
    private String namespace;
    private boolean stateful;
    private boolean update;
    private int replicas;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setPolicy(String policy) {
        this.policy = policy;
    }

    public String getPolicy() {
        return policy;
    }

    public void setImage(String image) {
        this.image = image;
    }

    public String getImage() {
        return image;
    }

    public void setNamespace(String namespace) {
        this.namespace = namespace;
    }

    public String getNamespace() {
        return namespace;
    }

    public void setStateful(boolean stateful) {
        this.stateful = stateful;
    }

    public boolean getStateful() {
        return stateful;
    }

    public void setUpdate(boolean update) {
        this.update = update;
    }

    public boolean getUpdate() {
        return update;
    }

    public void setReplicas(int replicas) {
        this.replicas = replicas;
    }

    public int getReplicas() {
        return replicas;
    }
}
