# Project 04: Qt音乐播放器

## 📋 项目简介

创建一个功能完整的音乐播放器，支持播放列表、播放控制、音量调节、可视化等功能。

## 🎯 项目要求

### 基础功能
1. **音乐加载**
   - 扫描本地音乐文件
   - 支持常见音频格式（MP3, WAV, FLAC, OGG）
   - 显示文件列表
   - 文件信息显示（歌名、艺术家、专辑）

2. **播放控制**
   - 播放/暂停
   - 上一首/下一首
   - 进度条拖动
   - 播放速度调节

3. **音量控制**
   - 音量滑块
   - 静音功能
   - 音量预设

### 进阶功能
1. **播放列表**
   - 播放列表管理
   - 循环模式（单曲循环、列表循环、随机播放）
   - 播放顺序
   - 播放历史

2. **可视化**
   - 频谱分析
   - 波形显示
   - 专辑封面显示

3. **音效**
   - 均衡器
   - 淡入淡出
   - 重低音

### 代码质量要求
1. 遵循Qt编码规范
2. 使用MVC模式
3. 代码结构清晰
4. 有适当的注释
5. 支持单元测试

## 📂 项目结构

```
Project_04_MusicPlayer/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp                    # 主程序入口
    ├── MainWindow.h                # 主窗口头文件
    ├── MainWindow.cpp              # 主窗口实现
    ├── MusicPlayer.h               # 音乐播放器头文件
    ├── MusicPlayer.cpp             # 音乐播放器实现
    ├── PlaylistModel.h             # 播放列表模型头文件
    ├── PlaylistModel.cpp           # 播放列表模型实现
    ├── TrackInfo.h                 # 曲目信息头文件
    ├── TrackInfo.cpp               # 曲目信息实现
    ├── PlaylistWidget.h            # 播放列表组件头文件
    ├── PlaylistWidget.cpp          # 播放列表组件实现
    ├── VisualizerWidget.h          # 可视化组件头文件
    ├── VisualizerWidget.cpp        # 可视化组件实现
    ├── EqualizerDialog.h           # 均衡器对话框头文件
    ├── EqualizerDialog.cpp         # 均衡器对话框实现
    └── tests/
        ├── test_player.cpp         # 播放器测试
        └── test_playlist.cpp       # 播放列表测试
```

## 🔧 技术要点

### 需要学习的知识
1. Qt的Qt Multimedia模块
2. QMediaPlayer和QAudioOutput
3. Qt的QtMultimediaWidgets
4. 音频解码和处理
5. 音频频谱分析
6. Qt的MVC模式
7. Qt的模型视图框架
8. Qt的信号与槽

### 设计模式
1. MVC模式
2. 观察者模式
3. 策略模式（播放策略）
4. 单例模式（播放器实例）

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
./Project_04_MusicPlayer
```

### 注意事项
- 需要系统支持音频解码
- 某些音频格式可能需要额外解码器
- Windows上需要安装DirectShow解码器
- macOS上需要安装QuickTime
- Linux上需要安装GStreamer或FFmpeg

## 📚 参考资源

- Qt官方文档：https://doc.qt.io/qt-6/
- Qt Multimedia模块：https://doc.qt.io/qt-6/qtmultimedia-index.html
- QMediaPlayer：https://doc.qt.io/qt-6/qmediaplayer.html
- QAudioOutput：https://doc.qt.io/qt-6/qaudiooutput.html
- Qt音频可视化：https://doc.qt.io/qt-6/visualize-spectrum.html

## 💡 学习建议

1. 先实现基本的播放功能
2. 再添加播放列表功能
3. 实现播放控制功能
4. 添加可视化功能
5. 实现均衡器
6. 优化用户体验
7. 处理各种音频格式

## ✅ 验收标准

- [ ] 可以加载和播放音乐
- [ ] 支持播放列表
- [ ] 实现播放控制
- [ ] 实现音量控制
- [ ] 显示可视化效果
- [ ] 代码有良好注释
- [ ] 符合MVC设计模式
- [ ] 符合Qt编码规范
