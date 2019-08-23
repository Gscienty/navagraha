package indi.gscienty.navagraha.dashboard.controllers;

import java.util.List;

import java.util.UUID;

import indi.gscienty.navagraha.dashboard.entities.BuildRepoForm;
import indi.gscienty.navagraha.dashboard.entities.FuncRepoInfo;
import indi.gscienty.navagraha.dashboard.entities.GatewayRepoInfo;
import indi.gscienty.navagraha.dashboard.services.IActionListener;
import indi.gscienty.navagraha.dashboard.services.IFuncService;
import indi.gscienty.navagraha.dashboard.services.IGatewayService;
import indi.gscienty.navagraha.dashboard.websocket.WebSocketService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.concurrent.ThreadPoolTaskExecutor;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(value = "/api/repo")
public class RepoController {

    @Autowired
    private IFuncService funcService;

    @Autowired
    private IGatewayService gatewayService;

    @Autowired
    private ThreadPoolTaskExecutor threadPool;

    @Autowired
    private IActionListener actionListener;

    @RequestMapping(value = "/func", method = RequestMethod.GET)
    public List<FuncRepoInfo> funcRepoAction() {
        return this.funcService.repo();
    }

    @RequestMapping(value = "/apigw", method = RequestMethod.GET)
    public List<GatewayRepoInfo> gatewayRepoAction() {
        return this.gatewayService.repo();
    }

    @RequestMapping(value = "/build/{topic}", method = RequestMethod.POST)
    public String buildRepoAction(@PathVariable String topic, @RequestBody BuildRepoForm form) {

        this.actionListener.listenTopic(topic, message -> {
            if (message == "done") {
                WebSocketService.sendInfo(topic, "complete:complete");

                WebSocketService.topicOffline(topic);
            }
            else {
                WebSocketService.sendInfo(topic, "data:" + message);
            }
        });

        this.threadPool.execute(() -> {
            String path = "/tmp/nava-build-" + UUID.randomUUID().toString();
            this.funcService.repoInit(form.getType(), path);
            this.funcService.repoFillContent(form.getType(), path, form.getContent());
            this.funcService.repoBuild(form.getName(), form.getVersion(), path, val -> {
                this.actionListener.pushMessage(topic, val);
            });
            this.funcService.repoRemove(path);
            this.actionListener.pushMessage(topic, "done");
        });

        return "done";
    }


}

