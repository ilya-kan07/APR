# Используем официальный образ с C++ и CMake
FROM ubuntu:20.04

# Устанавливаем переменную окружения для подавления интерактивных запросов
ENV DEBIAN_FRONTEND=noninteractive

# Устанавливаем временную зону
ENV TZ=America/New_York
RUN apt-get update && \
    apt-get install -y tzdata && \
    ln -fs /usr/share/zoneinfo/$TZ /etc/localtime && \
    dpkg-reconfigure --frontend noninteractive tzdata && \
    rm -rf /var/lib/apt/lists/*

# Устанавливаем оставшиеся пакеты
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Создаем директорию для нашего приложения
WORKDIR /app

# Копируем файлы проекта в контейнер
COPY . .

# Создаем директорию для сборки и переходим в нее
RUN mkdir build && cd build && \
    cmake .. && \
    make

# Команда по умолчанию для запуска приложения
CMD ["./build/AutomaticPowerReduction"]
