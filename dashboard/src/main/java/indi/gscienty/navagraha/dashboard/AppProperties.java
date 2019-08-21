package indi.gscienty.navagraha.dashboard;

import java.util.List;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component
public class AppProperties {

    @Value("#{'${nava.app.template.supported}'.split(',')}")
    private List<String> supportedTemplates;

    @Value("${nava.app.template.java8}")
    private String javaTemplateContent;

    @Value("${nava.app.template.java8.rewritepath}")
    private String javaRewritePath;

    @Value("${nava.app.template.python3}")
    private String pythonTemplateContent;

    @Value("${nava.app.template.python3.rewritepath}")
    private String pythonRewritePath;

    @Value("${nava.app.template.repo.uselocal}")
    private Boolean templateRepoLocal;

    @Value("${nava.app.template.repo.path}")
    private String localTemplateRepoPath;


    public String getJavaTemplateContent() {
        return this.javaTemplateContent;
    }

    public String getPythonTemplateContent() {
        return this.pythonTemplateContent;
    }

    public List<String> getSupportedTemplates() {
        return this.supportedTemplates;
    }

    public Boolean getTemplateRepoLocal() {
        return templateRepoLocal;
    }

    public String getLocalTemplateRepoPath() {
        return localTemplateRepoPath;
    }

    public String getJavaRewritePath() {
        return javaRewritePath;
    }

    public String getPythonRewritePath() {
        return pythonRewritePath;
    }
}
