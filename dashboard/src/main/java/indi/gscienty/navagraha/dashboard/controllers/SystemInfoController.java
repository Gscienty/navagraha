package indi.gscienty.navagraha.dashboard.controllers;

import indi.gscienty.navagraha.dashboard.entities.SystemInfo;
import indi.gscienty.navagraha.dashboard.entities.GlobalInfo;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMethod;

import indi.gscienty.navagraha.dashboard.services.IMonitorService;

@RestController
@RequestMapping(value = "/api/system_info")
public class SystemInfoController {

    @Autowired
    private IMonitorService monitor;

    @RequestMapping(value = "/nava_version", method = RequestMethod.GET)
    public SystemInfo navaBaseInfoAcion() {
        SystemInfo info = new SystemInfo();

        info.setName("Navagraha");
        info.setVersion("v0.1");

        return info;
    }
    
    @RequestMapping(value = "/global", method = RequestMethod.GET)
    public GlobalInfo globalInfo() {
        return this.monitor.getGlobalInfo();
    }
}
