/****************************************************************************************************
**   Impresario Library ImageProcessing_ltilib-2
**   This file is part of the Impresario Library ImageProcessing_ltilib-2.
**
**   Copyright (C) 2015-2018  Lars Libuda
**   All rights reserved.
**
**   Redistribution and use in source and binary forms, with or without
**   modification, are permitted provided that the following conditions are met:
**       * Redistributions of source code must retain the above copyright
**         notice, this list of conditions and the following disclaimer.
**       * Redistributions in binary form must reproduce the above copyright
**         notice, this list of conditions and the following disclaimer in the
**         documentation and/or other materials provided with the distribution.
**       * Neither the name of the copyright holder nor the
**         names of its contributors may be used to endorse or promote products
**         derived from this software without specific prior written permission.
**
**   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
**   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
**   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*****************************************************************************************************/
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    width: 300
    height: 300

    ListModel {
        id: itemProperties;

        signal adaptList(int selection);
        property variant props: macro.parameters();

        Component.onCompleted: {
            append({"property": props[0].name, "value": props[0].value, "component": props[0].component, "properties": props[0].properties, "tagIndex": 0 });
            adaptList(props[0].value);
            // NOTE: There is a nasty bug in the TableView component introduced in Qt 5.6
            // It seems like a racing condition between this method and loading the TableView
            // Assigned the model to the TableView here fixes this problem
            propertyView.model = this;
        }

        onDataChanged: {
            //console.log("onDataChanged",propertyView.currentRow);
            if (propertyView.currentRow >= 0 && propertyView.currentRow < itemProperties.count) {
                var index = itemProperties.get(propertyView.currentRow).tagIndex;
                props[index].value = itemProperties.get(propertyView.currentRow).value;
                if (index === 0) {
                    adaptList(props[index].value);
                }
            }
        }

        onAdaptList: {
            //console.log("adaptList",selection);
            propertyView.currentRow = -1;
            if (count > 1) {
                remove(1,count-1);
            }
            var prop;
            var elements = [];
            switch(selection) {
            case 2:
                for(prop = 1; prop <= 2; prop++) {
                    elements.push({"property": props[prop].name, "value": props[prop].value, "component": props[prop].component, "properties": props[prop].properties, "tagIndex": prop });
                }
                append(elements);
                break;
            case 0:
            case 1:
            case 7:
            case 8:
                for(prop = 1; prop <= 1; prop++) {
                    elements.push({"property": props[prop].name, "value": props[prop].value, "component": props[prop].component, "properties": props[prop].properties, "tagIndex": prop });
                }
                append(elements);
                break;
            case 9:
            case 10:
            case 13:
            case 14:
                for(prop = 3; prop <= 3; prop++) {
                    elements.push({"property": props[prop].name, "value": props[prop].value, "component": props[prop].component, "properties": props[prop].properties, "tagIndex": prop });
                }
                append(elements);
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
            propertyView.currentRow = 0;
        }
    }


    Connections {
        target: macro;
        onParameterUpdated: {
            itemProperties.set(index,{"value": itemProperties.props[index].value });
        }
    }

    Component {
        id: propertyDelegate

        Item {
            SystemPalette { id: palette; colorGroup: SystemPalette.Active }
            id: propertyDelegateItem
            Component.onCompleted: {
                if (styleData.column === 0) {
                    Qt.createQmlObject(
                        'import QtQuick 2.5
                         Text {
                            id: propertyDelegateText
                            anchors.fill: parent
                            anchors.leftMargin: 3.0
                            text: styleData.value
                            elide: styleData.elideMode
                            verticalAlignment: Text.AlignVCenter
                            renderType: Text.NativeRendering
                            color: if (styleData.selected) {
                                return palette.highlightedText
                            }
                            else {
                                return palette.text
                            }
                         }',propertyDelegateItem,"propertyNameItem");
                }
                else if (styleData.column === 1) {
                    var index = itemProperties.get(styleData.row).tagIndex;
                    var component = Qt.createComponent(itemProperties.props[index].component + ".qml");
                    if (component.status === Component.Error) {
                        component = Qt.createComponent("StringLineEdit.qml");
                    }
                    if (component.status === Component.Error) {
                        throw "\nFailed to load custom component '" + itemProperties.props[index].component + ".qml'" +
                              "and default component 'StringLineEdit.qml' as backup for parameter '" + itemProperties.props[index].name + "'";
                    }

                    if (itemProperties.props[index].properties.length > 0) {
                        var errorCaught = false;
                        var props;
                        try {
                            props = eval(itemProperties.props[index].properties);
                        }
                        catch(error) {
                            errorCaught = true;
                            throw "\nFailed to correctly parse custom properties '" + itemProperties.props[index].properties + "'\n" +
                                  "for parameter '" + itemProperties.props[index].name + "':" +
                                  error.message +
                                  "\nProperties are ignored.";
                        }
                        finally {
                            if (errorCaught) {
                                component.createObject(propertyDelegateItem);
                            }
                            else {
                                component.createObject(propertyDelegateItem,props);
                            }
                        }
                    }
                    else {
                        component.createObject(propertyDelegateItem);
                    }
                }
            }

            Rectangle {
                anchors.fill: parent
                color: palette.midlight

                Rectangle {
                    anchors.fill: parent
                    anchors.bottomMargin: 1.0
                    anchors.rightMargin: 1.0
                    color: {
                        if (styleData.selected) {
                            return palette.highlight;
                        }
                        else if ((propertyView.rowCount - styleData.row) % 2 === 1) {
                            return palette.alternateBase
                        }
                        else {
                            return palette.base;
                        }
                    }
                }
            }
        }
    }

    Component {
        id: propertyRowDelegate

        Rectangle {
            SystemPalette { id: palette; colorGroup: SystemPalette.Active }
            FontMetrics { id: defaultFont; }
            id: rowRectangle
            height: defaultFont.height + 7
            color: palette.base
        }
    }

    TableView {
        id : propertyView;
        // NOTE: No model assignment here any more, see also comment in ListModel:Component.onCompleted
        //model: itemProperties;
        anchors.fill: parent;
        itemDelegate: propertyDelegate
        rowDelegate: propertyRowDelegate
        selectionMode: SelectionMode.SingleSelection;

        onClicked: {
            macro.showDescription(itemProperties.get(row).tagIndex);
        }

        TableViewColumn {
            id: colPropertyName
            role: "property"
            title: "Property"
            width: 120
            resizable: true
            movable: false
        }
        TableViewColumn {
            id: colPropertyValue
            role: "value"
            title: "Value"
            width: propertyView.width - colPropertyName.width - 2
            resizable: false
            movable: false
        }

    }

}
