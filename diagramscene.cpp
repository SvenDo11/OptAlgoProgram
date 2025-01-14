/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "diagramscene.h"
#include "arrow.h"

#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>
#include <QApplication>

//! [0]
DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = DiagramItem::Step;
    line = nullptr;
    textItem = nullptr;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;

    boxPen = QPen(Qt::black, 5);
    boxHighlightPen = QPen(highlightColor, 7);
    rectPen = QPen(Qt::black);
    rectHighlightPen = QPen(highlightColor, 3);
}
//! [0]

//! [1]
void DiagramScene::setLineColor(const QColor &color)
{
    myLineColor = color;
    if (isItemChange(Arrow::Type)) {
        Arrow *item = qgraphicsitem_cast<Arrow *>(selectedItems().first());
        item->setColor(myLineColor);
        update();
    }
}
//! [1]

//! [2]
void DiagramScene::setTextColor(const QColor &color)
{
    myTextColor = color;
    if (isItemChange(DiagramTextItem::Type)) {
        DiagramTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item->setDefaultTextColor(myTextColor);
    }
}
//! [2]

//! [3]
void DiagramScene::setItemColor(const QColor &color)
{
    myItemColor = color;
    if (isItemChange(DiagramItem::Type)) {
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(selectedItems().first());
        item->setBrush(myItemColor);
    }
}
//! [3]

//! [4]
void DiagramScene::setFont(const QFont &font)
{
    myFont = font;

    if (isItemChange(DiagramTextItem::Type)) {
        QGraphicsTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (item)
            item->setFont(myFont);
    }
}
//! [4]

void DiagramScene::setMode(Mode mode)
{
    myMode = mode;
}

void DiagramScene::setItemType(DiagramItem::DiagramType type)
{
    myItemType = type;
}

//! [5]
void DiagramScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}
//! [5]

//! [6]
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    DiagramItem *item;
    switch (myMode) {
        case InsertItem:
            item = new DiagramItem(myItemType, myItemMenu);
            item->setBrush(myItemColor);
            addItem(item);
            item->setPos(mouseEvent->scenePos());
            emit itemInserted(item);
            break;
//! [6] //! [7]
        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(myLineColor, 2));
            addItem(line);
            break;
//! [7] //! [8]
        case InsertText:
            textItem = new DiagramTextItem();
            textItem->setFont(myFont);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setZValue(1000.0);
            connect(textItem, &DiagramTextItem::lostFocus,
                    this, &DiagramScene::editorLostFocus);
            connect(textItem, &DiagramTextItem::selectedChange,
                    this, &DiagramScene::itemSelected);
            addItem(textItem);
            textItem->setDefaultTextColor(myTextColor);
            textItem->setPos(mouseEvent->scenePos());
            emit textInserted(textItem);
//! [8] //! [9]
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}
//! [9]

//! [10]
void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != nullptr) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}
//! [10]

//! [11]
void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != nullptr && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;
//! [11] //! [12]

        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == DiagramItem::Type &&
            endItems.first()->type() == DiagramItem::Type &&
            startItems.first() != endItems.first()) {
            DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
            DiagramItem *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());
            Arrow *arrow = new Arrow(startItem, endItem);
            arrow->setColor(myLineColor);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }
    }
//! [12] //! [13]
    line = nullptr;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
//! [13]

//! [14]
bool DiagramScene::isItemChange(int type) const
{
    const QList<QGraphicsItem *> items = selectedItems();
    const auto cb = [type](const QGraphicsItem *item) { return item->type() == type; };
    return std::find_if(items.begin(), items.end(), cb) != items.end();
}
//! [14]

void DiagramScene::cleanUp()
{
    clear();
    rectangles.clear();
    boxes.clear();
}

void DiagramScene::initRectangles(RectangleInstance *instance)
{
    cleanUp();

    LINES = floor(sqrt(instance->size()));
    int rows = instance->size();

    int boxLength = instance->getBoxlength();
    //SCALE = (boxLength >= 100) ? 1 : ((boxLength < 20) ? 20 : 10);

    this->setSceneRect(0, 0, ((rows + 1)*(boxLength + 1)*SCALE), ((LINES + 1)*(boxLength + 1)*SCALE));
    int currentX = 0;
    for(auto block: *(instance))
    {
        QGraphicsRectItem *rec = new QGraphicsRectItem(currentX, 0,
                                                       block->width * SCALE,
                                                       block->heigth * SCALE);

        currentX += block->width * SCALE;

        addItem(rec);
        rectangles.append(rec);
    }

    int currentY = SCALE * (boxLength + 1);
    currentX = SCALE;
    for(int i = 0; i < instance->length(); i++)
    {
        QGraphicsRectItem *box = new QGraphicsRectItem(currentX,
                                                       currentY,
                                                       boxLength * SCALE,
                                                       boxLength * SCALE);
        box->setPen(boxPen);
        addItem(box);
        boxes.append(box);

        currentY += SCALE * (boxLength + 1);
        if(currentY >= (LINES * boxLength + LINES + 1) * SCALE)
        {
            currentY = SCALE * (boxLength + 1);
            currentX += SCALE * (boxLength + 1);
        }
    }

    colorRectangles();

    emit ensureVisible(QRectF(0, 0, currentX, ((LINES * boxLength + LINES + 1) * SCALE)));
}

void DiagramScene::updateRectangles(RectSolution sol)
{
    int i = 0;
    // iterate over boxes
    for(auto box: boxes)
    {
        bool boxUpdated = false;
        int boxX = box->rect().x();
        int boxY = box->rect().y();
        // for each box, look for rectangles in sol
        for(int rectID: sol.boxes[i])
        {
            // update according rectangle
            auto rect = rectangles[rectID];
            QRectF oldRect = rect->rect();
            rectType solRect = sol.rectangles[rectID];
            QRectF newRect(boxX + solRect.x * SCALE, boxY + solRect.y * SCALE,
                          solRect.w * SCALE, solRect.h * SCALE);
            if(oldRect != newRect)
            {
                rect->setPen(rectHighlightPen);
                rect->setRect(newRect);
                rect->setBrush(highlightColors[rectID % highlightColors.length()]);
                boxUpdated = true;
            }
            else
            {
                rect->setPen(rectPen);
                rect->setBrush(colors[rectID % colors.length()]);
            }
        }
        box->setPen((boxUpdated) ? boxHighlightPen : boxPen );
        i++;
    }
    QApplication::processEvents();
}

void DiagramScene::colorRectangles()
{
    int i = 0;
    for(QGraphicsRectItem *rect: rectangles)
    {
        rect->setBrush(colors[i]);
        i++;
        if(i >= colors.length())
            i = 0;
    }
}

void DiagramScene::resetRectangles()
{
    int i = 0;
    int currentX = 0;
    for(QGraphicsRectItem *rec: rectangles)
    {
        QRectF baseRect(currentX, 0, rec->rect().width(), rec->rect().height());
        currentX += baseRect.width();
        rec->setRect(baseRect);
        rec->setPen(rectPen);
        rec->setBrush(colors[i % colors.length()]);
        i++;
    }
    for(auto box: boxes)
    {
        box->setPen(boxPen);
    }
    QApplication::processEvents();
}
