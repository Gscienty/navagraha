package indi.gscienty.navagraha.dashboard.controllers;

import java.util.List;

import indi.gscienty.navagraha.dashboard.entities.FuncUpForm;
import indi.gscienty.navagraha.dashboard.entities.FuncInfo;
import indi.gscienty.navagraha.dashboard.services.IFuncService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(value = "/api/func")
public class FuncController {

    @Autowired
    private IFuncService funcService;

    @RequestMapping(value = "/{namespace}", method = RequestMethod.GET)
    public List<FuncInfo> funcListAction(@PathVariable String namespace) {
        return this.funcService.list(namespace);
    }

    @RequestMapping(value = "/{namespace}", method = RequestMethod.POST)
    public String funcUpAction(@PathVariable String namespace, @RequestBody FuncUpForm form) {
        form.setNamespace(namespace);
        // TODO check form
        this.funcService.up(form);
        return "done";
    }

    @RequestMapping(value = "/{namespace}/{name}", method = RequestMethod.DELETE)
    public String funcDownAction(@PathVariable String namespace, @PathVariable String name) {
        this.funcService.down(name, namespace);
        return "done";
    }
}