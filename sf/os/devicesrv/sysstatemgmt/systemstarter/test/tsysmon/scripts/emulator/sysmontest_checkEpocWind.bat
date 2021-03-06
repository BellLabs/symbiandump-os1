@rem
@rem Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
@rem All rights reserved.
@rem This component and the accompanying materials are made available
@rem under the terms of "Eclipse Public License v1.0"
@rem which accompanies this distribution, and is available
@rem at the URL "http://www.eclipse.org/legal/epl-v10.html".
@rem
@rem Initial Contributors:
@rem Nokia Corporation - initial contribution.
@rem
@rem Contributors:
@rem
@rem Description:
@rem
@echo off
setlocal

set RESTART_RESULT_FILE=\epoc32\winscw\c\Restart_ResultFile.txt
set REGISTER_RESULT_FILE=\epoc32\winscw\c\Register_ResultFile.txt


set TEST_CASE=%1
set EPOCWIND=%TEMP%\epocwind.out

goto :%TEST_CASE%

:checkLog
	:: checkLog SEARCH_STRING EXPECTED_NUMBER_OF_OCCURENCES
	set SEARCH_STRING=%1
	set TEMP_FILE=sysstart_temp.txt
	set EXPECTED_COUNT=%2
	set LOG_COUNT=0
	type %EPOCWIND% | %windir%\system32\find /c %SEARCH_STRING%>%TEMP_FILE%
	for /f "delims=\" %%i in ('type %TEMP_FILE%') do set LOG_COUNT=%%i
	del %TEMP_FILE%
	if "%EXPECTED_COUNT%" ==  "%LOG_COUNT%" goto :EOF
	if "%EXPECTED_COUNT%" NEQ "%LOG_COUNT%" set TEST_RESULT_FLAG=false
goto :EOF

:initialise
	if exist %RESTART_RESULT_FILE% del %RESTART_RESULT_FILE%
	if exist %REGISTER_RESULT_FILE%  del %REGISTER_RESULT_FILE%
	set TEST_RESULT_FLAG=true
goto :EOF

:checkRegister
	set TEST_RESULT_FLAG=true
	set REG_FILENAME=%1
	set REG_COUNT=%2
	set /a REG_COUNT=%REG_COUNT% - 1
	call :checkLog "SysMonServSess: Creating monitor for %REG_FILENAME%" 1
	if /i "%TEST_RESULT_FLAG%"=="true" call :checkLog "SysMonMonitor: %REG_FILENAME% restarted," %REG_COUNT%
	if /i "%TEST_RESULT_FLAG%"=="true" echo register=^1 > %REGISTER_RESULT_FILE%
	if /i "%TEST_RESULT_FLAG%"=="false" echo register=^0 > %REGISTER_RESULT_FILE%
goto :EOF

:noRegister
	echo register=^0 > %REGISTER_RESULT_FILE%
goto :EOF

:checkRestart
	set TEST_RESULT_FLAG=true
	call :checkLog "Panic RestartSys 1" 1
	if /i "%TEST_RESULT_FLAG%"=="true" echo count=^1 > %RESTART_RESULT_FILE%
	if /i "%TEST_RESULT_FLAG%"=="false" echo count=^0 > %RESTART_RESULT_FILE%
goto :EOF

:noRestart
	echo count=^0 > %RESTART_RESULT_FILE%
goto :EOF

:faileiofcount0
	call :initialise
	call :checkRegister tsysmon_app_donothing.exe 1
	call :noRestart
goto :EOF

:faileiofcount1fail 
	call :initialise
	call :checkRegister tsysmon_app_dontrendezvous.exe 1
	call :noRestart
goto :EOF

:faileroscount1fail
	call :initialise
	call :checkRegister tsysmon_app_dontrendezvous.exe 1
	call :checkRestart
goto :EOF

:failcount2failquick
	call :initialise
	call :checkRegister tsysmon_app_failcount2failquick_slave.exe 3
	call :noRestart
goto :EOF

:failcount2failwait
	call :initialise
	call :checkRegister tsysmon_app_failcount2failwait_slave.exe 3
	call :noRestart
goto :EOF

:restartreg
	call :initialise
	call :checkRegister tsysmon_app_deregister.exe 1
	call :checkRestart
goto :EOF

:restartfail
	call :initialise
	call :checkRegister tsysmon_app_donothing.exe 1
	call :checkRestart
goto :EOF

:startupregeiof
	call :initialise
	call :checkRegister Z:\sys\bin\tsysmon_app_startupregeiof.exe 1
	call :noRestart
goto :EOF

:startupregeioffailstart1
	call :initialise
	call :noRegister
	call :noRestart
goto :EOF

:startupregeioffailstart2
:startupregerosfailstart
	call :initialise
	call :noRegister
	call :checkRestart
goto :EOF

:startupregerosfaillater
	call :initialise
	call :checkRegister Z:\sys\bin\tsysmon_app_startupregerosfaillater.exe 1
	call :checkRestart
goto :EOF

endlocal
