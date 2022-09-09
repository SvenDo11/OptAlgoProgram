QT += widgets
requires(qtConfig(fontcombobox))

HEADERS	    =   mainwindow.h \
		diagramitem.h \
		diagramscene.h \
		arrow.h \
		diagramtextitem.h \
		instance_creator_dialog.h \
		local_search.h \
		rectangleinstance.h
SOURCES	    =   mainwindow.cpp \
		diagramitem.cpp \
		instance_creator_dialog.cpp \
		main.cpp \
		arrow.cpp \
		diagramtextitem.cpp \
		diagramscene.cpp \
		rectangleinstance.cpp
RESOURCES   =	diagramscene.qrc


# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/diagramscene
INSTALLS += target
