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

    @Value("${nava.app.template.python3}")
    private String pythonTemplateContent;

    public String getJavaTemplateContent() {
        return this.javaTemplateContent;
    }

    public String getPythonTemplateContent() {
        return this.pythonTemplateContent;
    }

    public List<String> getSupportedTemplates() {
        return this.supportedTemplates;
    }

}
