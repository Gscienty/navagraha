package indi.gscienty.navagraha.dashboard.services;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import java.util.function.Consumer;

import com.alibaba.fastjson.JSON;
import indi.gscienty.navagraha.dashboard.AppProperties;
import indi.gscienty.navagraha.dashboard.ConfigSingleton;
import indi.gscienty.navagraha.dashboard.entities.FuncAutoscalingForm;
import indi.gscienty.navagraha.dashboard.entities.FuncAutoscalingInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncPodInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncRepoInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncUpForm;
import indi.gscienty.navagraha.entities.FuncAutoscaling;
import indi.gscienty.navagraha.entities.FuncAutoscalingList;
import indi.gscienty.navagraha.entities.FuncDown;
import indi.gscienty.navagraha.entities.FuncList;
import indi.gscienty.navagraha.entities.FuncPodList;
import indi.gscienty.navagraha.entities.FuncUp;
import indi.gscienty.navagraha.entities.ProjectBuild;
import indi.gscienty.navagraha.entities.ProjectInit;
import indi.gscienty.navagraha.entities.ProjectRemove;
import indi.gscienty.navagraha.jni.Func;
import indi.gscienty.navagraha.jni.Project;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class FuncService implements IFuncService {
    
    @Autowired
    private AppProperties props;

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

    public void localRepoInit(String type, String path) {
        if (this.props.getTemplateRepoLocal()) {
            this.copyLocalRepoTemplateDir(this.props.getLocalTemplateRepoPath() + "/template/" + type, path);
        }
        else {
            Project project = new Project();
            ProjectInit projectInit = new ProjectInit();

            projectInit.setPath(path);
            projectInit.setCodeType(type);
            projectInit.setLocalTemplatePath(this.props.getLocalTemplateRepoPath());
            projectInit.setUseLocal(this.props.getTemplateRepoLocal());

            project.init(projectInit);
        }

    }

    public void localRepoBuild(String name, String version, String path, Consumer<String> callback) {
        Project project = new Project();
        ProjectBuild build = new ProjectBuild();

        build.setName(name);
        build.setVersion(version);
        build.setPath(path);
        build.setConsumer(callback);

        project.build(ConfigSingleton.getInstance().getConfig(), build);
    }

    public void localRepoFillContent(String type, String path, String content) {
        switch (type) {
            case "java8":
                path = path + "/" + this.props.getJavaRewritePath();
                break;

            case "python3":
                path = path + "/" + this.props.getPythonRewritePath();
                break;
        }

        try {
            FileOutputStream stream = new FileOutputStream(path);
            stream.write(content.getBytes("UTF-8"));
            stream.close();
        }
        catch (Exception ex) {
            
        }
    }

    public void localRepoRemove(String path) {
        File file = new File(path);
        if (file.exists() == false) {
            return;
        }

        if (file.isDirectory()) {
            for (File subFile : file.listFiles()) {
                this.localRepoRemove(subFile.getAbsolutePath());
            }
        }
        file.delete();
    }

    public void dockerRepoRemove(String name, String version) {
        Project project = new Project();
        ProjectRemove remove = new ProjectRemove();
        remove.setName(name);
        remove.setVersion(version);

        project.remove(ConfigSingleton.getInstance().getConfig(), remove);
    }

    private void copyLocalRepoTemplateDir(String src, String dst) {
        File srcDir = new File(src);
        File[] srcFiles = srcDir.listFiles();

        File dstDir = new File(dst);

        if (dstDir.exists() == false) {
            dstDir.mkdir();
        }

        for (File f : srcFiles) {
            if (f.isFile()) {
                this.copyLocalRepoTemplateFile(f.getPath(), dst + "/" + f.getName());
            }
            else if (f.isDirectory()) {
                this.copyLocalRepoTemplateDir(f.getPath(), dst + "/" + f.getName());
            }
        }
    }

    private void copyLocalRepoTemplateFile(String src, String dst) {
        try {
            BufferedInputStream in = new BufferedInputStream(new FileInputStream(src));
            BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(dst));
            int i = -1;
            byte[] cache = new byte[4096];
            while ((i = in.read(cache)) != -1) {
                out.write(cache, 0, i);
            }
            in.close();
            out.close();
        }
        catch (Exception ex) {

        }
    }
}

