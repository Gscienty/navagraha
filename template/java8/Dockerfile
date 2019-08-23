FROM openjdk:8u131-jdk-alpine as builder

LABEL navafunc=java8

ENV GRADLE_HOME=/opt/gradle-4.8.1/
ENV PATH=$PATH:$GRADLE_HOME/bin
ENV GRADLE_OPTS="-Dorg.gradle.daemon=false"
ENV HUMHA_EXEC="http://localhost:8000"

EXPOSE 80

WORKDIR /app
COPY . /appsource
COPY --from=nava/humha:v0.1 /var/lib/nginx /var/lib/nginx

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories \
    && apk --no-cache add curl \
    && mkdir -p /opt/ && cd /opt/ \
    && curl -SfL https://services.gradle.org/distributions/gradle-4.8.1-bin.zip -o gradle-bin.zip \
    && unzip gradle-bin.zip -d /opt/ \
    && rm gradle-bin.zip \
    && apk del curl \
    && cd /appsource \
    && gradle build \
    && cp /appsource/enter/build/distributions/enter-1.0.tar /app/enter-1.0.tar \
    && cd /app \
    && tar xvf ./enter-1.0.tar

CMD  /var/lib/nginx/sbin/nginx && enter-1.0/bin/enter -XX:+UnlockExperimentalVMOptions -XX:+UseCGroupMemoryLimitForHeap
