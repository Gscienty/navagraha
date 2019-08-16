package indi.gscienty.navagraha.dashboard.controllers;

import java.util.List;

import indi.gscienty.navagraha.dashboard.entities.GatewayInfo;
import indi.gscienty.navagraha.dashboard.entities.GatewayForm;
import indi.gscienty.navagraha.dashboard.services.IGatewayService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(value = "/api/gateway")
public class GatewayController {

    @Autowired
    private IGatewayService gatewayService;

    @RequestMapping(value = "/{namespace}", method = RequestMethod.GET)
    public List<GatewayInfo> gatewayListAction(@PathVariable String namespace) {
        return this.gatewayService.get(namespace);
    }

    @RequestMapping(value = "/{namespace}", method = RequestMethod.POST)
    public String gatewaySetAction(@PathVariable String namespace, @RequestBody GatewayForm form) {
        form.setNamespace(namespace);
        this.gatewayService.set(form);
        return "done";
    }

    @RequestMapping(value = "/{namespace}", method = RequestMethod.DELETE)
    public String gatewayRemoveAction(@PathVariable String namespace) {
        this.gatewayService.remove(namespace);
        return "done";
    }
}

