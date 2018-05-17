if(NOT DEFINED DIGIDOC_EXECUTABLE)
    set(DIGIDOC_EXECUTABLE qdigidocclient)
    set(DIGIDOC_ICON qdigidoc-client)
    set(DIGIDOC_NAME Digidoc3)
endif()

configure_file(nautilus-qdigidoc.py.cmake nautilus-qdigidoc.py)
configure_file(po/et.po.cmake po/et.po)
configure_file(po/nautilus-qdigidoc.pot.cmake po/nautilus-qdigidoc.pot)
configure_file(po/ru.po.cmake po/ru.po)

find_package(Gettext)

file(GLOB PO_FILES ${CMAKE_CURRENT_BINARY_DIR}/po/*.po)
gettext_create_translations(${CMAKE_CURRENT_BINARY_DIR}/po/nautilus-qdigidoc.pot ALL ${PO_FILES})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/nautilus-qdigidoc.py DESTINATION ${CMAKE_INSTALL_DATADIR}/nautilus-python/extensions/)
