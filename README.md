# tinyraycaster in plain C

This raycaster implementation is based on Dmitry V. Sokolov's (aka “ssloy") tutorial “Project based learning: build your own 3D shooter in a weekend"  (original [repository](https://github.com/ssloy/tinyraycaster)).

Differences from the original:

* The source code is rewritten in plain C (C11 standart).

* For the convenience of processing and displaying the text of SDL2 errors, functional macros have been added with the ability to set a flag to terminate the application. For more information, see [lecture](https://rutube.ru/video/437ec1cc186ac3222b32dd4730a9ec61/?t=395&r=plwd) “The practice of the C language (MIPT, 2023-2024). SDL addition and visualization” by Konstantin Vladimirov.

* Other differences related to the lack of separate C\+\+ features in C.
