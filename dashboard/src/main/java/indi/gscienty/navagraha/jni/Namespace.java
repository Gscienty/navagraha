package indi.gscienty.navagraha.jni;

import indi.gscienty.navagraha.entities.Config;

public class Namespace {

    public native String list(Config cfg);

    public native String add(Config cfg, String namespace);

    public native String remove(Config cfg, String namespace);
}
