@echo off
echo Deleting executable and object file

%CD:~0,2%/Compilers/MinGW64_4.9.2/bin/rm.exe bin\Debug\Kroz.exe bin\Debug\main.o 

set start=%time% ::Record start time

if NOT exist bin\Debug\ (
    mkdir bin\Debug
)

echo Creating object file.
%CD:~0,2%/Compilers/MinGW64_4.9.2/bin/g++.exe -D__DEBUG__ -c main.cpp -o bin/Debug/main.o -I"include/" -Ofast -std=c++11 -w -pedantic -pg -g3

echo Creating executable
if exist bin\debug\main.o (
    %CD:~0,2%/Compilers/MingW64_4.9.2/bin/g++.exe -D__DEBUG__ bin/Debug/main.o -o bin/Debug/Kroz.exe -L"%CD:~0,2%/Compilers/mingw64/lib32" -L"%CD:~0,2%/Compilers/mingw64/x86_64-w64-mingw32/lib32" -static-libgcc -pg -g3
) 

::Record end time && calculate duration
set end=%time%
set options="tokens=1-4 delims=:.,"
for /f %options% %%a in ("%start%") do set start_h=%%a&set /a start_m=100%%b %% 100&set /a start_s=100%%c %% 100&set /a start_ms=100%%d %% 100
for /f %options% %%a in ("%end%") do set end_h=%%a&set /a end_m=100%%b %% 100&set /a end_s=100%%c %% 100&set /a end_ms=100%%d %% 100

set /a hours=%end_h%-%start_h%
set /a mins=%end_m%-%start_m%
set /a secs=%end_s%-%start_s%
set /a ms=%end_ms%-%start_ms%
if %ms% lss 0 set /a secs = %secs% - 1 & set /a ms = 100%ms%
if %secs% lss 0 set /a mins = %mins% - 1 & set /a secs = 60%secs%
if %mins% lss 0 set /a hours = %hours% - 1 & set /a mins = 60%mins%
if %hours% lss 0 set /a hours = 24%hours%
if 1%ms% lss 100 set ms=0%ms%

:: mission accomplished
set /a totalsecs = %hours%*3600 + %mins%*60 + %secs% 
::echo command took %hours%:%mins%:%secs%.%ms% (%totalsecs%.%ms%s total)

:: Get file size
set file="bin\Debug\Kroz.exe"
FOR /F "usebackq" %%A IN ('%file%') DO set size=%%~zA
set /a result=(size/1024)


setlocal EnableDelayedExpansion

set "var1=%result%"
set "var2="
set "sign="

if "%var1:~0,1%" equ "-" set "sign=-" & set "var1=%var1:~1%"

for /L %%i in (1,1,4) do if defined var1 (
   set "var2=,!var1:~-3!!var2!"
   set "var1=!var1:~0,-3!"
)
set "fileSize=%sign%%var2:~1%


::echo results
echo.
echo Compilation results...
echo --------
if exist bin/Debug/Kroz.exe (
    echo - Successful!
    echo - Output Filename: %cd%\bin\Debug\Kroz.exe
    echo - Output Size: %fileSize% KiB
) else (
    echo Failed!
)
echo - Compilation Time: %totalsecs%.%ms%s