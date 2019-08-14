package indi.gscienty.navagraha.entities;

public class FuncAutoscaling {
    private String name;
    private String namespace;
    private int cpu;
    private int min;
    private int max;

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

    public void setCpu(int cpu) {
        this.cpu = cpu;
    }

    public int getCpu() {
        return cpu;
    }

    public void setMin(int min) {
        this.min = min;
    }

    public int getMin() {
        return min;
    }

    public void setMax(int max) {
        this.max = max;
    }

    public int getMax() {
        return max;
    }
}
