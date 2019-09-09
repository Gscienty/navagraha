package indi.gscienty.navagraha.jni;

import indi.gscienty.navagraha.entities.Config;

public class Monitor {
    public native String add(Config config, String namespace);

    public native String remove(Config config, String namespace);

    public native String get(Config config, String namespace);

    public native int nodeCount(Config config);

    public native int namespaceCount(Config config);

    public native int funcCount(Config config);
    
    public native int projectCount(Config config);
}
