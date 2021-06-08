@echo off
@rem change version

@rem compile
cd source\server
call compile-all.bat
cd ..\..
cd source\client2.4\client\client
call compile.bat
cd ..\..\..\..
