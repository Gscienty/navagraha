package indi.gscienty.navagraha.dashboard;

import indi.gscienty.navagraha.entities.Config;

public class ConfigSingleton {

    private volatile Config config;
    private static ConfigSingleton instance = null;

    private ConfigSingleton() {
        this.config = new Config();
        this.config.setCa("/etc/kubernetes/pki/ca.crt");
        this.config.setKey("/etc/kubernetes/pki/apiserver-kubelet-client.key");
        this.config.setCert("/etc/kubernetes/pki/apiserver-kubelet-client.crt");
        this.config.setApiServer("https://localhost:6443");
        this.config.setDockerSock("/var/run/docker.sock");
    }

    public synchronized static ConfigSingleton getInstance() {
        if (ConfigSingleton.instance == null) {
            ConfigSingleton.instance = new ConfigSingleton();
        }

        return ConfigSingleton.instance;
    }

    public Config getConfig() {
        return this.config;
    }
}
