FROM python:3-alpine

LABEL navafunc=python3

RUN mkdir -p /home/app/function/
WORKDIR /home/app/function/
COPY . .
RUN pip3 install -r requirements.txt
COPY --from=nava/humha:v0.1 /var/lib/nginx /var/lib/nginx
ENV HUMHA_EXEC="/usr/local/bin/python3" \
    HUMHA_NAME="python3" \
    HUMHA_ARGS="/home/app/function/index.py"
EXPOSE 80
CMD /var/lib/nginx/sbin/nginx -g "daemon off;"
