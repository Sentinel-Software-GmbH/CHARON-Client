@echo off
WHERE doxygen
IF %ERRORLEVEL% NEQ 0 (
	ECHO doxygen wasn't found
) else (
	doxygen "documentation/Doxyfile" 2> documentation_error.log
	cd build\documentation\html
	copy Charon_UDS_Client.chm ..\
)