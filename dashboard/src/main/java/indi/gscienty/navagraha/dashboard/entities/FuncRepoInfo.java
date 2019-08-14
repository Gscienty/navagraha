package indi.gscienty.navagraha.dashboard.entities;

import java.util.List;

public class FuncRepoInfo {
    private String name;
    private List<String> versions;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setVersions(List<String> versions) {
        this.versions = versions;
    }

    public List<String> getVersions() {
        return versions;
    }
}
