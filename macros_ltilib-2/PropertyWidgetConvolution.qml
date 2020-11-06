/******************************************************************************************
**   Impresario - Image Processing Engineering System applying Reusable Interactive Objects
**   Copyright (C) 2015-2020  Lars Libuda
**
**   This file is part of Impresario.
**
**   Impresario is free software: you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation, either version 3 of the License, or
**   (at your option) any later version.
**
**   Impresario is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with Impresario in subdirectory "licenses", file "LICENSE_Impresario.GPLv3".
**   If not, see <http://www.gnu.org/licenses/>.
******************************************************************************************/
import QtQml 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0

Item {
    // "macro" is passed as QML Context by Impresario

    width: 300
    height: 300

    onWidthChanged: propertyView.forceLayout()
    onHeightChanged: propertyView.forceLayout()

    SystemPalette {
        id: palette
        colorGroup: SystemPalette.Active
    }

    TableModel {
        id: itemModel

        property variant props: (macro === null) ? null : macro.parameters()

        TableModelColumn {
            display: "name"
        }
        TableModelColumn {
            display: "value"
            edit: "component"              // misuse of edit role to pass editor component to model
            accessibleText: "properties"   // misuse of accessibleText role to pass properties for editor component to model
            accessibleDescription: "name"  // misuse of accessibleDescription role to have the name of the property in model
        }

        Component.onCompleted: function() {
            appendRow({"name": props[0].name, "value": props[0].value, "component": props[0].component, "properties": props[0].properties, "description": props[0].description, "tagIndex": 0 });
            adaptList(props[0].value)
        }

        onDataChanged: function(modelIndex) {
            var rowIndex = getRow(modelIndex.row).tagIndex
            if (props[rowIndex].value !== data(modelIndex,"display")) {
                //console.log("OnDataChanged: " + props[rowIndex].name + " Value: " + data(modelIndex,"display"))
                props[rowIndex].value = data(modelIndex,"display")
                if (rowIndex === 0) {
                    adaptList(props[0].value)
                }
            }
        }

        signal adaptList(int kernelType)

        onAdaptList: function(kernelType) {
            if (rowCount > 1) removeRow(1,rowCount - 1)

            switch(kernelType) {
            case 2:
                appendRow({"name": props[1].name, "value": props[1].value, "component": props[1].component, "properties": props[1].properties, "description": props[1].description, "tagIndex": 1 });
                appendRow({"name": props[2].name, "value": props[2].value, "component": props[2].component, "properties": props[2].properties, "description": props[2].description, "tagIndex": 2 });
                break;
            case 0:
            case 1:
            case 7:
            case 8:
                appendRow({"name": props[1].name, "value": props[1].value, "component": props[1].component, "properties": props[1].properties, "description": props[1].description, "tagIndex": 1 });
                break;
            case 9:
            case 10:
            case 13:
            case 14:
                appendRow({"name": props[3].name, "value": props[3].value, "component": props[3].component, "properties": props[3].properties, "description": props[3].description, "tagIndex": 3 });
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 11:
            case 12:
                break;

            default:
                break;
            }
        }
    }

    Connections {
        target: macro
        function onParameterUpdated(index) {
            itemModel.setData(itemModel.index(index,1), "display", itemModel.props[index].value)
        }
    }

    Component {
        id: propertyValueDelegate

        Item {
            id: propertyDelegateItem
            Component.onCompleted: function() {
                var component = Qt.createComponent(model.edit + ".qml")
                if (component.status === Component.Error) {
                    component = Qt.createComponent("StringLineEdit.qml")
                }
                if (component.status === Component.Error) {
                    throw "\nFailed to load custom component '" + model.edit + ".qml'" +
                            "and default component 'StringLineEdit.qml' as backup for parameter '" + model.accessibleDescription + "'"
                }

                if (model.accessibleText.length > 0) {
                    var errorCaught = false
                    var props;
                    try {
                        props = JSON.parse(model.accessibleText)
                    }
                    catch(error) {
                        errorCaught = true;
                        throw "\nFailed to correctly parse custom properties '" + model.accessibleText + "'\n" +
                                "for parameter '" + model.accessibleDescription + "':" +
                                error.message +
                                "\nProperties are ignored."
                    }
                    finally {
                        if (errorCaught) {
                            component.createObject(propertyDelegateItem)
                        }
                        else {
                            component.createObject(propertyDelegateItem,props)
                        }
                    }
                }
                else {
                    component.createObject(propertyDelegateItem)
                }
            }

            Rectangle {
                anchors.fill: parent
                z: -1
                border.width: 1
                border.color: palette.midlight
                color: {
                    if (propertyView.currentItemRow === model.row) {
                        return palette.highlight
                    }
                    else if ((model.row) % 2 === 0) {
                        return palette.alternateBase
                    }
                    else {
                        return palette.base;
                    }
                }
            }
        }
    }

    HorizontalHeaderView {
        id: headerView
        boundsBehavior: Flickable.StopAtBounds
        syncView: propertyView
        anchors.left: propertyView.left
        width: parent.width
        model: ["Property","Value"]
        MouseArea {
            anchors.fill: parent
            anchors.leftMargin: parent.width * propertyView.columnDevider - 3
            anchors.rightMargin: parent.width * (1 - propertyView.columnDevider) - 3
            cursorShape: Qt.SplitHCursor
            acceptedButtons: Qt.LeftButton

            onPositionChanged: function(mouse) {
                var pos = mapToItem(parent,mouse.x,mouse.y)
                var devider = pos.x / parent.width
                if (devider < 0.1) devider = 0.1
                if (devider > 0.9) devider = 0.9
                propertyView.columnDevider = devider
                propertyView.forceLayout()
            }
        }
    }

    TableView {
        id: propertyView
        model: itemModel;
        boundsBehavior: Flickable.StopAtBounds
        anchors.fill: parent
        anchors.topMargin: headerView.height
        clip: true
        focus: true
        reuseItems: false

        property int currentItemRow: -1
        property real columnDevider: 0.3
        property int rowHeight: 0

        columnWidthProvider: function(column) {
            if (column === 0)
                return parent.width * columnDevider
            else
                return parent.width * (1 - columnDevider)
        }

        onContentHeightChanged: function() {
            if (contentHeight > 0 && rowHeight === 0) {
                rowHeight = contentHeight / itemModel.rowCount
                contentHeight = Qt.binding(function() { return rowHeight * itemModel.rowCount })
            }
        }

        onActiveFocusChanged: function(hasFocus) {
            if (!hasFocus) {
                propertyView.currentItemRow = -1
                macro.showDescription(propertyView.currentItemRow)
            }
        }

        Keys.onPressed: function(event) {
            if (event.key === Qt.Key_Up) {
                if (propertyView.currentItemRow < 0) propertyView.currentItemRow = 0
                else if (propertyView.currentItemRow > 0) propertyView.currentItemRow--
                macro.showDescription(propertyView.currentItemRow)
                event.accepted = true;
            }
            else if (event.key === Qt.Key_Down) {
                if (propertyView.currentItemRow < 0) propertyView.currentItemRow = 0
                else if (propertyView.currentItemRow < propertyView.rows - 1) propertyView.currentItemRow++
                macro.showDescription(propertyView.currentItemRow)
                event.accepted = true;
            }
        }

        MouseArea{
            id: propertyViewMouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onPressed: function(mouse) {
                // the following formular implies that all rows have the same height ...
                propertyView.currentItemRow = Math.min(mouse.y / propertyView.contentHeight * propertyView.rows, propertyView.rows - 1)
                macro.showDescription(propertyView.currentItemRow)
                mouse.accepted = true
            }
        }

        delegate: DelegateChooser {
            DelegateChoice {
                column: 0
                delegate: Text {
                    text: (model.display) ? model.display : ""
                    elide: Text.ElideRight
                    color: (propertyView.currentItemRow === model.row) ? palette.highlightedText : text
                    padding: 5
                    Rectangle {
                        anchors.fill: parent
                        z: -1
                        border.width: 1
                        border.color: palette.midlight
                        color: {
                            if (propertyView.currentItemRow === model.row) {
                                return palette.highlight
                            }
                            else if ((model.row) % 2 === 0) {
                                return palette.alternateBase
                            }
                            else {
                                return palette.base;
                            }
                        }
                    }
                }
            }
            DelegateChoice {
                column: 1
                delegate: propertyValueDelegate
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }
}
