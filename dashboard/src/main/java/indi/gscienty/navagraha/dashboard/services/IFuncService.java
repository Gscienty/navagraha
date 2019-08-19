package indi.gscienty.navagraha.dashboard.services;

import indi.gscienty.navagraha.dashboard.entities.FuncUpForm;
import indi.gscienty.navagraha.dashboard.entities.FuncInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncRepoInfo;
import indi.gscienty.navagraha.dashboard.entities.FuncPodInfo;

import java.util.List;


public interface IFuncService {

    public List<FuncInfo> list(String namespace);

    public List<FuncRepoInfo> repo();

    public void up(FuncUpForm form);

    public void down(String namespace, String name);

    public List<FuncPodInfo> podList(String namespace, String name);
}
