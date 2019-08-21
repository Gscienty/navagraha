package indi.gscienty.navagraha.jni;

import indi.gscienty.navagraha.entities.ProjectInit;
import indi.gscienty.navagraha.entities.ProjectBuild;
import indi.gscienty.navagraha.entities.Config;

public class Project {

    public native String init(ProjectInit init);

    public native String build(Config config, ProjectBuild build);
}
