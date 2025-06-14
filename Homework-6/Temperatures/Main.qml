import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    color: "#aaaaaa"
    title: qsTr("Temperatures converter")

    Column{
        anchors.centerIn: parent
        anchors.margins: 10
        spacing: 10

        Row{
            Label {
                text: "Celsius";
                width: 150;
                height: 30;
                anchors.horizontalCenter: right;
                horizontalAlignment: TextInput.AlignRight;
                font.pixelSize: 25;
                rightPadding: 5
            }

            TextField {
                id: cTemp;
                background:
                    Rectangle{color:"white"}
                color: "black";
                text: model.cTemp;
                width: 100;
                height: 30;
                validator: DoubleValidator{
                    bottom: -273.16;
                    decimals: 2;
                    notation: DoubleValidator.StandardNotation;
                }
                horizontalAlignment: TextInput.AlignHCenter
                onTextEdited: {
                    controller.cTemp_handler(cTemp.text)
                }
            }
        }

        Row{
            Label {
                text: "Fahrenheit";
                width: 150;
                height: 30;
                anchors.horizontalCenter: right;
                horizontalAlignment: TextInput.AlignRight;
                font.pixelSize: 25;
                rightPadding: 5
            }

            TextField {
                id: fTemp;
                background: Rectangle{color:"white"}
                color: "black";
                text: model.fTemp;
                width: 100;
                height: 30;
                validator: DoubleValidator{
                    bottom: -459.67;
                    decimals: 2;
                    notation: DoubleValidator.StandardNotation;
                }
                horizontalAlignment: TextInput.AlignHCenter
                onTextEdited: {
                    controller.fTemp_handler(fTemp.text)
                }
            }
        }

        Row{
            Label {
                text: "Kelvin";
                width: 150;
                height: 30;
                anchors.horizontalCenter: right;
                horizontalAlignment: TextInput.AlignRight;
                font.pixelSize: 25;
                rightPadding: 5
            }

            TextField {
                id: kTemp;
                background: Rectangle{color:"white"}
                color: "black";
                text: model.kTemp;
                width: 100;
                height: 30;
                validator: DoubleValidator{
                    bottom: 0;
                    decimals: 2;
                    notation: DoubleValidator.StandardNotation;
                }
                horizontalAlignment: TextInput.AlignHCenter
                onTextEdited: {
                    controller.kTemp_handler(kTemp.text)
                }
            }
        }
    }
}
