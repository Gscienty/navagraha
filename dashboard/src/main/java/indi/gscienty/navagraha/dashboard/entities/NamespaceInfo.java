package indi.gscienty.navagraha.dashboard.entities;

import indi.gscienty.navagraha.dashboard.entities.GatewayInfo;
import indi.gscienty.navagraha.dashboard.entities.MonitorInfo;

public class NamespaceInfo {
    private String name;
    private String status;
    private GatewayInfo gatewayInfo;
    private MonitorInfo monitorInfo;

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

    public void setMonitorInfo(MonitorInfo monitorInfo) {
        this.monitorInfo = monitorInfo;
    }

    public MonitorInfo getMonitorInfo() {
        return monitorInfo;
    }
}
