package indi.gscienty.navagraha.dashboard.entities;

public class FuncAutoscalingInfo {
    private String name;
    private int minReplicas;
    private int maxReplicas;
    private int cpu;
    private String target;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setMinReplicas(int minReplicas) {
        this.minReplicas = minReplicas;
    }

    public int getMinReplicas() {
        return minReplicas;
    }

    public void setMaxReplicas(int maxReplicas) {
        this.maxReplicas = maxReplicas;
    }

    public int getMaxReplicas() {
        return maxReplicas;
    }

    public void setCpu(int cpu) {
        this.cpu = cpu;
    }

    public int getCpu() {
        return cpu;
    }

    public void setTarget(String target) {
        this.target = target;
    }

    public String getTarget() {
        return target;
    }
}
