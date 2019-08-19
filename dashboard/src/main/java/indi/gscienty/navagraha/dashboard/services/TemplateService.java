package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

import indi.gscienty.navagraha.dashboard.AppProperties;
import indi.gscienty.navagraha.dashboard.entities.TemplateInfo;
import indi.gscienty.navagraha.dashboard.services.ITemplateService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class TemplateService implements ITemplateService {

    @Autowired
    private AppProperties properties;

    public TemplateInfo get(String type) {
        TemplateInfo info = new TemplateInfo();
        switch (type) {
            case "java8":
                info.setType("java8");
                info.setContent(this.properties.getJavaTemplateContent());
                break;

            case "python3":
                info.setType("python3");
                info.setContent(this.properties.getPythonTemplateContent());
                break;

            default:
                return null;
        }
        return info;
    }

    public List<String> supported() {
        return this.properties.getSupportedTemplates();
    }
}
