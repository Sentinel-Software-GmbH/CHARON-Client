@echo off
WHERE doxygen
IF %ERRORLEVEL% NEQ 0 (
	ECHO doxygen wasn't found
) else (
	IF exist "build\" (
	doxygen "documentation/Doxyfile" 2> documentation_error.log
	cd build\documentation\html
	copy Charon_UDS_Client.chm ..\
	cd..
	cd..
	cd..
	) else ( 
	mkdir build
	doxygen "documentation/Doxyfile" 2> documentation_error.log
	cd build\documentation\html
	copy Charon_UDS_Client.chm ..\
	cd.. 
	cd.. 
	cd..
	)
)