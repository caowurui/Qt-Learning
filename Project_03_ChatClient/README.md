# Project 03: Qt网络聊天室客户端

## 📋 项目简介

创建一个基于 TCP 协议的网络聊天室客户端，支持连接服务器、收发消息、在线用户列表和私聊功能。

> ⚠️ 本项目仅包含**客户端**代码。你需要一个服务器来测试。建议完成后端项目 `Project_03_ChatServer`，
> 或使用一个简单的 TCP 测试工具（如 `netcat`）在本地启动一个回显服务器：
> ```bash
> nc -l -p 8888
> ```

---

## 🗺️ 分步实现路径

### 阶段一：网络连接基础

- [ ] **1. 创建主窗口框架**
  - 创建 `main.cpp` 和 `MainWindow`
  - 左侧是用户列表区域，右侧是聊天区域
  - 顶部是连接控制区域（服务器地址、端口、连接/断开按钮）
  - 涉及类：`QMainWindow`, `QWidget`, `QLineEdit`, `QPushButton`

- [ ] **2. 实现 TCP 连接**
  - 创建 `ClientConnection` 类，封装 `QTcpSocket`
  - 实现 `connectToServer(host, port)` 方法
  - 实现 `disconnectFromServer()` 方法
  - 监听 `connected`、`disconnected`、`errorOccurred` 信号
  - 连接成功后，禁用"连接"按钮，启用"断开"按钮
  - 涉及类：`QTcpSocket`, `QHostAddress`

- [ ] **3. 收发文本消息**
  - 实现 `sendMessage(QString text)` 方法，通过 socket 写入数据
  - 监听 socket 的 `readyRead` 信号，读取服务器发来的数据
  - 在状态栏显示连接状态（已连接/未连接）
  - 涉及类：`QTcpSocket::write()`, `readyRead`, `QDataStream`

### 阶段二：聊天 UI

- [ ] **4. 显示收到的消息**
  - 创建一个只读的 `QTextEdit` 或 `QListWidget` 作为消息显示区域
  - 将收到的消息追加到显示区域
  - 每条消息显示为 `[昵称]: 消息内容` 的格式
  - 自动滚动到底部，显示最新消息
  - 涉及类：`QTextEdit`（只读模式）, `QScrollBar`

- [ ] **5. 发送消息界面**
  - 聊天区域底部添加文本输入框和"发送"按钮
  - 按 `Enter` 键或点击"发送"按钮发送消息
  - 发送成功后清空输入框
  - 涉及类：`QLineEdit`, `QPushButton`, `QShortcut`

- [ ] **6. 用户列表显示**
  - 左侧添加 `QListWidget` 显示在线用户
  - 服务器发送用户列表时，更新显示
  - 当前用户自己显示在列表第一位或特殊标记
  - 涉及类：`QListWidget`, `QSplitter`（分割左右区域）

### 阶段三：功能完善

- [ ] **7. 区分消息类型（公共/私聊/系统）**
  - 定义简单的文本协议格式，如：
    - 公共消息：`PUBLIC|sender|content`
    - 私聊消息：`PRIVATE|sender|receiver|content`
    - 系统消息：`SYSTEM|content`
    - 用户列表：`USERLIST|user1,user2,user3`
  - 在 `MessageHandler` 中解析消息类型
  - 不同类型的消息用不同颜色或前缀显示
  - 涉及类：`QString::split()`, `QTextCharFormat`

- [ ] **8. 私聊功能**
  - 双击用户列表中的某个用户，自动在输入框中填入 `/w 用户名 `
  - 发送私聊消息时，消息显示区域标注"私聊给 XXX"
  - 收到私聊时，标注"XXX 私聊给你"
  - 涉及类：`QListWidget::itemDoubleClicked`

- [ ] **9. 连接状态与断线重连**
  - 在状态栏显示当前连接状态（绿色=已连接，红色=已断开）
  - 添加 `QTimer`，断开连接后每隔 3 秒自动重试连接
  - 重连成功后停止定时器
  - 涉及类：`QTimer`, `QStatusBar`, `QLabel`

### 阶段四：完善

- [ ] **10. 昵称设置**
  - 启动时弹出一个对话框输入昵称
  - 连接时发送昵称到服务器
  - 涉及类：`QInputDialog`

- [ ] **11. 消息历史与时间戳**
  - 每条消息前显示时间戳 `[HH:mm]`
  - 在内存中保存最近 100 条消息
  - 涉及类：`QDateTime`, `QList<QString>`

- [ ] **12. 代码清理与注释**
  - 清理所有 TODO 注释
  - 为每个类和方法添加文档注释
  - 整理代码格式

---

## 📂 项目结构

```
Project_03_ChatClient/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp                    # 主程序入口
    ├── MainWindow.h/cpp            # 主窗口
    ├── ClientConnection.h/cpp      # TCP 连接管理
    ├── MessageHandler.h/cpp        # 消息解析与格式化
    └── tests/
        └── test_connection.cpp     # 连接测试
```

---

## 📚 参考资源

- Qt官方文档：https://doc.qt.io/qt-6/
- Qt Network模块：https://doc.qt.io/qt-6/qtnetwork-index.html
- QTcpSocket：https://doc.qt.io/qt-6/qtcpsocket.html
- Qt线程：https://doc.qt.io/qt-6/qthread.html

## 📝 学习要点

| 阶段 | 核心知识点 |
|------|-----------|
| 网络连接 | `QTcpSocket`、信号与槽的异步通信 |
| 聊天 UI | 控件布局、`QTextEdit` 只读模式 |
| 功能完善 | 文本协议设计、`QTimer` 重连机制 |
| 完善 | 数据持久化、代码组织、文档编写 |
