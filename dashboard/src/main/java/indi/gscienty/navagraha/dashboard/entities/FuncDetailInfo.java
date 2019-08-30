package indi.gscienty.navagraha.dashboard.entities;

import java.util.List;

import indi.gscienty.navagraha.dashboard.entities.FuncAutoscalingInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncPodInfo;

public class FuncDetailInfo {
    private FuncInfo common;
    private List<FuncPodInfo> pods;
    private FuncAutoscalingInfo autoscaling;

    public void setCommon(FuncInfo common) {
        this.common = common;
    }

    public FuncInfo getCommon() {
        return common;
    }

    public void setPods(List<FuncPodInfo> pods) {
        this.pods = pods;
    }

    public List<FuncPodInfo> getPods() {
        return pods;
    }

    public void setAutoscaling(FuncAutoscalingInfo autoscaling) {
        this.autoscaling = autoscaling;
    }

    public FuncAutoscalingInfo getAutoscaling() {
        return autoscaling;
    }
}
