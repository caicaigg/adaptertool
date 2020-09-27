@echo off
echo 清理文件
del /s *.user
del /s *.sdf
del /s *.suo
del /s *.exe
rd /s /q ipch
rd /s /q obj
rd /s /q bin
del /s *.VC.db
del /s *.VC.db-shm
del /s *.VC.db-wal
for /f "delims=" %%i in ('dir /ad /b /s "Debug"') do (
rd /s /q "%%i"
)
for /f "delims=" %%i in ('dir /ad /b /s "GeneratedFiles"') do (
rd /s /q "%%i"
)
for /f "delims=" %%i in ('dir /ad /b /s "Release"') do (
rd /s /q "%%i"
)
for /f "delims=" %%i in ('dir /ad /b /s "obj"') do (
rd /s /q "%%i"
)
for /f "delims=" %%i in ('dir /ad /b /s "Debug"') do (
rd /s /q "%%i"
)
for /f "delims=" %%i in ('dir /ad /b /s "ipch"') do (
rd /s /q "%%i"
)
for /f "delims=" %%i in ('dir /ad /b /s "obj"') do (
rd /s /q "%%i"
)

