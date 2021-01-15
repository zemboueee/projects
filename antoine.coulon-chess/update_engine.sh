#!/bin/sh
git push
git tag -a "engine-myTinyCoreWarV$1" -m "ok"
git push --tags
