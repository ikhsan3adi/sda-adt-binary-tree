@echo off
gcc -o btree main.c btree/btree.c -I.
if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b %errorlevel%
)
btree
echo.
pause