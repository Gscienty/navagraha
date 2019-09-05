package indi.gscienty.navagraha.dashboard.services;

import java.util.List;

import com.alibaba.fastjson.JSON;

import org.springframework.stereotype.Service;

import indi.gscienty.navagraha.dashboard.ConfigSingleton;
import indi.gscienty.navagraha.dashboard.entities.NodeInfo;
import indi.gscienty.navagraha.dashboard.services.INodeService;
import indi.gscienty.navagraha.jni.Node;

@Service
public class NodeService implements INodeService {

    public List<NodeInfo> list() {
        Node node = new Node();
        String result = node.list(ConfigSingleton.getInstance().getConfig());
        return JSON.parseArray(result, NodeInfo.class);
    }
}

