package indi.gscienty.navagraha.dashboard.entities;

import indi.gscienty.navagraha.dashboard.entities.GatewayInfo;

public class NamespaceInfo {
    private String name;
    private String status;
    private GatewayInfo gatewayInfo;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return status;
    }

    public void setGatewayInfo(GatewayInfo gatewayInfo) {
        this.gatewayInfo = gatewayInfo;
    }

    public GatewayInfo getGatewayInfo() {
        return gatewayInfo;
    }
}
