
set(SERVICES_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/kservices5" CACHE PATH "Install dir for KDE service (desktop, protocol, ...) files")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qdigidoc-signer.desktop DESTINATION "${SERVICES_INSTALL_DIR}")
