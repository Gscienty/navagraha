package indi.gscienty.navagraha.jni;

import indi.gscienty.navagraha.entities.Config;
import indi.gscienty.navagraha.entities.FuncUp;
import indi.gscienty.navagraha.entities.FuncDown;
import indi.gscienty.navagraha.entities.FuncList;
import indi.gscienty.navagraha.entities.FuncAutoscaling;
import indi.gscienty.navagraha.entities.FuncAutoscalingList;
import indi.gscienty.navagraha.entities.FuncPodList;
import indi.gscienty.navagraha.entities.RepoRemove;

public class Func {

    public native String up(Config cfg, FuncUp funcUp);

    public native String down(Config cfg, FuncDown funcDown);

    public native String repo(Config cfg);

    public native int repoRemove(Config cfg, RepoRemove repoRemove);

    public native String list(Config cfg, FuncList funcList);

    public native String autoscaling(Config cfg, FuncAutoscaling funcAutoscaling);

    public native String autoscalingList(Config cfg, FuncAutoscalingList funcAutoscalingList);

    public native String podList(Config cfg, FuncPodList funcPodList);
}
