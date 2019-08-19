package indi.gscienty.navagraha.dashboard.controllers;

import java.util.List;

import indi.gscienty.navagraha.dashboard.entities.TemplateInfo;
import indi.gscienty.navagraha.dashboard.services.ITemplateService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(value = "/api/template")
public class TemplateController {

    @Autowired
    private ITemplateService templateService;

    @RequestMapping(value = "/content/{type}", method = RequestMethod.GET)
    public TemplateInfo getTypeInfoAction(@PathVariable String type) {
        return this.templateService.get(type);
    }

    @RequestMapping(value = "/type", method = RequestMethod.GET)
    public List<String> getTypes() {
        return this.templateService.supported();
    }

}
