It's just simple try to create OS/2 console git client from scratch.
I use VisualAge C++ 3.0 compiler (I hope, God bless me).
Today I try make future structure of the project. 
Use nmake/nmake clean to work with files. Command os2git init create .git folder with file HEAD in it.
Adde os2git commands hash-object, add and status.
Add commands diff, checkout and commit.
Add log command.

Это попытка с нуля написать консольный гит-клиент для операционнйо системы OS/2 WARP.
Я работаю в среде VisualAge C++ 3.0. У меня есть машина с OS/2 WARP 4.5 server, првоеряю код на ней, пишу и заливаю с Windows машины.
Сегондя попробовал обрисовать будущую архитектуру - главный файл main.cpp, файл команды init.cpp, файл сборки (под OS/2 сборка nmake/nmake clean).
по команде os2git init создается папка .git, где есть файл HEAD с записью. Добавлены команды hash-object, add и status.
Добавлены команды diff, checkout и commit. По идее основная локальная часть (для рабоыт на диске, но не в сети) уже готова на большу часть.
Добавлена команда log.
