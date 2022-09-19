QT += widgets
requires(qtConfig(fontcombobox))

HEADERS	    =   mainwindow.h \
		algorithmrunner.h \
		diagramitem.h \
		diagramscene.h \
		arrow.h \
		diagramtextitem.h \
		geometrieneighbor.h \
		instance_creator_dialog.h \
		local_search.h \
		localsearch.h \
		lsgeometrie.h \
		lstest.h \
		neighborhood.h \
		rectangleinstance.h \
		rectsolution.h
SOURCES	    =   mainwindow.cpp \
		algorithmrunner.cpp \
		diagramitem.cpp \
		geometrieneighbor.cpp \
		instance_creator_dialog.cpp \
		lsgeometrie.cpp \
		lstest.cpp \
		main.cpp \
		arrow.cpp \
		diagramtextitem.cpp \
		diagramscene.cpp \
		neighborhood.cpp \
		rectangleinstance.cpp \
		rectsolution.cpp
RESOURCES   =	diagramscene.qrc


# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/diagramscene
INSTALLS += target
