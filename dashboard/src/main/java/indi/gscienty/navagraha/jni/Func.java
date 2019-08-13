package indi.gscienty.navagraha.jni;

import indi.gscienty.navagraha.entities.Config;
import indi.gscienty.navagraha.entities.FuncUp;
import indi.gscienty.navagraha.entities.FuncDown;

public class Func {

    public native String up(Config cfg, FuncUp funcUp);

    public native String down(Config cfg, FuncDown funcDown);

    public native String repo(Config cfg);
}
