if(NOT DEFINED DIGIDOC_EXECUTABLE)
    set(DIGIDOC_EXECUTABLE qdigidocclient)
    set(DIGIDOC_ICON qdigidoc-client)
endif()

configure_file(qdigidoc-signer.desktop.cmake qdigidoc-signer.desktop)

set(SERVICES_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/kde4/services" CACHE PATH "Install dir for KDE service (desktop, protocol, ...) files")

install(FILES ${CMAKE_CURRENT_BINARY_DATADIR}/qdigidoc-signer.desktop DESTINATION "${SERVICES_INSTALL_DIR}")
