package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

import com.alibaba.fastjson.JSON;

import indi.gscienty.navagraha.dashboard.entities.NamespaceInfo;
import indi.gscienty.navagraha.dashboard.ConfigSingleton;
import indi.gscienty.navagraha.jni.Namespace;

import org.springframework.stereotype.Service;

@Service
public class NamespaceService implements INamespaceService {
    
    private Namespace namespace;

    public NamespaceService() {
        this.namespace = new Namespace();
    }

    public List<NamespaceInfo> list() {
        String result = this.namespace.list(ConfigSingleton.getInstance().getConfig());
        return JSON.parseArray(result, NamespaceInfo.class);
    }

    public void add(String namespace) {
        this.namespace.add(ConfigSingleton.getInstance().getConfig(), namespace);
    }

    public void remove(String namespace) {
        this.namespace.remove(ConfigSingleton.getInstance().getConfig(), namespace);
    }

}
