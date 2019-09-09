package indi.gscienty.navagraha.dashboard.services;

import org.springframework.stereotype.Service;

import indi.gscienty.navagraha.dashboard.ConfigSingleton;
import indi.gscienty.navagraha.dashboard.entities.GlobalInfo;
import indi.gscienty.navagraha.jni.Monitor;

@Service
public class MonitorService implements IMonitorService {
    public GlobalInfo getGlobalInfo() {
        Monitor monitor = new Monitor();
        GlobalInfo info = new GlobalInfo();

        info.setFuncCount(monitor.funcCount(ConfigSingleton.getInstance().getConfig()));
        info.setNodeCount(monitor.nodeCount(ConfigSingleton.getInstance().getConfig()));
        info.setProjectCount(monitor.projectCount(ConfigSingleton.getInstance().getConfig()));
        info.setNamespaceCount(monitor.namespaceCount(ConfigSingleton.getInstance().getConfig()));

        return info;
    }
}
