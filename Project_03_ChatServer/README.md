# Project 03: ChatServer — 聊天室服务器

## 📋 项目简介

一个基于 TCP 和 JSON 协议的聊天服务器，支持多客户端连接、昵称管理、消息广播和用户列表同步。
无界面，纯命令行运行。配套 `Project_03_ChatClient` 使用。

---

## 🗺️ 分步实现路径

### 阶段一：基础功能

- [x] **1. 启动服务器，监听端口**
  - `QTcpServer` 监听 `0.0.0.0:8888`

- [x] **2. 接受客户端连接**
  - 保存客户端 socket，连接信号

- [x] **3. 消息广播**
  - 收到消息后转发给所有客户端

### 阶段二：功能完善

- [x] **4. 处理客户端断开**
  - 清理 socket 和昵称映射
  - 广播用户离线通知

- [x] **5. 昵称管理与用户列表**
  - `NICK` JSON 协议注册昵称
  - 昵称重复/保留名检查
  - `USERLIST` 广播给所有客户端
  - 上下线时自动更新列表

- [ ] **6. 支持私聊转发**
  - 识别 `PRIVATE` 类型消息
  - 只转发给指定的目标客户端

### 阶段三：完善

- [ ] **7. 代码清理与注释**
  - 清理所有 TODO 注释
  - 为每个方法添加注释
  - 整理代码格式

---

## 📂 项目结构

```
Project_03_ChatServer/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp           # 程序入口
    ├── ChatServer.h       # 服务器类声明
    └── ChatServer.cpp     # 服务器类实现
```

---

## 🚀 启动步骤

```bash
cd build_root && cmake .. -G Ninja && cd ..
cmake --build build_root
./build_root/Project_03_ChatServer/Project_03_ChatServer.exe
```

## 📚 参考资源

- QTcpServer: https://doc.qt.io/qt-6/qtcpserver.html
- QTcpSocket: https://doc.qt.io/qt-6/qtcpsocket.html

## 📝 学习要点

| 阶段 | 核心知识点 |
|------|-----------|
| 基础功能 | `QTcpServer` 监听、`QTcpSocket` 读写 |
| 功能完善 | 连接管理、JSON 协议 |
| 完善 | 代码组织、文档编写 |
