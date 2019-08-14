package indi.gscienty.navagraha.dashboard.controllers;

import java.util.List;

import indi.gscienty.navagraha.dashboard.services.INamespaceService;
import indi.gscienty.navagraha.dashboard.entities.NamespaceForm;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(value = "/api/namespace")
public class NamespaceController {

    @Autowired
    private INamespaceService namespaceService;

    @RequestMapping(method = RequestMethod.GET)
    public List<String> namespaceListAction() {
        return this.namespaceService.list();
    }

    @RequestMapping(method = RequestMethod.POST)
    public String namespaceAdd(@RequestBody NamespaceForm form) {
        this.namespaceService.add(form.getNamespace());
        return "done";
    }

    @RequestMapping(value = "/{namespace}", method = RequestMethod.DELETE)
    public String namespaceDelete(@PathVariable String namespace) {
        this.namespaceService.remove(namespace);
        return "done";
    }
}

