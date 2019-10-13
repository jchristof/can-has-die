d:\gbdk-2.95-3-win32\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c
d:\gbdk-2.95-3-win32\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o main.gb main.o

QPROCESS "bgb.exe">NUL
IF %ERRORLEVEL% EQU 0 goto end
D:\bgb\bgb -rom main.gb -watch
:end
