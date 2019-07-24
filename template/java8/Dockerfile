FROM openjdk:8u131-jdk-alpine as builder

LABEL navafunc=java8

ENV GRADLE_HOME=/opt/gradle-4.8.1/
ENV PATH=$PATH:$GRADLE_HOME/bin
ENV GRADLE_OPTS="-Dorg.gradle.daemon=false"

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.ustc.edu.cn/g' /etc/apk/repositories \
    && apk --no-cache add curl \
    && mkdir -p /opt/ && cd /opt/ \
    && curl -SfL https://services.gradle.org/distributions/gradle-4.8.1-bin.zip -o gradle-bin.zip \
    && unzip gradle-bin.zip -d /opt/ \
    && rm gradle-bin.zip \
    && apk del curl \
    && mkdir -p /app/libs

WORKDIR /app
COPY . /app

RUN gradle build

FROM openjdk:8u131-jdk-alpine as ship

WORKDIR /app
COPY --from=builder /app/enter/build/distributions/enter-1.0.tar ./enter-1.0.tar
COPY --from=nava/humha:v0.1 /var/lib/nginx /var/lib/nginx
RUN tar xvf ./enter-1.0.tar
ENV HUMHA_EXEC="http://localhost:8000"
EXPOSE 80
CMD enter-1.0/bin/enter -XX:+UnlockExperimentalVMOptions -XX:+UseCGroupMemoryLimitForHeap & /var/lib/nginx/sbin/nginx -g "daemon off;"
