package indi.gscienty.navagraha.dashboard.controllers;

import java.util.List;
import java.util.UUID;

import indi.gscienty.navagraha.dashboard.entities.FuncRepoInfo;
import indi.gscienty.navagraha.dashboard.entities.GatewayRepoInfo;
import indi.gscienty.navagraha.dashboard.entities.BuildRepoForm;
import indi.gscienty.navagraha.dashboard.services.IFuncService;
import indi.gscienty.navagraha.dashboard.services.IGatewayService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(value = "/api/repo")
public class RepoController {

    @Autowired
    private IFuncService funcService;

    @Autowired
    private IGatewayService gatewayService;

    @RequestMapping(value = "/func", method = RequestMethod.GET)
    public List<FuncRepoInfo> funcRepoAction() {
        return this.funcService.repo();
    }

    @RequestMapping(value = "/apigw", method = RequestMethod.GET)
    public List<GatewayRepoInfo> gatewayRepoAction() {
        return this.gatewayService.repo();
    }

    @RequestMapping(value = "/build/{type}", method = RequestMethod.POST)
    public String buildRepoAction(@PathVariable String type, @RequestBody BuildRepoForm form) {
        String path = "/tmp/nava-build-" + UUID.randomUUID().toString();
        this.funcService.repoInit(type, path);
        this.funcService.repoFillContent(type, path, form.getContent());
        this.funcService.repoBuild(form.getName(), form.getVersion(), path, val -> {
            System.out.println(val);
        });
        this.funcService.repoRemove(path);

        return "done";
    }

}

