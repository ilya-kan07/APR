# Используем официальный образ Ubuntu как базовый
FROM ubuntu:20.04

# Устанавливаем нужные пакеты: g++, cmake и любые другие зависимости
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    && rm -rf /var/lib/apt/lists/*

# Устанавливаем рабочую директорию внутри контейнера
WORKDIR /app

# Копируем файлы проекта в контейнер
COPY . .

# Создаем директорию для сборки
RUN mkdir -p build

# Переходим в директорию сборки и запускаем cmake и make
WORKDIR /app/build
RUN cmake ..
RUN make
