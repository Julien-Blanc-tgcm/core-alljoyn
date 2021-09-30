cmake_minimum_required(VERSION 3.9)

project(Alljoyn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file("src/version.cc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.cc")

set_source_files_properties(${Status-cc-file} PROPERTIES GENERATED ON)
set(alljoyn-core-sources
    "src/AboutData.cc"
    "src/AboutIcon.cc"
    "src/AboutIconObj.cc"
    "src/AboutIconProxy.cc"
    "src/AboutKeys.cc"
    "src/AboutObj.cc"
    "src/AboutObjectDescription.cc"
    "src/AboutProxy.cc"
    "src/AllJoynCrypto.cc"
    "src/AllJoynPeerObj.cc"
    "src/AllJoynStd.cc"
    "src/AuthMechLogon.cc"
    "src/AuthMechSRP.cc"
    "src/AutoPinger.cc"
    "src/AutoPingerInternal.cc"
    "src/BusAttachment.cc"
    "src/BusEndpoint.cc"
    "src/BusObject.cc"
    "src/BusUtil.cc"
    "src/ClientRouter.cc"
    "src/ClientTransport.cc"
    "src/ConversationHash.cc"
    "src/CredentialAccessor.cc"
    "src/DBusStd.cc"
    "src/DefaultECDHEAuthListener.cc"
    "src/EndpointAuth.cc"
    "src/InterfaceDescription.cc"
    "src/KeyExchanger.cc"
    "src/KeyInfoHelper.cc"
    "src/KeyStore.cc"
    "src/LocalTransport.cc"
    "src/Message.cc"
    "src/Message_Gen.cc"
    "src/Message_Parse.cc"
    "src/MethodTable.cc"
    "src/MsgArg.cc"
    "src/NullTransport.cc"
    "src/Observer.cc"
    "src/ObserverManager.cc"
    "src/PasswordManager.cc"
    "src/PeerState.cc"
    "src/PermissionConfigurator.cc"
    "src/PermissionManager.cc"
    "src/PermissionMgmtObj.cc"
    "src/PermissionPolicy.cc"
    "src/PermissionPolicyUtil.cc"
    "src/ProtectedAuthListener.cc"
    "src/ProxyBusObject.cc"
    "src/RemoteEndpoint.cc"
    "src/Rule.cc"
    "src/SASLEngine.cc"
    "src/SecurityApplicationObj.cc"
    "src/SecurityApplicationProxy.cc"
    "src/SessionOpts.cc"
    "src/SignalTable.cc"
    "src/SignatureUtils.cc"
    "src/SimpleBusListener.cc"
    "src/StaticGlobals.cc"
    "src/Translator.cc"
    "src/Transport.cc"
    "src/TransportList.cc"
    "src/XmlHelper.cc"
    "src/XmlManifestConverter.cc"
    "src/XmlManifestTemplateConverter.cc"
    "src/XmlManifestTemplateValidator.cc"
    "src/XmlManifestValidator.cc"
    "src/XmlPoliciesConverter.cc"
    "src/XmlPoliciesValidator.cc"
    "src/XmlRulesConverter.cc"
    "src/XmlRulesValidator.cc"
    "src/XmlValidator.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/version.cc"
    "${Status-cc-file}"
)

list(APPEND alljoyn-core-sources
    "src/posix/ClientTransport.cc"
    "src/posix/KeyStoreListenerFactory.cc"
    "src/posix/NamedPipeClientTransport.cc")

set(alljoyn-router-sources)

set(alljoyn-router-common-sources
    "router/ArdpProtocol.cc"
    "router/AllJoynObj.cc"
    "router/AllJoynDebugObj.cc"
    "router/Bus.cc"
    "router/BusController.cc"
    "router/ConfigDB.cc"
    "router/DaemonRouter.cc"
    "router/DBusObj.cc"
    "router/NameTable.cc"
    "router/RouterGlobals.cc"
    "router/RuleTable.cc"
    "router/SessionlessObj.cc"
    "router/TCPTransport.cc"
    "router/UDPTransport.cc"
    "router/VirtualEndpoint.cc"
    "router/ns/IpNameService.cc"
    "router/ns/IpNameServiceImpl.cc"
    "router/ns/IpNsProtocol.cc"
)

list(APPEND alljoyn-router-common-sources
    "router/posix/PermissionMgrPosix.cc"
    "router/posix/Socket.cc"
    )

if(${EMBED_ALLJOYN_ROUTER})
    list(APPEND alljoyn-router-sources
        "router/bundled/BundledRouter.cc"
        "router/bundled/BundledRouter.h"
        "router/bundled/BundledRouterInit.cc"
        ${alljoyn-router-common-sources}
        )
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common/crypto"
    "${CMAKE_CURRENT_BINARY_DIR}/inc"
    "${CMAKE_CURRENT_BINARY_DIR}/inc/alljoyn"
    )

# also adds generated files to sources
add_library(alljoyn
    ${alljoyn-core-sources}
    ${alljoyn-common-sources}
    ${alljoyn-router-sources}
)

add_dependencies(alljoyn status_header_cpp)

if(${EMBED_ALLJOYN_ROUTER})
    target_compile_definitions(alljoyn PRIVATE ROUTER)
    target_include_directories(alljoyn PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/router"
        "${CMAKE_CURRENT_SOURCE_DIR}/router/posix"
        )
endif()

