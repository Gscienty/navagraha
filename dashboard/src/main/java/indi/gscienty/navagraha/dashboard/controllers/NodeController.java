package indi.gscienty.navagraha.dashboard.controllers;

import java.util.List;

import indi.gscienty.navagraha.dashboard.services.INodeService;
import indi.gscienty.navagraha.dashboard.entities.NodeInfo;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(value = "/api/node")
public class NodeController {

    @Autowired
    private INodeService node;

    @RequestMapping(method = RequestMethod.GET)
    public List<NodeInfo> getNodeList() {
        return this.node.list();
    }
}
