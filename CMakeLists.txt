cmake_minimum_required(VERSION 3.16)

project(plasma-krunner-shuangpin)

set(PROJECT_VERSION "1.0")
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

set(QT_MIN_VERSION "5.15.0")
set(KF_MIN_VERSION "5.80.0")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 先查找 ECM，这是使用 KF5 的前提
find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Gui
    DBus
)

find_package(KF5 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    Runner
    I18n
    Service
)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 相关设置
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# 源文件
set(shuangpin_runner_SRCS
    src/shuangpin.cpp
    src/shuangpin_runner.cpp
)

set(shuangpin_runner_HDRS
    src/shuangpin.h
    src/shuangpin_runner.h
)

# 创建插件库
add_library(plasma_runner_shuangpin MODULE ${shuangpin_runner_SRCS})

target_link_libraries(plasma_runner_shuangpin
    Qt5::Core
    Qt5::Gui
    Qt5::DBus
    KF5::Runner
    KF5::I18n
    KF5::Service
)

# 安装插件库到系统目录
install(TARGETS plasma_runner_shuangpin
    DESTINATION /usr/lib/x86_64-linux-gnu/qt5/plugins/kf5/krunner
)

