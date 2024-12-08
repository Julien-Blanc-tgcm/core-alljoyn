cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

project(Alljoyn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_custom_command(OUTPUT
    "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn/Status.h"
    "${CMAKE_CURRENT_BINARY_DIR}/alljoyn_core/Status.cc"
    COMMAND
        mkdir -p "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn/" &&
        mkdir -p "${CMAKE_CURRENT_SOURCE_DIR}/alljoyn_core/src/" &&
        ${CMAKE_CURRENT_SOURCE_DIR}/build_core/tools/bin/make_status.py --header
        "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn/Status.h" --code
        "${CMAKE_CURRENT_BINARY_DIR}/alljoyn_core/Status.cc" --base
        "${CMAKE_CURRENT_SOURCE_DIR}/alljoyn_core"
        "${CMAKE_CURRENT_SOURCE_DIR}/alljoyn_core/src/Status.xml"
)

add_custom_command(OUTPUT
    "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn_c/Status.h"
    COMMAND mkdir -p "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn_c" &&
        cp "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn/Status.h"
        "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn_c/Status.h"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn/Status.h"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn/Status.h"
    DESTINATION dist/c/inc/alljoyn_c/Status.h
    )

add_custom_target(status_header_cpp DEPENDS
    "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn/Status.h"
    "${CMAKE_CURRENT_BINARY_DIR}/alljoyn_core/Status.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn_c/Status.h"
    )

set(Status-cc-file
    "${CMAKE_CURRENT_BINARY_DIR}/alljoyn_core/Status.cc"
    )

set(alljoyn-common-sources
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/Alarm.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/ASN1.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/BigNum.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/CertificateECC.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/CertificateHelper.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/Config.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/Crypto.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/CryptoECCFieldp256.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/CryptoECCMath.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/CryptoECCOldEncoding.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/CryptoECCp256.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/CryptoSRP.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/Debug.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/DebugControl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/GUID.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/IODispatch.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/IPAddress.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/KeyBlob.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/KeyInfoECC.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/LockOrderChecker.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/Logger.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/Mutex.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/MutexInternal.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/Pipe.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/SLAPPacket.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/SLAPStream.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/SocketStream.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/StaticGlobals.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/Stream.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/StreamPump.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/String.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/StringSource.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/StringUtil.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/ThreadPool.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/Timer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/Util.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/src/XmlElement.cc
    )

## os dependant files
list(APPEND alljoyn-common-sources
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/atomic.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/Condition.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/defs.mk"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/Environ.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/Event.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/FileStream.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/IfConfigDarwin.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/IfConfigLinux.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/MutexInternal.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/OSLogger.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/osUtil.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/RWLock.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/Socket.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/Thread.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/time.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/UARTStreamDarwin.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/os/posix/UARTStreamLinux.cc"
)

## crypto files
list(APPEND alljoyn-common-sources
    "${CMAKE_CURRENT_SOURCE_DIR}/common/crypto/ECC/generic/CryptoECC.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/crypto/openssl/CryptoAES.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/crypto/openssl/CryptoHash.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/crypto/openssl/CryptoRand.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/crypto/openssl/OpenSsl.cc"
)

include_directories("common/inc"
    "common/crypto"
    "${CMAKE_CURRENT_BINARY_DIR}/inc"
    "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn"
    )

add_definitions("-DQCC_OS_GROUP_POSIX" -DQCC_OS_LINUX -DQCC_LINUX_OPENSSL_GT_1_1_X)
#add_compile_definitions("QCC_OS_GROUP_POSIX" QCC_OS_LINUX QCC_LINUX_OPENSSL_GT_1_1_X)

set_source_files_properties(${Status-cc-file} PROPERTIES GENERATED ON)
message("Status file source is ${Status-cc-file}")

add_subdirectory(alljoyn_c)
add_subdirectory(alljoyn_core)

