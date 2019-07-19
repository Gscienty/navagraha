#!/usr/bin/env sh

# 确保脚本抛出遇到的错误
set -e

npm run docs:build
cd dcos/.vuepress/dist

git init

# git pull git@github.com:Gscienty/navagraha.git master
git add -A
git commit -m 'deploy'
git push -f git@github.com:Gscienty/navagraha.git master:gh-pages

cd -
