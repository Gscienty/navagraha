package indi.gscienty.navagraha.entities;

public class FuncDown {
    private String namespace;
    private String name;
    private boolean stateful;

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
}
