# Project 02: Qt文本编辑器

## 📋 项目简介

创建一个支持基本文本编辑、文件保存和简单语法高亮的文本编辑器。

---

## 🗺️ 分步实现路径

### 阶段一：窗口框架（基础）

- [x] **1. 显示带编辑区的窗口**
  - 创建 `main.cpp`：启动 `QApplication`，创建并显示 `MainWindow`
  - 创建 `MainWindow.h` / `MainWindow.cpp`：继承 `QMainWindow`，中间放一个 `QTextEdit` 作为编辑区
  - 涉及类：`QApplication`, `QMainWindow`, `QTextEdit`

- [x] **2. 添加退出菜单**
  - 在 `createMenuBar()` 中创建"文件"菜单，添加"退出"选项
  - 绑定 `Ctrl+Q` 快捷键
  - 涉及类：`QMenuBar`, `QMenu`, `QAction`, `QKeySequence`

- [x] **3. 添加新建、打开、保存功能**
  - 文件菜单中添加"新建(Ctrl+N)"、"打开(Ctrl+O)"、"保存(Ctrl+S)"
  - 实现 `newFile()`：清空编辑器，重置标题
  - 实现 `openFile()`：弹出文件对话框，读取文件内容到编辑器
  - 实现 `saveFile()`：将编辑器内容写入文件（首次保存弹"另存为"对话框）
  - 涉及类：`QFileDialog`, `QFile`, `QTextStream`, `QMessageBox`

### 阶段二：编辑增强

- [x] **4. 添加剪切/复制/粘贴/撤销/重做**
  - 在菜单栏添加"编辑"菜单
  - 添加"撤销(Ctrl+Z)"、"重做(Ctrl+Y)"、"剪切(Ctrl+X)"、"复制(Ctrl+C)"、"粘贴(Ctrl+V)"
  - `QTextEdit` 已内置这些操作，只需调用对应槽函数
  - 涉及类：`QTextEdit`（`undo()`, `redo()`, `cut()`, `copy()`, `paste()`）

- [x] **5. 添加状态栏**
  - 在窗口底部显示光标所在的行号、列号
  - 监听 `QTextEdit` 的光标位置变化信号 `cursorPositionChanged()`
  - 涉及类：`QStatusBar`, `QLabel`, `QTextEdit`

- [ ] **6. 添加查找/替换对话框**
  - 编辑菜单中添加"查找(Ctrl+F)"和"替换(Ctrl+H)"
  - 弹出对话框，输入查找内容和替换内容
  - 使用 `QTextDocument::find()` 进行查找
  - 涉及类：`QDialog`, `QLineEdit`, `QPushButton`, `QTextCursor`

### 阶段三：语法高亮

- [ ] **7. 实现基础语法高亮**
  - 创建 `SyntaxHighlighter` 类，继承 `QSyntaxHighlighter`
  - 为 C++ 关键字（`int`, `return`, `if`, `class` 等）设置颜色
  - 为字符串字面量和注释设置颜色
  - 涉及类：`QSyntaxHighlighter`, `QTextCharFormat`, `QRegularExpression`

- [ ] **8. 添加行号显示**
  - 在编辑器左侧显示行号区域
  - 监听编辑器的滚动和内容变化，同步更新行号
  - 涉及类：`QWidget`（自定义绘制）, `QPainter`, `QTextBlock`

### 阶段四：完善

- [ ] **9. 添加文件标签页**
  - 支持同时打开多个文件，用标签页切换
  - 涉及类：`QTabWidget`

- [ ] **10. 代码清理与注释**
  - 清理所有 TODO 注释
  - 为每个类和方法添加文档注释
  - 整理代码格式

---

## 📂 项目结构

```
Project_02_TextEditor/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp                    # 主程序入口
    ├── MainWindow.h                # 主窗口头文件
    ├── MainWindow.cpp              # 主窗口实现
    └── tests/
        └── test_editor.cpp         # 编辑器测试
```

*（后续步骤中可能需要添加更多文件，如 `SyntaxHighlighter.h/cpp` 等）*

---

## 📚 参考资源

- Qt官方文档：https://doc.qt.io/qt-6/
- Qt Widgets模块：https://doc.qt.io/qt-6/qtwidgets-index.html
- QTextDocument：https://doc.qt.io/qt-6/qtextdocument.html
- QTextCursor：https://doc.qt.io/qt-6/qtextcursor.html
- QSyntaxHighlighter：https://doc.qt.io/qt-6/qsyntaxhighlighter.html
- Qt事件系统：https://doc.qt.io/qt-6/eventsandsignals.html

---

## 📝 学习要点

### 每阶段学到的知识

| 阶段 | 核心知识点 |
|------|-----------|
| 窗口框架 | `QMainWindow` 结构、菜单栏、`QTextEdit`、文件I/O |
| 编辑增强 | 信号与槽、状态栏、`QTextCursor` 操作 |
| 语法高亮 | `QSyntaxHighlighter`、正则表达式、文本格式 |
| 完善 | 多标签管理、代码组织、文档编写 |
