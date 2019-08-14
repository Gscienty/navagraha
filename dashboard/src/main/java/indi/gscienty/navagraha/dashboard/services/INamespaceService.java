package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

public interface INamespaceService {

    public List<String> list();

    public void add(String namespace);

    public void remove(String namespace);
}

