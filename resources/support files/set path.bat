
@echo off
set /p givenPath="Enter cloned repo path (with bin folder at the end): "
for /f "skip=2 tokens=1,2*" %%a in ('reg query HKCU\Environment /v Path') do set "newPath=%%c;%givenPath%"
setx Path "%newPath%"
