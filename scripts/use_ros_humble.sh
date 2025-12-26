#!/usr/bin/env bash
# 快捷脚本：切换到 ROS 2 humble 并（可选）source 工作区安装的 local_setup
if [ -f /opt/ros/humble/setup.bash ]; then
  source /opt/ros/humble/setup.bash
fi

# 尝试 source 工作区的安装/本地 setup（相对于脚本在 workspace/scripts 下）
WS_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
if [ -f "${WS_ROOT}/install/setup.bash" ]; then
  source "${WS_ROOT}/install/setup.bash"
elif [ -f "${WS_ROOT}/install/local_setup.bash" ]; then
  source "${WS_ROOT}/install/local_setup.bash"
fi

echo "Sourced ROS_DISTRO=${ROS_DISTRO:-unknown}"
