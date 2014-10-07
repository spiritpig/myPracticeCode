@echo off
@echo delete all intermidiate file!
del /S *.htm
del /S *.ilk
del /S *.obj
del /S *.pch
del /S *.pdb
del /S *.idb
del /S *.pdb
del /S *.exe
@echo start counting!
set curDate=%date:~0,4%%date:~5,2%%date:~8,2%
perl ../../cloc-1.60.pl . > "codeCount/cc%curDate%.txt"
pause
@echo on
