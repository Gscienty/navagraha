package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

import com.alibaba.fastjson.JSON;

import org.springframework.stereotype.Service;

import indi.gscienty.navagraha.dashboard.ConfigSingleton;
import indi.gscienty.navagraha.dashboard.entities.FuncInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncRepoInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncUpForm;
import indi.gscienty.navagraha.entities.FuncList;
import indi.gscienty.navagraha.entities.FuncUp;
import indi.gscienty.navagraha.entities.FuncDown;
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
        return JSON.parseArray(result, FuncInfo.class);
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
}
