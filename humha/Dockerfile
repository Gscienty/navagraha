FROM alpine

ADD ./ /var/tmp/humha

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.ustc.edu.cn/g' /etc/apk/repositories \
    && apk add --no-cache gcc make curl musl-dev \
    && curl -o /var/tmp/nginx.tar.gz -L http://nginx.org/download/nginx-1.17.0.tar.gz \
    && mkdir -p /var/tmp/nginx && tar zxvf /var/tmp/nginx.tar.gz -C /var/tmp \
    && cd /var/tmp/nginx-1.17.0 \
    && ./configure --prefix=/var/lib/nginx \
                   --without-http-cache \
                   --without-http_charset_module \
                   --without-http_gzip_module \
                   --without-http_ssi_module \
                   --without-http_userid_module \
                   --without-http_access_module \
                   --without-http_auth_basic_module \
                   --without-http_mirror_module \
                   --without-http_autoindex_module \
                   --without-http_status_module \
                   --without-http_geo_module \
                   --without-http_map_module \
                   --without-http_referer_module \
                   --without-http_rewrite_module \
                   --without-http_fastcgi_module \
                   --without-http_uwsgi_module \
                   --without-http_scgi_module \
                   --without-http_grpc_module \
                   --without-http_memcached_module \
                   --without-http_limit_conn_module \
                   --without-http_limit_req_module \
                   --without-http_empty_gif_module \
                   --without-http_browser_module \
                   --without-http_upstream_hash_module \
                   --without-http_upstream_ip_hash_module \
                   --without-http_upstream_least_conn_module \
                   --without-http_upstream_random_module \
                   --without-http_upstream_keepalive_module \
                   --without-http_upstream_zone_module \
                   --without-mail_pop3_module \
                   --without-mail_imap_module \
                   --without-mail_smtp_module \
                   --without-stream_limit_conn_module \
                   --without-stream_access_module \
                   --without-stream_geo_module \
                   --without-stream_map_module \
                   --without-stream_split_clients_module \
                   --without-stream_return_module \
                   --without-stream_upstream_hash_module \
                   --without-stream_upstream_least_conn_module \
                   --without-stream_upstream_random_module \
                   --without-stream_upstream_zone_module \
                   --add-module=/var/tmp/humha \
    && make \
    && make install \
    && rm -rf /var/lib/nginx/conf/* \
    && rm -rf /var/lib/nginx/html \
    && cp /var/tmp/humha/compact_nginx.conf /var/lib/nginx/conf/nginx.conf \
    && rm -rf /var/tmp/* \
    && apk del gcc make curl musl-dev

