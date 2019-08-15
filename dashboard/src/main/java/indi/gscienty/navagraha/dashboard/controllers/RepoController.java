package indi.gscienty.navagraha.dashboard.controllers;

import java.util.List;

import indi.gscienty.navagraha.dashboard.entities.FuncRepoInfo;
import indi.gscienty.navagraha.dashboard.services.IFuncService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(value = "/api/repo")
public class RepoController {
    @Autowired
    private IFuncService funcService;

    @RequestMapping(value = "/func", method = RequestMethod.GET)
    public List<FuncRepoInfo> funcRepoAction() {
        return this.funcService.repo();
    }

}
