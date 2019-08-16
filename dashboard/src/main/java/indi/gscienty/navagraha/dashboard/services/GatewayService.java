package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

import com.alibaba.fastjson.JSON;

import indi.gscienty.navagraha.entities.GatewayGet;
import indi.gscienty.navagraha.entities.GatewayRemove;
import indi.gscienty.navagraha.entities.GatewaySet;
import indi.gscienty.navagraha.dashboard.ConfigSingleton;
import indi.gscienty.navagraha.dashboard.entities.GatewayInfo;
import indi.gscienty.navagraha.dashboard.entities.GatewayForm;
import indi.gscienty.navagraha.dashboard.entities.GatewayRepoInfo;
import indi.gscienty.navagraha.jni.Gateway;
import org.springframework.stereotype.Service;

@Service
public class GatewayService implements IGatewayService {

    private Gateway gateway;

    public GatewayService() {
        this.gateway = new Gateway();
    }

    public void set(GatewayForm form) {
        GatewaySet set = new GatewaySet();

        set.setImage(form.getImage());
        set.setPolicy(form.getPolicy());
        set.setReplicas(form.getReplicas());
        set.setNamespace(form.getNamespace());

        this.gateway.set(ConfigSingleton.getInstance().getConfig(), set);
    }

    public List<GatewayInfo> get(String namespace) {
        GatewayGet get = new GatewayGet();

        get.setNamespace(namespace);
        String result = this.gateway.get(ConfigSingleton.getInstance().getConfig(), get);

        return JSON.parseArray(result, GatewayInfo.class);
    }

    public void remove(String namespace) {
        GatewayRemove remove = new GatewayRemove();

        remove.setNamespace(namespace);

        this.gateway.remove(ConfigSingleton.getInstance().getConfig(), remove);
    }

    public List<GatewayRepoInfo> repo() {
       String result = this.gateway.repo(ConfigSingleton.getInstance().getConfig());
       return JSON.parseArray(result, GatewayRepoInfo.class);
    }
}
