package indi.gscienty.navagraha.entities;

public class FuncDetail {
    private String name;
    private String namespace;
    private boolean stateful;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setNamespace(String namespace) {
        this.namespace = namespace;
    }

    public String getNamespace() {
        return namespace;
    }

    public void setStateful(boolean Stateful) {
        this.stateful = Stateful;
    }

    public boolean getStateful() {
        return stateful;
    }
}
