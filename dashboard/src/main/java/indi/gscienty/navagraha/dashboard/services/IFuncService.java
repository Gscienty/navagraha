package indi.gscienty.navagraha.dashboard.services;

import java.util.function.Consumer;

import java.util.List;

import indi.gscienty.navagraha.dashboard.entities.FuncAutoscalingForm;
import indi.gscienty.navagraha.dashboard.entities.FuncInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncPodInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncRepoInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncUpForm;


public interface IFuncService {

    public List<FuncInfo> list(String namespace);

    public List<FuncRepoInfo> repo();

    public void up(FuncUpForm form);

    public void down(String namespace, String name);

    public List<FuncPodInfo> podList(String namespace, String name);

    public void autoscaling(String namespace, String name, FuncAutoscalingForm form);

    public void repoInit(String type, String path);

    public void repoFillContent(String type, String path, String content);

    public void repoBuild(String name, String version, String path, Consumer<String> callback);

    public void repoRemove(String path);
}
