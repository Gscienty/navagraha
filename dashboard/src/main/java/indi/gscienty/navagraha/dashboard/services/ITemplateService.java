package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

import indi.gscienty.navagraha.dashboard.entities.TemplateInfo;

public interface ITemplateService {

    public TemplateInfo get(String type);

    public List<String> supported();

}
