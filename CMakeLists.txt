cmake_minimum_required(VERSION 3.5)

project(TcpClient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH /home/fumoumou/Qt5.14.2/5.14.2/gcc_64)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)

add_executable(TcpClient
  main.cpp
        UI/login/tcpclient.cpp
        UI/login/tcpclient.h
        UI/login/tcpclient.ui
        func/protocol.h
        func/protocol.cpp
        UI/ope/OpeWidget.cpp
        UI/ope/OpeWidget.h
        UI/book/book.cpp
        UI/book/book.h
        UI/friend/friend.cpp
        UI/friend/friend.h
        UI/online/Online.cpp
        UI/online/Online.h
        UI/online/Online.ui
        UI/privatechat/privatechat.cpp
        UI/privatechat/privatechat.h
        UI/privatechat/privatechat.ui)

target_link_libraries(TcpClient PRIVATE Qt5::Widgets Qt5::Network)
