package indi.gscienty.navagraha.dashboard.controllers;

import indi.gscienty.navagraha.dashboard.ConfigSingleton;
import indi.gscienty.navagraha.entities.FuncDown;
import indi.gscienty.navagraha.entities.FuncList;
import indi.gscienty.navagraha.entities.FuncUp;
import indi.gscienty.navagraha.jni.Func;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(value = "/api/func")
public class FuncController {

    private Func func;

    public FuncController() {
        this.func = new Func();
    }

    @RequestMapping(value = "/list/{namespace}", method = RequestMethod.GET)
    public String funcListAction(@PathVariable String namespace) {
        FuncList listConfig = new FuncList();
        if (namespace.isEmpty()) {
            namespace = "default";
        }
        listConfig.setNamespace(namespace);

        return this.func.list(ConfigSingleton.getInstance().getConfig(), listConfig);
    }

    @RequestMapping(value = "/repo", method = RequestMethod.GET)
    public String funcRepoAction() {
        return this.func.repo(ConfigSingleton.getInstance().getConfig());
    }

    @RequestMapping(value = "/up/{namespace}", method = RequestMethod.POST)
    public String funcUpAction(@PathVariable String namespace) {
        FuncUp upConfig = new FuncUp();

        upConfig.setNamespace(namespace);
        // TODO
        
        return this.func.up(ConfigSingleton.getInstance().getConfig(), upConfig);
    }

    @RequestMapping(value = "/down/{namespace}/{name}", method = RequestMethod.DELETE)
    public String funcDownAction(@PathVariable String namespace, @PathVariable String name) {
        FuncDown downConfig = new FuncDown();

        downConfig.setName(name);
        downConfig.setNamespace(namespace);
        downConfig.setStateful(false);

        return this.func.down(ConfigSingleton.getInstance().getConfig(), downConfig);
    }
}
