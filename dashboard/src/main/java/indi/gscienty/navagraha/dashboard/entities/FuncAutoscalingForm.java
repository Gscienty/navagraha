package indi.gscienty.navagraha.dashboard.entities;

public class FuncAutoscalingForm {
    private int cpu;
    private int min;
    private int max;

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
