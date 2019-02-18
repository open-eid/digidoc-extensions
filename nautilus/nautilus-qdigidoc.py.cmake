#
# QDigiDoc Nautilus Extension
#
# Copyright (C) 2010  Erkko Kebbinau
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc, 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#
import os
import urllib
import gettext
import locale

from gi.repository import Nautilus, GObject, Gio

APP = 'nautilus-qdigidoc'

locale.setlocale(locale.LC_ALL, '')
gettext.bindtextdomain(APP)
gettext.textdomain(APP)

class OpenDigidocExtension(GObject.GObject, Nautilus.MenuProvider):
    def __init__(self):
        pass

    def menu_activate_cb(self, menu, paths):
        args = "-sign "
        for path in paths:
            args += "\"%s\" " % path
        cmd = ("${DIGIDOC_EXECUTABLE} " + args + "&")
        os.system(cmd)

    def valid_file(self, file):
        return file.get_file_type() == Gio.FileType.REGULAR and file.get_uri_scheme() == 'file'

    def get_file_items(self, window, files):
        paths = []
        for file in files:
            if self.valid_file(file):
                path = urllib.unquote(file.get_uri()[7:])
                paths.append(path)

        if len(paths) < 1:
            return

        item = Nautilus.MenuItem(
            name="OpenDigidocExtension::DigidocSigner",
            label=gettext.gettext('Sign digitally'),
            tip=gettext.ngettext('Sign selected file with ${DIGIDOC_NAME} Client',
                                 'Sign selected files with ${DIGIDOC_NAME} Client',
                                 len(paths)),
            icon='${DIGIDOC_ICON}'
        )
        item.connect('activate', self.menu_activate_cb, paths)
        return item,

class OpenCryptoExtension(GObject.GObject, Nautilus.MenuProvider):
    def __init__(self):
        pass

    def menu_activate_cb(self, menu, paths):
        args = "-crypto "
        for path in paths:
            args += "\"%s\" " % path
        cmd = ("${DIGIDOC_EXECUTABLE} " + args + "&")
        os.system(cmd)

    def valid_file(self, file):
        return file.get_file_type() == Gio.FileType.REGULAR and file.get_uri_scheme() == 'file'

    def get_file_items(self, window, files):
        paths = []
        for file in files:
            if self.valid_file(file):
                path = urllib.unquote(file.get_uri()[7:])
                paths.append(path)

        if len(paths) < 1:
            return

        item = Nautilus.MenuItem(
            name="OpenCryptoExtension::DigidocEncrypter",
            label=gettext.gettext('Encrypt files'),
            tip=gettext.ngettext('Encrypt selected file with ${DIGIDOC_NAME} Client',
                                 'Encrypt selected files with ${DIGIDOC_NAME} Client',
                                 len(paths)),
            icon='${DIGIDOC_ICON}'
        )
        item.connect('activate', self.menu_activate_cb, paths)
        return item,
