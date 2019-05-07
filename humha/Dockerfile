FROM centos:7

LABEL version="0.1"
LABEL description="Humha image"
MAINTAINER gaoxiaochuan@hotmail.com

ADD ./ /var/tmp/humha

RUN yum install -y gcc make 
RUN curl -o /var/tmp/nginx.tar.gz -L http://nginx.org/download/nginx-1.15.12.tar.gz
RUN mkdir -p /var/tmp/nginx && tar zxvf /var/tmp/nginx.tar.gz -C /var/tmp
RUN cd /var/tmp/nginx-1.15.12 \
    && ./configure --prefix=/var/lib/nginx \
                   --without-http_rewrite_module \
                   --without-http_gzip_module \
                   --add-module=/var/tmp/humha \
    && make \
    && make install

RUN rm -rf /var/tmp/*

EXPOSE 80/tcp

CMD ["/var/lib/nginx/sbin/nginx", "-g", "\"daemon off;\""]
