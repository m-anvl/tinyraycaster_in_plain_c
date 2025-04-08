# tinyraycaster на C

Эта реализация рейкастера создана на основе туториала Дмитрия Соколова (aka “ssloy”) “Project based learning: build your own 3D shooter in a weekend” (оригинальный [репозиторий](https://github.com/ssloy/tinyraycaster), [статья](https://habr.com/ru/articles/439698/) на Хабре).

Отличия от оригинала:

* Использована библиотека SDL3 вместо SDL2

* Исходный код переписан на обычном C (стандарт C11).

* Для удобства обработки и вывода текста ошибок SDL3 добавлены функциональные макросы с возможностью установки флага для прекращения работы приложения. Подробнее в [лекции](https://rutube.ru/video/437ec1cc186ac3222b32dd4730a9ec61/?t=395&r=plwd) Константина Владимирова “Практика языка C (МФТИ, 2023-2024). Дополнение SDL и визуализация”.

* Иные отличия, связанные с отсутствием в C отдельных возможностей C\+\+.

![Screenshot](screenshot.png)

## Сборка/генерация проекта

NOTE: перед сборкой необходимо установить библиотеку SDL3.

```sh
git clone https://github.com/AnatoliiM18/tinyraycaster_in_plain_c.git
cd tinyraycaster_in_plain_c
mkdir build
cd build
cmake ..
```

Открыть проект в IDE или использовать иные инструменты в завимости от среды.