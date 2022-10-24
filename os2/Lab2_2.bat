@echo Генеруємо файли

cd d:\university\

echo FILE1 > f1.txt
echo FILE2 > f2.txt
echo FILE3 > f3.txt
echo FILE4 > f4.pas
echo FILE5 > f5.pas
echo FILE6 > f6.pas
echo FILE7 > f7.cpp
echo FILE8 > f8.cpp
echo FILE9 > f9.cpp
echo FILE10 > f10.bat
echo FILE11 > f11.bat
echo FILE12 > f12.bat
echo FILE13 > f13.exe
echo FILE14 > f14.exe
echo FILE15 > f15.exe
echo FILE16 > f16.gif
echo FILE17 > f17.gif
echo FILE18 > f18.gif
echo FILE19 > f19.com
echo FILE20 > f20.com
echo FILE21 > f21.com
echo FILE22 > f22.tmp
echo FILE23 > f23.tmp
echo FILE24 > f24.tmp
copy *.txt d:\university\ud_VDS\ud_VDS_5\ud_VDS_52\ud_VDS_552\
copy *.gif d:\university\ud_VDS\ud_VDS_5\ud_VDS_52\ud_VDS_553\
copy *.com d:\university\ud_VDS\ud_VDS_5\ud_VDS_52\ud_VDS_551\
FOR %%c IN (*.cpp *.pas) DO copy %%c d:\university\ud_VDS\ud_VDS_6\ud_VDS_62\*.*
move *.cpp d:\university\ud_VDS\ud_VDS_4\ud_VDS_42\
move *.exe d:\university\ud_VDS\ud_VDS_4\ud_VDS_43\
del /f /s /q d:\university\*.tmp
