Для создания библиотеки выполнить make

Для создания хука нужно добавить библиотеку в PRELOAD.
выполните команду export LD_PRELOAD=path/to/lib

При использовании функций библиотеки в проекте подключить библиотеку и собирать с флагом -Wl,-rpath,.
gcc -c example.c 
gcc example.o -L. -lsecureallocation -o example -I ./secure_allocation_lib.h -Wl,-rpath,.
