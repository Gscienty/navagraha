package indi.gscienty.navagraha.dashboard.services;

import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import com.alibaba.fastjson.JSON;

import org.springframework.stereotype.Service;

import indi.gscienty.navagraha.dashboard.ConfigSingleton;
import indi.gscienty.navagraha.dashboard.entities.FuncInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncRepoInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncUpForm;
import indi.gscienty.navagraha.dashboard.entities.FuncPodInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncAutoscalingInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncAutoscalingForm;
import indi.gscienty.navagraha.entities.FuncList;
import indi.gscienty.navagraha.entities.FuncUp;
import indi.gscienty.navagraha.entities.FuncDown;
import indi.gscienty.navagraha.entities.FuncPodList;
import indi.gscienty.navagraha.entities.FuncAutoscalingList;
import indi.gscienty.navagraha.entities.FuncAutoscaling;
import indi.gscienty.navagraha.jni.Func;

@Service
public class FuncService implements IFuncService {
    private Func func;

    public FuncService() {
        this.func = new Func();
    }

    public List<FuncInfo> list(String namespace) {
        FuncList listConfig = new FuncList();
        listConfig.setNamespace(namespace);

        String result = this.func.list(ConfigSingleton.getInstance().getConfig(), listConfig);
        List<FuncInfo> ret = JSON.parseArray(result, FuncInfo.class);

        FuncAutoscalingList funcAutoscalingListConfig = new FuncAutoscalingList();
        funcAutoscalingListConfig.setNamespace(namespace);
        funcAutoscalingListConfig.setName("");

        String autoscalingResult = this.func.autoscalingList(ConfigSingleton.getInstance().getConfig(), funcAutoscalingListConfig);
        List<FuncAutoscalingInfo> autoscalingInfos = JSON.parseArray(autoscalingResult, FuncAutoscalingInfo.class);

        Map<String, FuncAutoscalingInfo> autoscalingInfoMap = new TreeMap<String, FuncAutoscalingInfo>();

        for (FuncAutoscalingInfo autoscalingInfo : autoscalingInfos) {
            autoscalingInfoMap.put(autoscalingInfo.getTarget(), autoscalingInfo);
        }

        for (FuncInfo info : ret) {
            if (autoscalingInfoMap.containsKey(info.getName())) {
                info.setAutoscalingInfo(autoscalingInfoMap.get(info.getName()));
            }
        }

        return ret;
    }

    public List<FuncRepoInfo> repo() {
        String result = this.func.repo(ConfigSingleton.getInstance().getConfig());
        return JSON.parseArray(result, FuncRepoInfo.class);
    }

    public void up(FuncUpForm form) {
        FuncUp upConfig = new FuncUp();

        upConfig.setName(form.getName());
        upConfig.setImage(form.getImage());
        upConfig.setPolicy(form.getPolicy());
        upConfig.setUpdate(form.getUpdate());
        upConfig.setReplicas(form.getReplicas());
        upConfig.setStateful(form.getStateful());
        upConfig.setNamespace(form.getNamespace());

        this.func.up(ConfigSingleton.getInstance().getConfig(), upConfig);
    }

    public void down(String namespace, String name) {
        FuncDown downConfig = new FuncDown();

        downConfig.setName(name);
        downConfig.setNamespace(namespace);
        downConfig.setStateful(false);

        this.func.down(ConfigSingleton.getInstance().getConfig(), downConfig);
    }

    public List<FuncPodInfo> podList(String namespace, String name) {
        FuncPodList podListConfig = new FuncPodList();

        podListConfig.setName(name);
        podListConfig.setNamespace(namespace);

        String result = this.func.podList(ConfigSingleton.getInstance().getConfig(), podListConfig);
        return JSON.parseArray(result, FuncPodInfo.class);
    }

    public void autoscaling(String namespace, String name, FuncAutoscalingForm form) {
        FuncAutoscaling autoscaling = new FuncAutoscaling();        

        autoscaling.setName(name);
        autoscaling.setNamespace(namespace);
        autoscaling.setCpu(form.getCpu());
        autoscaling.setMax(form.getMax());
        autoscaling.setMin(form.getMin());

        this.func.autoscaling(ConfigSingleton.getInstance().getConfig(), autoscaling);
    }
}

