package indi.gscienty.navagraha.dashboard.controllers;

import indi.gscienty.navagraha.dashboard.entities.SystemInfo;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMethod;

@RestController
@RequestMapping(value = "/api/system_info")
public class SystemInfoController {

    @RequestMapping(value = "/nava_version", method = RequestMethod.GET)
    public SystemInfo navaBaseInfoAcion() {
        SystemInfo info = new SystemInfo();

        info.setName("Navagraha");
        info.setVersion("v0.1");

        return info;
    }
}
