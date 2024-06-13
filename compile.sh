#!/bin/bash

name=$1

rm -rf "${name}.*"

em++ -o "${name}.html" main.cpp App/App.cpp Objects/Plane.cpp Lights/DirectionalLight.cpp Lights/PointLight.cpp Image/image.cpp Color/color.cpp Vector3/Vector3.cpp Scene/Scene.cpp Ray/Ray.cpp Ray/HitInfo.cpp Objects/Object.cpp Objects/Sphere.cpp Camera/Camera.cpp Materials/material.cpp  -sUSE_SDL=2 --shell-file Shell/shell.html --preload-file materials.json -w --bind -sPTHREAD_POOL_SIZE_STRICT=0 -fsanitize=address -sALLOW_MEMORY_GROWTH=1 -sASYNCIFY -O3 -sUSE_PTHREADS=1 -sNO_EXIT_RUNTIME

python main.py --html-file "${name}.html"

docker stop my-webtracer-app
docker rm my-webtracer-app
docker build -t my-webtracer-app .
docker run -d --name my-webtracer-app -p 8080:80 my-webtracer-app

C:\Users\Mabeshau\AppData\Local\Programs\Opera\opera.exe http://localhost:8080/inc5.html