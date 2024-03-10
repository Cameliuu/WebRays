#!/bin/bash
em++ -o main.html main.cpp App/App.cpp Image/image.cpp Color/color.cpp Vector3/Vector3.cpp Scene/Scene.cpp Ray/Ray.cpp Ray/HitInfo.cpp Objects/Object.cpp Objects/Sphere.cpp Camera/Camera.cpp -sUSE_SDL=2 -sALLOW_MEMORY_GROWTH=1 -sASYNCIFY -O3 -sUSE_PTHREADS=1 --shell-file Shell/shell.html
docker stop my-webtracer-app;
docker rm my-webtracer-app;
docker build -t my-webtracer-app . ;
docker run -d --name my-webtracer-app -p 8080:80 my-webtracer-app;
