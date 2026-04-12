import QtQuick
import QtQuick.Controls

Window {
    id: root
    width: 300
    height: 600
    visible: true
    title: qsTr("MoveGame - QML edition")

    Timer {
        id: updateTimer
        interval: 100
        repeat: true
        running: true

        onTriggered: {
            for (const child of root.contentItem.children) {
                if (!(child instanceof Button)) {
                    continue;
                }

                child.y += child.hovered ? (child.speed * 2) : child.speed;

                if ((child.y + child.height) >= root.height) {
                    root.color = "red"
                    root.title = qsTr("You LOOSE!")
                    child.destroy(1)
                }
            }
        }
    }

    Timer {
        id: spawnTimer
        interval: 1000
        repeat: true
        running: true

        onTriggered: {
            templateButton.createObject(root.contentItem)
            interval = randomInt(100, 1000)
        }
    }

    Component {
        id: templateButton
        Button {
            text: qsTr("*")
            width: 25
            height: 25
            y: 100

            property int speed: 0

            Component.onCompleted: {
                x = randomInt(0, root.width - width)
                speed = randomInt(1, 4)
            }

            onClicked: {
                destroy()
            }
        }
    }

    function randomInt(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }
}