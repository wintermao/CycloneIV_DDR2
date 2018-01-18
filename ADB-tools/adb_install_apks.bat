@echo off 
title ADB Install Apks[By LongLuo]
goto BEGIN


:COMMENT
echo ##############################################
rem 	adb_install_apks.bat
rem			By Long.Luo @2013/03/20
rem		
rem 	Description:
rem 		Used to install all the apks in a PATH including 
rem 	the subdirs.
rem 
rem 	Version: 2.5
rem
echo ##############################################
pause


:BEGIN
echo.
echo ################   Begin...   ################ 


:HELP
rem 无文件拖至bat时 
if "%~1"=="" echo Please drag apks to this bat file！&goto END 
 
echo Infomation:
echo Support multi-files. 


:MAIN
setlocal enabledelayedexpansion 
if not "%~1"=="" ( 
  echo. 
  rem 文件后缀名判断 
  if /i "%~x1"==".apk" ( 
    echo Install "%~1"... 
	adb install -r "%~1"
  ) else ( 
    echo File Type error：Don't support%~x1！ 
  ) 
 
  shift /1 
  goto MAIN 
) 


:END
echo.
echo ################  All apks were installed!   ################
pause