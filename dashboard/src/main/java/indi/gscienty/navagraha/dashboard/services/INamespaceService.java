package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

import indi.gscienty.navagraha.dashboard.entities.NamespaceInfo;

public interface INamespaceService {

    public List<NamespaceInfo> list();

    public void add(String namespace);

    public void remove(String namespace);

    public void setMonitor(String namespace);

    public void deleteMonitor(String namespace);
}

