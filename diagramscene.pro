QT += widgets
requires(qtConfig(fontcombobox))

HEADERS	    =   mainwindow.h \
		algorithmrunner.h \
		algotoolbox.h \
		diagramitem.h \
		diagramscene.h \
		arrow.h \
		diagramtextitem.h \
		greedy.h \
		greedylargestfirst.h \
		instance_creator_dialog.h \
		local_search.h \
		localsearch.h \
		lsgeometrie.h \
		lsoverlap.h \
		lspermutation.h \
		lstest.h \
		rectangleinstance.h \
		rectsolution.h
SOURCES	    =   mainwindow.cpp \
		algorithmrunner.cpp \
		algotoolbox.cpp \
		diagramitem.cpp \
		greedylargestfirst.cpp \
		instance_creator_dialog.cpp \
		lsgeometrie.cpp \
		lsoverlap.cpp \
		lspermutation.cpp \
		lstest.cpp \
		main.cpp \
		arrow.cpp \
		diagramtextitem.cpp \
		diagramscene.cpp \
		rectangleinstance.cpp \
		rectsolution.cpp
RESOURCES   =	diagramscene.qrc


# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/diagramscene
INSTALLS += target
