package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

import indi.gscienty.navagraha.dashboard.entities.GatewayInfo;
import indi.gscienty.navagraha.dashboard.entities.GatewayForm;
import indi.gscienty.navagraha.dashboard.entities.GatewayRepoInfo;

public interface IGatewayService {

    public void set(GatewayForm form);

    public List<GatewayInfo> get(String namespace);

    public void remove(String namespace);

    public List<GatewayRepoInfo> repo();
}
