package indi.gscienty.navagraha.dashboard.entities;

public class NodeInfo {
    private String name;
    private String status;
    private String architecture;
    private String containerRuntimeVersion;
    private String kernelVersion;
    private String kubeProxyVersion;
    private String kubeletVersion;
    private String os;
    private String osImage;

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

    public void setArchitecture(String architecture) {
        this.architecture = architecture;
    }

    public String getArchitecture() {
        return architecture;
    }

    public void setContainerRuntimeVersion(String containerRuntimeVersion) {
        this.containerRuntimeVersion = containerRuntimeVersion;
    }

    public String getContainerRuntimeVersion() {
        return containerRuntimeVersion;
    }

    public void setKernelVersion(String kernelVersion) {
        this.kernelVersion = kernelVersion;
    }

    public String getKernelVersion() {
        return kernelVersion;
    }

    public void setKubeProxyVersion(String kubeProxyVersion) {
        this.kubeProxyVersion = kubeProxyVersion;
    }

    public String getKubeProxyVersion() {
        return kubeProxyVersion;
    }

    public void setKubeletVersion(String kubeletVersion) {
        this.kubeletVersion = kubeletVersion;
    }

    public String getKubeletVersion() {
        return kubeletVersion;
    }

    public void setOs(String os) {
        this.os = os;
    }

    public String getOs() {
        return os;
    }

    public void setOsImage(String osImage) {
        this.osImage = osImage;
    }

    public String getOsImage() {
        return osImage;
    }
}
