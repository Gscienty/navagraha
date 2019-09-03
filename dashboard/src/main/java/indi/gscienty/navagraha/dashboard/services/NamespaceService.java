package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

import com.alibaba.fastjson.JSON;

import indi.gscienty.navagraha.dashboard.entities.NamespaceInfo;
import indi.gscienty.navagraha.dashboard.entities.GatewayInfo;
import indi.gscienty.navagraha.dashboard.ConfigSingleton;
import indi.gscienty.navagraha.entities.GatewayGet;
import indi.gscienty.navagraha.jni.Namespace;
import indi.gscienty.navagraha.jni.Gateway;

import org.springframework.stereotype.Service;

@Service
public class NamespaceService implements INamespaceService {
    
    private Namespace namespace;
    private Gateway gateway;

    public NamespaceService() {
        this.namespace = new Namespace();
        this.gateway = new Gateway();
    }

    public List<NamespaceInfo> list() {
        String result = this.namespace.list(ConfigSingleton.getInstance().getConfig());
        List<NamespaceInfo> resultList = JSON.parseArray(result, NamespaceInfo.class);

        for (NamespaceInfo ns : resultList) {
            GatewayGet gatewayGet = new GatewayGet();
            gatewayGet.setNamespace(ns.getName());
            String gatewayInfosStr = this.gateway.get(ConfigSingleton.getInstance().getConfig(), gatewayGet);
            List<GatewayInfo> gatewayInfos = JSON.parseArray(gatewayInfosStr, GatewayInfo.class);
            if (gatewayInfos.size() != 0) {
                ns.setGatewayInfo(gatewayInfos.get(0));
            }
            else {
                ns.setGatewayInfo(null);
            }
        }

        return resultList;
    }

    public void add(String namespace) {
        this.namespace.add(ConfigSingleton.getInstance().getConfig(), namespace);
    }

    public void remove(String namespace) {
        this.namespace.remove(ConfigSingleton.getInstance().getConfig(), namespace);
    }

}
