# Project 03: Qt网络聊天室客户端

## 📋 项目简介

创建一个支持多用户聊天的客户端，使用TCP连接，支持发送/接收消息、私聊、历史记录等功能。

## 🎯 项目要求

### 基础功能
1. **连接管理**
   - 连接到服务器
   - 显示连接状态
   - 断开连接
   - 重新连接

2. **消息功能**
   - 发送公共消息
   - 发送私聊消息
   - 接收消息
   - 消息显示

3. **用户管理**
   - 显示在线用户列表
   - 选择用户发送私聊
   - 用户头像（可选）
   - 用户昵称

### 进阶功能
1. **聊天功能**
   - 实时消息更新
   - 消息历史记录
   - 消息时间戳
   - 消息类型（公共/私聊/系统）

2. **用户体验**
   - 不同的消息样式
   - 自动滚动到最新消息
   - 离线消息提示
   - 通知声音（可选）

3. **系统功能**
   - 设置昵称
   - 设置头像
   - 断线重连机制
   - 账号验证

### 代码质量要求
1. 遵循Qt编码规范
2. 使用线程管理
3. 代码结构清晰
4. 有适当的注释
5. 支持单元测试

## 📂 项目结构

```
Project_03_ChatClient/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp                    # 主程序入口
    ├── MainWindow.h                # 主窗口头文件
    ├── MainWindow.cpp              # 主窗口实现
    ├── ChatWindow.h                # 聊天窗口头文件
    ├── ChatWindow.cpp              # 聊天窗口实现
    ├── ClientConnection.h          # 客户端连接头文件
    ├── ClientConnection.cpp        # 客户端连接实现
    ├── MessageHandler.h            # 消息处理器头文件
    ├── MessageHandler.cpp          # 消息处理器实现
    ├── UserListWidget.h            # 用户列表头文件
    ├── UserListWidget.cpp          # 用户列表实现
    ├── MessageModel.h              # 消息模型头文件
    ├── MessageModel.cpp            # 消息模型实现
    └── tests/
        ├── test_connection.cpp     # 连接测试
        └── test_message.cpp        # 消息测试
```

## 🔧 技术要点

### 需要学习的知识
1. Qt的Socket编程（QTcpSocket, QTcpServer）
2. Qt的线程管理（QThread）
3. Qt的信号与多线程
4. Qt的定时器
5. Qt的序列化（JSON/XML）
6. Qt的网络协议设计
7. Qt的异步编程

### 设计模式
1. 观察者模式
2. 生产者-消费者模式
3. 工厂模式（消息创建）
4. 单例模式（连接管理）

## 🚀 启动步骤

### 编译
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 运行
```bash
cd build
./Project_03_ChatClient
```

### 服务器准备
- 需要先启动服务器（建议使用Project_03_ChatServer）
- 服务器地址：127.0.0.1
- 服务器端口：8888

## 📚 参考资源

- Qt官方文档：https://doc.qt.io/qt-6/
- Qt Network模块：https://doc.qt.io/qt-6/qtnetwork-index.html
- QTcpSocket：https://doc.qt.io/qt-6/qtcpsocket.html
- QTcpServer：https://doc.qt.io/qt-6/qtcpserver.html
- Qt线程：https://doc.qt.io/qt-6/qthread.html

## 💡 学习建议

1. 先理解客户端-服务器架构
2. 实现基本的连接和消息发送
3. 添加消息接收和显示
4. 实现多用户列表
5. 添加私聊功能
6. 实现断线重连
7. 优化代码结构

## ✅ 验收标准

- [ ] 可以连接到服务器
- [ ] 可以发送和接收消息
- [ ] 可以查看在线用户
- [ ] 可以发送私聊消息
- [ ] 显示消息历史
- [ ] 实现断线重连
- [ ] 代码有良好注释
- [ ] 符合Qt编码规范
