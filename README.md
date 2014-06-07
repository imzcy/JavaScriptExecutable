JavaScriptExecutable
====================

JavaScriptExecutable provides a environment for creating native GUI cross-platform JavaScript desktop application.

<img src="doc/images/jse.png?raw=true" alt="Screen Shot" width="522px" />

There is no stable version yet. Download latest development build (Windows and Mac) at

https://www.imzcy.com/jse/

How to build?
--------------------

1. Build v8 JavaScript Engine (http://code.google.com/p/v8/) (v3.24.35.22)
2. Build Qt (http://qt-project.org/) (v5.3)
3. Moc all `JSEUI*.h` (except `JSEUIBase.h` and `JSEUITpl.h`) using *Meta-Object Compiler* included in Qt.
4. Compile and link.


Mac

1. `cd` to root directory.
2. `mkdir build; cd build/`.
3. `make all -f ../Makefile.mac`
4. If error occurs, check your Qt and v8 installation directory and modify Makefile.mac accordingly.
 
How to run?
--------------------

**Windows** `JavaScriptExecutable.exe [app.js]`

*Other platforms* `Not tested but should be the same.`
