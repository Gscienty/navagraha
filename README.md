# navagraha

Navagraha（九曜）是基于Kerbernetes和Docker实现的一种函数即服务框架，可将业务逻辑以函数的形式在本框架中实现。该框架使用Prometheus对系统进行资源监控，可准确地获取到每个函数的执行次数、频率、资源使用情况等内容，并可通过这些获取到的系统状况进行自动扩容。

该项目的目标是实现函数计算私有云的开发、部署、维护的一整套解决方案。

## 如何编译

本项目编译后将产出三个结果:

1. nava-cli
2. API Gateway Docker image
3. Humha Docker image
