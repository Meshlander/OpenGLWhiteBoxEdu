@echo off

cl -EHa- -Oi -W4 -O2 WinMain.cpp /clr /link -opt:ref user32.lib gdi32.lib winmm.lib Ws2_32.lib Opengl32.lib