@echo off
@echo delete all intermidiate file!
./clearAll.bat
@echo start counting!
set curDate=%date:~0,4%%date:~5,2%%date:~8,2%
perl ../../cloc-1.60.pl . > "codeCount/cc%curDate%.txt"
pause
@echo on
