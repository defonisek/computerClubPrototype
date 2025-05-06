# computerClubPrototype
## English 
Russian version can be found [here](#russian).

This is a C++ prototype of a monitoring system for a non-existent computer cafe/club.

Can be built using CMake. 
VSCode automatically detects CMakeLists.txt and configures all necessary tools for this project. If you don't have VSCode or any similar IDE, it can be built in the command line as well.

Some functionality can be showcased with the provided files in testFiles directory. Each file has its corresponding output for comparison reasons. 

### How to build this in the command line?

#### Windows
```powershell
# Clone repository
git clone https://github.com/defonisek/computerClubPrototype.git
cd computerClubPrototype

# Configure build files (using mingw)
cmake -B build -G "MinGW Makefiles"

# Note: Absolute path to cmake.exe can be used as well

# Build project
cmake --build build --config Release

# Run executable
.\build\computerClubPrototype.exe file.txt

# Note: file.txt has to be in the same directory!
```
#### Unix systems
```sh
# Clone repository
git clone https://github.com/defonisek/computerClubPrototype.git
cd computerClubPrototype

# Configure build files
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build project
cmake --build build

# And run it
./build/computerClubPrototype file.txt

# Note: file.txt has to be in the same directory!

```

## Russian

Английская версия достуна [здесь](#english).

Это прототип системы мониторинга для несуществующего компьютерного клуба на C++.

Собирается с помощью CMake.
VSCode автоматически определяет CMakeLists.txt и настраивает все необходимые инструменты для проекта. Если вы по тем или иным причинам не используете VSCode или подобную IDE, сборку можно выполнить через командную строку.

Часть функционала может быть продемонстрирована с файлами из директории testFiles. У каждого файла есть соответствующий файл с выводом. С файлами вывода можно сравнивать вывод самой программы.

### Как собрать через командную строку?

#### Windows
```powershell
# Клонировать репозиторий
git clone https://github.com/defonisek/computerClubPrototype.git
cd computerClubPrototype

# Сгенерировать файлы сборки (используя mingw)
cmake -B build -G "MinGW Makefiles"

# Примечание: можно использовать абсолютный путь к cmake.exe

# Собрать проект
cmake --build build --config Release

# Запустить
.\build\computerClubPrototype.exe file.txt

# Примечание: file.txt должен находиться в той же директории!
```

#### Unix systems

```sh
# Клонировать репозиторий
git clone https://github.com/defonisek/computerClubPrototype.git
cd computerClubPrototype

# Сгенерировать файлы сборки
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Собрать проект
cmake --build build

# Запустить
./build/computerClubPrototype file.txt

# Примечание: file.txt должен находиться в той же директории!

```