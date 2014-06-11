JavaScriptExecutable
====================

JavaScriptExecutable provides a environment for creating native GUI cross-platform JavaScript desktop application.

<img src="doc/images/jse.png?raw=true" alt="Screen Shot" width="522px" />

There is no stable version yet. Download latest development build (Windows and Mac) at

https://www.imzcy.com/jse/

How to build?
--------------------

**Mac OS X**

1. Install XCode and Qt 5.3.0
2. `.\configure`
3. (Only apply if Qt cannot be found under home folder when `make`) `export QT_DIR=/path/to/qt`
4. `make`
5. If build error occurs, check your Qt directory and modify `QT_DIR` accordingly. If error persists, create a issue.
 
**General Guide**

1. Build v8 JavaScript Engine (http://code.google.com/p/v8/)
2. Install Qt (http://qt-project.org/) (v5.3)
3. Moc all `JSEUI*.h` (except `JSEUIBase.h` and `JSEUITpl.h`) using *Meta-Object Compiler* included in Qt.
4. Compile and link.

How to run?
--------------------

**Windows** 

`JavaScriptExecutable.exe app.js` or `double-click JavaScriptExecutable.exe`

**Mac OS X**

`./JavaScriptExecutable.app/Contents/MacOS/JavaScriptExecutable app.js` or `double-click JavaScriptExecutable.app`

**Ubuntu**

`./JavaScriptExecutable app.js` or `double-click JavaScriptExecutable`
