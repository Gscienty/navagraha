package indi.gscienty.navagraha.entities;

public class ProjectInit {
    private String path;
    private String codeType;
    private String localTemplatePath;
    private boolean useLocal;

    public void setPath(String path) {
        this.path = path;
    }

    public String getPath() {
        return path;
    }

    public void setCodeType(String codeType) {
        this.codeType = codeType;
    }

    public String getCodeType() {
        return codeType;
    }

    public void setLocalTemplatePath(String localTemplatePath) {
        this.localTemplatePath = localTemplatePath;
    }

    public String getLocalTemplatePath() {
        return localTemplatePath;
    }

    public void setUseLocal(boolean useLocal) {
        this.useLocal = useLocal;
    }

    public boolean getUseLocal() {
        return useLocal;
    }
}
