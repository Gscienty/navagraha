package indi.gscienty.navagraha.jni;

import indi.gscienty.navagraha.entities.Config;
import indi.gscienty.navagraha.entities.FuncUp;

public class Func {
    public native String up(Config cfg, FuncUp funcUp);
}
