package indi.gscienty.navagraha.dashboard;

import indi.gscienty.navagraha.jni.CommonJNI;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.servlet.ServletComponentScan;
import org.springframework.scheduling.annotation.EnableAsync;

@SpringBootApplication
@ServletComponentScan
@EnableAutoConfiguration
@EnableAsync
public class App {

    public static void main(String[] args) {
        CommonJNI.init();
        SpringApplication.run(App.class, args);
    }
}
