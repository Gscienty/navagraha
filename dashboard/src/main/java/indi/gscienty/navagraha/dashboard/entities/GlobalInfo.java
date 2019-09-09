package indi.gscienty.navagraha.dashboard.entities;

public class GlobalInfo {
    private Integer nodeCount;
    private Integer namespaceCount;
    private Integer funcCount;
    private Integer projectCount;

    public void setNodeCount(Integer nodeCount) {
        this.nodeCount = nodeCount;
    }

    public Integer getNodeCount() {
        return nodeCount;
    }

    public void setNamespaceCount(Integer namespaceCount) {
        this.namespaceCount = namespaceCount;
    }

    public Integer getNamespaceCount() {
        return namespaceCount;
    }

    public void setFuncCount(Integer funcCount) {
        this.funcCount = funcCount;
    }

    public Integer getFuncCount() {
        return funcCount;
    }

    public void setProjectCount(Integer projectCount) {
        this.projectCount = projectCount;
    }

    public Integer getProjectCount() {
        return projectCount;
    }
}
