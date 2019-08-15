package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

import indi.gscienty.navagraha.dashboard.entities.GatewayInfo;
import indi.gscienty.navagraha.dashboard.entities.GatewayForm;

public interface IGatewayService {

    public void set(GatewayForm namespace);

    public List<GatewayInfo> get(String namespace);

    public void remove(String namespace);
}
