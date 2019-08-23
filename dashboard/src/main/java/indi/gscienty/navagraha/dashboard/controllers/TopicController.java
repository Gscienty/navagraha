package indi.gscienty.navagraha.dashboard.controllers;


import indi.gscienty.navagraha.dashboard.entities.TopicInfo;
import indi.gscienty.navagraha.dashboard.services.IActionListener;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import org.springframework.web.servlet.ModelAndView;

@RestController
@RequestMapping(value = "/api/topic")
public class TopicController {

    @Autowired
    private IActionListener actionListener;

    @RequestMapping(method = RequestMethod.POST)
    public TopicInfo registerTopicAction() {
        TopicInfo ret = new TopicInfo();
        ret.setTopic(this.actionListener.createTopic());

        return ret;
    }

    @RequestMapping(value = "/{topic}")
    public ModelAndView listenTopicAction(@PathVariable String topic) {
        ModelAndView mav = new ModelAndView("/api/ws-topic");
        mav.addObject("topic", topic);

        return mav;
    }

    //@RequestMapping(value = "/{topic}", produces="text/event-stream")
    //public SseEmitter buildRepoPushAction(@PathVariable String topic, HttpServletResponse response) {
        //SseEmitter event = new SseEmitter();

        //this.actionListener.listenTopic(topic, val -> {
            //if (val == "done") {
                //try {
                    //event.send(SseEmitter.event().name("complete").data("complete"));
                    //event.complete();
                    //this.actionListener.removeTopic(topic);
                //}
                //catch (Exception ex) { ex.printStackTrace(); }

            //}
            //else {
                //try {
                    //event.send(SseEmitter.event().name("data").data(val));
                //}
                //catch (Exception ex) { }
            //}
        //});

        //response.setHeader("Cache-Control", "no-cache");
        //response.setHeader("Pragma", "no-cache");
        //response.setHeader("Expires", "-1");

        //return event;
    //}

}
