@echo off
@echo delete all .htm file
del /S *.htm
@echo start counting!
set curDate=%date:~0,4%%date:~5,2%%date:~8,2%
perl ../../cloc-1.60.pl . > "codeCount/cc%curDate%.txt"
pause
@echo on
