# navagraha

Navagraha（九曜）是基于Kerbernetes和Docker实现的一种函数即服务框架，可将业务逻辑以函数的形式在本框架中实现。该框架使用Prometheus对系统进行资源监控，可准确地获取到每个函数的执行次数、频率、资源使用情况等内容，并可通过这些获取到的系统状况进行自动扩容。

该项目的目标是实现函数计算私有云的开发、部署、维护的一整套解决方案。

## 如何编译

本项目编译后将产出三个结果:

1. nava-cli
2. API Gateway Docker image
3. Humha Docker image

### nava-cli 的编译方式

该模块的依赖包括以下内容：

* cmake
* make
* gcc
* libcurl
* libtar
* libgit2

该可执行文件现阶段仅支持在linux下使用，需要预先安装这些依赖的工具以及第三方链接库后才能正常编译，如果需要在CentOS下进行编译和使用，则可执行如下命令:
```
yum install -y cmake make gcc libcurl-devel libtar-devel libgit2-devel
cmake .
make
```
编译结果将产出名为nava的可执行文件，通过它可以实现Navagraha的开发、部署和维护工作。

### API Gateway Docker image

该模块需要在有Docker的环境下进行，但要求Docker版本在17.05以上，即需要Docker支持多阶段构建。编译方式如下：
```
cd api_gateway
sh build.sh
```

### Humha Docker image
该模块需要在有Docker的环境下进行，但要求Docker版本在17.05以上，即需要Docker支持多阶段构建。编译方式如下：
```
cd humha
sh build.sh
```
