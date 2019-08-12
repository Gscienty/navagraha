package indi.gscienty.navagraha.entities;

public class Config {
    private String ca;
    private String cert;
    private String key;
    private String apiServer;
    private String dockerSock;

    public void setCa(String ca) {
        this.ca = ca;
    }

    public String getCa() {
        return ca;
    }

    public void setCert(String cert) {
        this.cert = cert;
    }

    public String getCert() {
        return cert;
    }

    public void setKey(String key) {
        this.key = key;
    }

    public String getKey() {
        return key;
    }

    public void setApiServer(String apiServer) {
        this.apiServer = apiServer;
    }

    public String getApiServer() {
        return apiServer;
    }

    public void setDockerSock(String dockerSock) {
        this.dockerSock = dockerSock;
    }

    public String getDockerSock() {
        return dockerSock;
    }
}
