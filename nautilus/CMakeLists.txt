cmake_minimum_required(VERSION 2.6)
project(NautilusQDigiDoc)

configure_file(nautilus-qdigidoc.py.in nautilus-qdigidoc.py)
configure_file(po/et.po.in po/et.po)
configure_file(po/nautilus-qdigidoc.pot.in po/nautilus-qdigidoc.pot)
configure_file(po/ru.po.in po/ru.po)

find_package(Gettext)

file(GLOB PO_FILES po/*.po)
gettext_create_translations(po/nautilus-qdigidoc.pot ALL ${PO_FILES})

install(FILES nautilus-qdigidoc.py DESTINATION ${CMAKE_INSTALL_DATADIR}/nautilus-python/extensions/)
