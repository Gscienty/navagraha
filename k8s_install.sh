#!/bin/sh

cat <<EOF > /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://mirrors.aliyun.com/kubernetes/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://mirrors.aliyun.com/kubernetes/yum/doc/yum-key.gpg https://mirrors.aliyun.com/kubernetes/yum/doc/rpm-package-key.gpg
EOF

yum install -y kubelet kubeadm kubectl

kubeadm config images list | sed -e 's/^/docker pull /g' -e 's#k8s.gcr.io#docker.io/mirrorgooglecontainers#g' | sh -x

docker images |grep mirrorgooglecontainers |awk '{print "docker tag",$1":"$2,$1":"$2}' |sed -e 's/mirrorgooglecontainers/k8s.gcr.io/2' |sh -x
docker images |grep mirrorgooglecontainers |awk '{print "docker rmi """$1""":"""$2}' |sh -x
docker pull coredns/coredns:1.3.1
docker tag coredns/coredns:1.3.1 k8s.gcr.io/coredns:1.3.1
docker rmi coredns/coredns:1.3.1

swapoff -a
setenforce 0

systemctl start kubelet

kubeadm init --pod-network-cidr=10.244.0.0/16

sysctl net.bridge.bridge-nf-call-iptables=1

# master
kubectl taint nodes --all node-role.kubernetes.io/master-

kubectl apply -f https://docs.projectcalico.org/v3.8/manifests/calico.yaml

