package indi.gscienty.navagraha.jni;

import java.io.File;

public class CommonJNI {
    public static void init() {
        File file = new File("../jni", "libnavajni.so");
        System.load(file.getAbsolutePath());
    }
}
