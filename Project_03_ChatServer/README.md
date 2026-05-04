# Project 03: ChatServer — 聊天室服务器

## 📋 项目简介

一个简单的 TCP 聊天服务器，支持多客户端连接、消息广播和私聊。
无界面，纯命令行运行。配套 `Project_03_ChatClient` 使用。

---

## 🗺️ 分步实现路径

### 阶段一：基础功能

- [x] **1. 启动服务器，监听端口**
  - 创建 `QTcpServer`，监听 `0.0.0.0:8888`
  - 控制台输出 `Server started on port 8888`
  - 涉及类：`QTcpServer`, `QHostAddress`

- [x] **2. 接受客户端连接**
  - 连接 `newConnection` 信号
  - 获取 `nextPendingConnection()`，存入客户端列表
  - 为新客户端连接 `readyRead` 和 `disconnected` 信号
  - 客户端连接时，控制台输出 `Client connected: 127.0.0.1:xxxxx`
  - 涉及类：`QTcpSocket`, `QList<QTcpSocket*>`

- [x] **3. 消息广播**
  - 收到某客户端消息后，转发给**其他所有**客户端
  - 控制台输出收到的消息内容
  - 涉及方法：`QTcpSocket::readAll()`, `write()`

### 阶段二：功能完善

- [ ] **4. 处理客户端断开**
  - 从客户端列表中移除已断开的 socket
  - 通知其他客户端该用户已离线
  - 控制台输出 `Client disconnected: 127.0.0.1:xxxxx`

- [ ] **5. 解析并转发用户列表**
  - 维护一个用户名 → socket 的映射表
  - 客户端连接时先发送昵称
  - 用户上下线时，广播最新的用户列表给所有客户端

- [ ] **6. 支持私聊转发**
  - 识别消息中的私聊标记（如 `@用户名 消息内容`）
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
# 编译
cd build_root && cmake .. -G Ninja && cd ..
cmake --build build_root

# 运行
./build_root/Project_03_ChatServer/Project_03_ChatServer.exe
```

## 📚 参考资源

- QTcpServer: https://doc.qt.io/qt-6/qtcpserver.html
- QTcpSocket: https://doc.qt.io/qt-6/qtcpsocket.html

## 📝 学习要点

| 阶段 | 核心知识点 |
|------|-----------|
| 基础功能 | `QTcpServer` 监听、`QTcpSocket` 读写 |
| 功能完善 | 连接管理、协议设计 |
| 完善 | 代码组织、文档编写 |
