cmake_minimum_required(VERSION 3.25)
cmake_policy(VERSION 3.25)

project(Alljoyn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(alljoyn-c-sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AboutData.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AboutDataListener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AboutIcon.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AboutIconObj.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AboutIconProxy.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AboutListener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AboutObj.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AboutObjectDescription.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AboutProxy.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ApplicationStateListener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AuthListener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AutoPinger.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BusAttachment.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BusAttachmentC.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BusAttachmentC.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BusListener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BusObjectC.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CertificateUtilities.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CertificateUtilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DeferredCallback.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DeferredCallback.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Init.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/InterfaceDescription.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KeyStoreListener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Message.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MessageReceiverC.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MsgArg.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MsgArgC.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MsgArgC.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Observer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PasswordManager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PermissionConfigurationListener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PermissionConfigurator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ProxyBusObject.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ProxyBusObjectListenerC.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SecurityApplicationProxy.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SessionListener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SessionOpts.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SessionPortListener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/version.cc
)

# also adds generated files to sources
add_library(alljoyn_c
    ${alljoyn-c-sources}
    )

add_dependencies(alljoyn_c status_header_cpp)

target_include_directories(alljoyn_c PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common/crypto"
    "${CMAKE_CURRENT_SOURCE_DIR}/../alljoyn_core/inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/../alljoyn_core/src"
    )

