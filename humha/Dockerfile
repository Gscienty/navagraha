FROM alpine

LABEL version="0.1"
LABEL description="Humha image"
MAINTAINER gaoxiaochuan@hotmail.com

ADD ./ /var/tmp/humha

RUN apk add --no-cache gcc make curl musl-dev \
    && curl -o /var/tmp/nginx.tar.gz -L http://nginx.org/download/nginx-1.15.12.tar.gz \
    && mkdir -p /var/tmp/nginx && tar zxvf /var/tmp/nginx.tar.gz -C /var/tmp \
    && cd /var/tmp/nginx-1.15.12 \
    && ./configure --prefix=/var/lib/nginx \
                   --without-http_rewrite_module \
                   --without-http_gzip_module \
                   --add-module=/var/tmp/humha \
    && make \
    && make install \
    && rm -rf /var/tmp/* \
    && apk del gcc make curl musl-dev
