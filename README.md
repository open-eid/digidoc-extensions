# digidocshellextension

 * License: LGPL 2.1
 * &copy; Estonian Information System Authority
 * [Architecture of ID-software](http://open-eid.github.io)

Shell extensions for signing and encrypting with DigiDoc client.</br>
Extracted from [DigiDoc3 Client](https://github.com/open-eid/qdigidoc) - includes shell extensions for Windows, Linux and Mac (QuickLook plugin). Windows shell extension is compiled as a separate project, shell extensions for other platforms are included as DigiDoc3 or DigiDoc4 submodules and included in client build.


## Building on Windows

1. Install dependencies from

 * [Visual Studio Community 2015](https://www.visualstudio.com/downloads/)
 * [http://www.cmake.org](http://www.cmake.org)
 * [Wix toolset](http://wixtoolset.org/releases/)

2. Fetch the source

        git clone --recursive https://github.com/open-eid/digidocshellextension
        cd digidocshellextension

3. Configure

        mkdir build
        cd build
        cmake -G"NMake Makefiles" ..

4. Build

        nmake