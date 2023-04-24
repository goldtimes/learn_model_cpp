#!/bin/bash

set -o errexit

source "/opt/ros/${ROS_DISTRO}/setup.bash"
## exec执行命令 $@表示传入的所有参数
## ./shell_learn.sh echo "lihang" 相当于执行echo "lihang"的命令
exec "$@"