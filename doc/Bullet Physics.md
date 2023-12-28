# Bullet Physics

<img src="https://upload.wikimedia.org/wikipedia/commons/5/50/Bullet_Physics_Library_Logo.png">

# 一、简介

开源：zlib license

仓库：https://github.com/bulletphysics/bullet3

官网：http://bulletphysics.org/

## 1、Authors 作者

Erwin Coumans (欧文·库曼斯), Sony -> AMD -> Google -> Nvidia

## 2、Overview 概述

Bullet Physics SDK: real-time collision detection and multi-physics simulation for VR, games, visual effects, robotics, machine learning etc.
> Bullet 物理 SDK：用于 VR、游戏、视觉效果、机器人、机器学习等的实时碰撞检测和多物理模拟。

## 3、Features 特征

### APIs 接口

- **C++** (tested on Windows, Linux, Mac OSX, iOS, Android)
- **Python** (pip3 install pybullet)
- **JavaScript** (ammo.js)

### Experimental OpenCL GPGPU support 实验性支持

The entire collision detection and rigid body dynamics can be executed on the GPU.
> 整个碰撞检测和刚体动力学都可以在 GPU 上执行。

A high-end desktop GPU, such as an AMD Radeon 7970 or NVIDIA GTX 680 or better. We succesfully tested the software under Windows, Linux and Mac OSX. The software currently doesn't work on OpenCL CPU devices. It might run on a laptop GPU but performance will not likely be very good. Note that often an OpenCL drivers fails to compile a kernel. Some unit tests exist to track down the issue, but more work is required to cover all OpenCL kernels.
> 高端桌面 GPU，例如 AMD Radeon 7970 或 NVIDIA GTX 680 或更好。我们在 Windows、Linux 和 Mac OSX 下成功测试了该软件。该软件目前无法在 OpenCL CPU 设备上运行。它可能在笔记本电脑 GPU 上运行，但性能可能不会很好。请注意，OpenCL 驱动程序通常无法编译内核。存在一些单元测试来追踪问题，但需要做更多的工作来覆盖所有 OpenCL 内核。
