SET(_PLATFORM_NAME_WIN Win)
SET(_PLATFORM_NAME_IOS Ios)
SET(_PLATFORM_NAME_OSX Osx)
SET(_PLATFORM_NAME_ANDROID Android)
SET(_PLATFORM_NAME_LINUX Linux)

IF (WIN32)
	SET(PLATFORM_NAME_WIN ${_PLATFORM_NAME_WIN})
	SET(PLATFORM_NAME ${_PLATFORM_NAME_WIN})
ELSEIF (IOS_PLATFORM)
	SET(PLATFORM_NAME_IOS ${_PLATFORM_NAME_IOS})
	SET(PLATFORM_NAME ${_PLATFORM_NAME_IOS})
ELSEIF (APPLE)
	SET(PLATFORM_NAME_OSX ${_PLATFORM_NAME_OSX})
	SET(PLATFORM_NAME ${_PLATFORM_NAME_OSX})
ELSEIF (ANDROID_NDK)
	SET(PLATFORM_NAME_ANDROID ${_PLATFORM_NAME_ANDROID})
	SET(PLATFORM_NAME ${_PLATFORM_NAME_ANDROID})
ELSE()
	SET(PLATFORM_NAME_LINUX ${_PLATFORM_NAME_LINUX})
	SET(PLATFORM_NAME ${_PLATFORM_NAME_LINUX})
ENDIF()