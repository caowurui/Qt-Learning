# Project 04: Qt音乐播放器

## 📋 项目简介

创建一个功能完整的音乐播放器，支持音频文件加载、播放控制、播放列表、音量和可视化功能。

---

## 🗺️ 分步实现路径

### 阶段一：播放核心

- [ ] **1. 创建主窗口框架**
  - 创建 `main.cpp` 和 `MainWindow`
  - 设计布局：顶部是播放控制栏，中部是播放列表/专辑封面，底部是进度条
  - 涉及类：`QMainWindow`, `QVBoxLayout`, `QHBoxLayout`

- [ ] **2. 实现基础播放功能**
  - 创建 `MusicPlayer` 类，封装 `QMediaPlayer` 和 `QAudioOutput`
  - 实现播放/暂停/停止
  - 加载本地音频文件路径
  - 涉及类：`QMediaPlayer`, `QAudioOutput`, `QUrl`

- [ ] **3. 添加播放控制按钮**
  - 界面中添加播放/暂停、上一首、下一首按钮
  - 连接按钮到 `MusicPlayer` 的对应方法
  - 显示当前播放状态（播放中/已暂停）
  - 涉及类：`QPushButton`, `QLabel`

### 阶段二：进度与音量

- [ ] **4. 实现进度条控制**
  - 显示当前播放位置和总时长
  - `QSlider` 显示播放进度，可拖动跳转
  - 连接 `QMediaPlayer::positionChanged` 和 `durationChanged` 信号
  - 涉及类：`QSlider`, `QLabel`

- [ ] **5. 实现音量控制**
  - 添加音量滑块和静音按钮
  - 通过 `QAudioOutput::setVolume()` 控制音量
  - 涉及类：`QSlider`, `QPushButton`

### 阶段三：播放列表

- [ ] **6. 加载音乐文件**
  - 点击"打开文件"或"打开文件夹"按钮，选择音频文件
  - 支持格式：MP3、WAV、FLAC、OGG
  - 显示文件信息（歌名、时长）
  - 涉及类：`QFileDialog`, `QFileInfo`, `QDir`

- [ ] **7. 播放列表管理**
  - 创建 `PlaylistModel` 管理歌曲列表
  - 显示在 `QListWidget` 或 `QTableView` 中
  - 点击列表项直接播放
  - 支持删除歌曲、清空列表
  - 涉及类：`QListWidget`, `QFileInfo`

- [ ] **8. 循环与切换模式**
  - 上一首/下一首切换
  - 循环模式切换：单曲循环、列表循环、随机播放
  - 当前歌曲播放完毕后自动切到下一首
  - 涉及类：`QMediaPlayer::mediaStatusChanged`

### 阶段四：增强功能

- [ ] **9. 专辑封面显示**
  - 读取音频文件的封面图片（如有）
  - 在界面中显示专辑封面
  - 涉及类：`QMediaMetaData`, `QPixmap`, `QLabel`

- [ ] **10. 音频可视化（可选）**
  - 使用 `QAudioProbe` 获取音频数据
  - 在自定义 `QWidget` 中绘制频谱或波形
  - 涉及类：`QAudioProbe`, `QPainter`

### 阶段五：完善

- [ ] **11. 代码清理与注释**
  - 清理所有 TODO 注释
  - 为每个类和方法添加文档注释
  - 整理代码格式

---

## 📂 项目结构

```
Project_04_MusicPlayer/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp                    # 程序入口
    ├── MainWindow.h/cpp            # 主窗口
    ├── MusicPlayer.h/cpp           # 播放器封装
    └── tests/
        └── test_player.cpp         # 播放器测试
```

---

## 🔧 涉及类速查

| 类 | 用途 |
|------|------|
| `QMediaPlayer` | 核心播放器，控制播放/暂停/跳转 |
| `QAudioOutput` | 音频输出，控制音量和静音 |
| `QSlider` | 进度条和音量滑块 |
| `QFileDialog` | 选择音乐文件或文件夹 |
| `QMediaMetaData` | 读取音频元信息（歌名、专辑、封面） |
| `QAudioProbe` | 获取音频数据用于可视化 |

## 📚 参考资源

- [Qt Multimedia 模块](https://doc.qt.io/qt-6/qtmultimedia-index.html)
- [QMediaPlayer](https://doc.qt.io/qt-6/qmediaplayer.html)
- [QAudioOutput](https://doc.qt.io/qt-6/qaudiooutput.html)

## 📝 学习要点

| 阶段 | 核心知识点 |
|------|-----------|
| 播放核心 | `QMediaPlayer`、`QAudioOutput`、状态管理 |
| 进度与音量 | 信号与槽的实时更新、滑块交互 |
| 播放列表 | 文件 I/O、列表模型、播放模式切换 |
| 增强功能 | 元数据读取、自定义绘制 |
