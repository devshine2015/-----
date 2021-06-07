@echo off
call "%VS120COMNTOOLS%vsvars32.bat"
echo .
echo ===compile is started===
echo .
echo ---AccountServer compile is started---
echo 
cd AccountServer
call AccountServer.bat
cd..
echo .
echo ---GameServer compile is started---
echo .
cd GameServer
call GameServer.bat
cd..
echo .
echo ---GateServer compile is started---
echo .
cd GateServer
call GateServer.bat
cd..
echo .
echo ---GroupServer compile is started---
echo .
cd GroupServer
call GroupServer.bat
cd..
echo .
echo ===copy servers===
echo .
del /F /Q ..\..\server\AccountServer.exe
copy .\AccountServer\Bin\AccountServer.exe ..\..\server\AccountServer.exe
del /F /Q ..\..\server\GameServer.exe
copy .\GameServer\Bin\GameServer.exe ..\..\server\GameServer.exe
del /F /Q ..\..\server\GateServer.exe
copy .\GateServer\Bin\GateServer.exe ..\..\server\GateServer.exe
del /F /Q ..\..\server\GroupServer.exe
copy .\GroupServer\Bin\GroupServer.exe ..\..\server\GroupServer.exe