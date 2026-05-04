# 🎯 C++ / Qt 学习项目集合

这是一个用于系统学习 C++（特别是 Qt 开发）的项目集合，从简单到复杂，涵盖了 GUI 开发、网络编程、多媒体、数据库、游戏开发等领域。

---

## 📋 项目完成进度

| # | 项目 | 状态 | 学习内容 | 文档 |
|---|------|------|---------|------|
| 01 | 命令行参数解析器 | ✅ **已完成** | Qt 基础、命令行、信号槽 | [查看](Project_01_ArgumentParser/README.md) |
| 02 | 文本编辑器 | ✅ **已完成** | Qt GUI、多标签、查找替换、语法高亮 | [查看](Project_02_TextEditor/README.md) |
| 03s | 聊天服务器 | 🔄 **进行中** | QTcpServer、网络通信 | [查看](Project_03_ChatServer/README.md) |
| 03c | 聊天客户端 | ⬜ 待开始 | QTcpSocket、多线程、UI | [查看](Project_03_ChatClient/README.md) |
| 04 | 音乐播放器 | ⬜ 待开始 | 多媒体、播放器、可视化 | [查看](Project_04_MusicPlayer/README.md) |
| 05 | 任务管理器 | ⬜ 待开始 | 数据库、MVC、拖放 | [查看](Project_05_TaskManager/README.md) |
| 06 | 数据库客户端 | ⬜ 待开始 | 数据库深入、架构设计 | [查看](Project_06_DatabaseClient/README.md) |
| 07 | 游戏引擎基础 | ⬜ 待开始 | 图形编程、碰撞检测、性能优化 | [查看](Project_07_GameEngine/README.md) |

---

## 🚀 构建与运行

### 环境要求

- **编译器**: Clang 15+ / MSVC 2022+ / GCC 11+
- **CMake**: 3.16+
- **Qt**: 6.x（本项目使用 6.10.1 MSVC 版本）
- **构建工具**: Ninja（推荐）或 NMake

### 一键编译所有项目

```bash
# 在项目根目录
cd build_root
cmake .. -G Ninja
cmake --build .
```

### 编译并运行单个项目

```bash
# 编译
cmake --build build_root

# 运行项目1
./build_root/Project_01_ArgumentParser/Project_01_ArgumentParser.exe

# 运行项目2
./build_root/Project_02_TextEditor/Project_02_TextEditor.exe

# 运行项目3s（聊天服务器）
./build_root/Project_03_ChatServer/Project_03_ChatServer.exe
```

### 运行测试

```bash
./build_root/Project_01_ArgumentParser/Project_01_ArgumentParser_tests.exe
```

---

## 🗺️ 推荐学习顺序

| 阶段 | 项目 | 学习重点 | 预计时间 |
|------|------|---------|---------|
| **基础** | 01 命令行参数解析器 | Qt 基本类、QString、QMap | 1 天 |
| **GUI 编程** | 02 文本编辑器 | QMainWindow、QTextEdit、QSyntaxHighlighter | 3-4 天 |
| **网络编程** | 03 聊天服务器 + 客户端 | QTcpServer、QTcpSocket、协议设计 | 3-4 天 |
| **多媒体** | 04 音乐播放器 | QMediaPlayer、音频可视化 | 3-4 天 |
| **数据库** | 05 任务管理器 | QSqlDatabase、SQLite、MVC | 3-4 天 |
| **综合** | 06 数据库客户端 | 多数据库、架构设计 | 4-5 天 |
| **图形** | 07 游戏引擎 | 图形渲染、碰撞检测 | 5-7 天 |

---

## 📁 项目结构

```
Cpp_Learning/
├── CMakeLists.txt                  # 根构建文件（包含所有子项目）
├── .clangd                         # clangd 配置
├── .gitignore
├── README.md                        ← 你在这里
│
├── build_root/                      # 统一构建目录
│   └── compile_commands.json        # clangd 编译信息
│
├── .zed/                            # Zed 编辑器配置
│   ├── settings.json
│   └── tasks.json
│
├── Project_01_ArgumentParser/       # ✅ 已完成
├── Project_02_TextEditor/           # ✅ 已完成
├── Project_03_ChatServer/           # 🔄 进行中
├── Project_03_ChatClient/           # ⬜ 待开始
├── Project_04_MusicPlayer/          # ⬜ 待开始
├── Project_05_TaskManager/          # ⬜ 待开始
├── Project_06_DatabaseClient/       # ⬜ 待开始
└── Project_07_GameEngine/           # ⬜ 待开始
```

---

## 📚 学习资源

### Qt 官方
- [Qt 6 文档](https://doc.qt.io/qt-6/)
- [Qt 示例代码](https://doc.qt.io/qt-6/examples.html)
- [Qt 学习中心](https://learn.qt.io/)

### 书籍
- 《C++ Primer》（第 5 版）
- 《Effective C++》
- 《Qt 6 C++ GUI Programming Cookbook》

### 在线资源
- [CppReference](https://en.cppreference.com/)
- [Qt Forum](https://forum.qt.io/)

---

## 💡 学习建议

1. **按顺序做**：每个项目都依赖前面项目的知识
2. **先通 README**：每个项目都有详细的分步指南
3. **做完再优化**：先让功能跑起来，再回头重构
4. **善用 clangd**：Zed 中的错误提示和代码补全能帮你快速定位问题
5. **用 Git 记录**：每个项目完成后打 tag，方便回顾
