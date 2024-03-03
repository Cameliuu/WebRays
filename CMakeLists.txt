cmake_minimum_required(VERSION 3.25)
project(WebRays)

set(CMAKE_CXX_STANDARD 17)

add_executable(WebRays main.cpp App/App.h Image/Image.h App/App.cpp Color/Color.h Image/Image.cpp Color/Color.cpp Scene/Scene.h Vector3/Vector3.cpp Scene/Scene.cpp Ray/Ray.h Ray/Ray.cpp Objects/Object.h Objects/Sphere.h Objects/Sphere.cpp Objects/Object.cpp Ray/HitInfo.h Ray/HitInfo.cpp)
