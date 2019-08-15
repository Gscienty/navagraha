package indi.gscienty.navagraha.jni;

import indi.gscienty.navagraha.entities.Config;
import indi.gscienty.navagraha.entities.GatewayGet;
import indi.gscienty.navagraha.entities.GatewaySet;
import indi.gscienty.navagraha.entities.GatewayRemove;

public class Gateway {

    public native String get(Config config, GatewayGet gatewayGet);

    public native String set(Config config, GatewaySet gatewaySet);

    public native String remove(Config config, GatewayRemove gatewayRemove);
}
