
![text](https://banners.beyondco.de/WebRays.png?theme=dark&packageManager=&packageName=&pattern=randomShapes&style=style_1&description=A+sleek+and+modern+raytracer+for+the+web.&md=1&showWatermark=0&fontSize=100px&images=code)

## Raytracing în Browser - O Sinergie între C++ și JavaScript prin Emscripten


Acest proiect implementează un raytracer simplu utilizând Emscripten pentru a transpila codul C++ în WebAssembly, permițând astfel rularea sa în browser. Raytracer-ul generează imagini realistice prin simularea traiectoriei razelor de lumină și calcularea interacțiunilor acestora cu obiectele din scenă. Utilizarea Emscripten facilitează accesul la performanța nativă în contextul web, permițând o experiență vizuală fluidă și detaliată direct în browser. Acest readme oferă instrucțiuni pentru configurare, compilare și rulare, alături de exemple de utilizare și capturi de ecran ale rezultatelor obținute.


## Funcționalități

- Interoperabilitate intre codul C++ si JavaScript
- Abilitatea de a modifica conținutul scenei în timpul execuției
- Multithreading
- Redarea in mediul web cu Nginx si Docker


## Prerechizite

 - [emsdk](https://github.com/emscripten-core/emsdk)
 - [Docker](https://www.docker.com)
 - [Python](https://www.python.org)


## Instalare
### 1.Instalare Docker
1. **Descarcă Docker Desktop pentru Windows:**
    - Accesează [pagina oficială de descărcare Docker](https://www.docker.com/products/docker-desktop) și descarcă Docker Desktop pentru Windows.

2. **Instalează Docker Desktop:**
    - Rulează instalatorul descărcat și urmează instrucțiunile de pe ecran.
    - După instalare, asigură-te că `Docker Desktop` este pornit.

3. **Configurare Docker:**
    - Deschide Docker Desktop și verifică dacă Docker Engine este activ.

4. **Verifică instalarea:**
    - Deschide Command Prompt și rulează următoarea comandă:
      ```sh
      docker --version
      ```
### 1. Instalare pip
1. In cazul in care versiunea python folosita este mai mica decat versiuna 3.14, pip va trebui instalat manual.
Acest lucru poate fi facut cu urmatorele comenzi bash.
```sh
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python get-pip.py

```
### 2.Clonarea proiectului
1. **Clonați repository-ul proiectului raytracer:**
    ```sh
    git clone https://github.com/Cameliuu/WebRays
    ```
### 3.Instalarea modulelor pip
1. **Asigurați-vă că sunteți în folder-ul `WebRays`.**
```sh
cd WebRays
```
2. **Rulați script-ul pentru instalarea dependințelor.**
```sh
python dependencies.sh
```
### 4. Instalare Emscripten

1. **Clonați repository-ul oficial Emscripten:**
    ```sh
    git clone https://github.com/emscripten-core/emsdk.git
    ```
2. **Navigați în directorul `emsdk`:**
    ```sh
    cd emsdk
    ```
3. **Actualizați repository-ul:**
    ```sh
    git pull
    ```
4. **Instalați Emscripten și instrumentele necesare:**
    ```sh
    ./emsdk install latest
    ```
5. **Activați Emscripten în sesiunea curentă:**
    ```sh
    ./emsdk activate latest
    source ./emsdk_env.sh
    ```
### 5. Compilarea proiectului
1. **Activați `emsdk` in directorul `WebRays`**
```sh
emsdk activate latest
```
2. **Compilați proiectul folosind comanda:**
```sh
./compile.sh {NUME}
```
Unde ```{NUME}``` este numele fisierului HTML ce va avea sa fie produs in urma compilarii.
## Utilizare

### 1. Navigati in browser la serverul Nginx la urmatorul link
```sh
http://localhost:8080/{NUME}.html
```

### 2. Modificare Configuratie

