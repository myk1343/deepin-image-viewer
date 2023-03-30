// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.11

BaseImageDelegate {
    id: delegate

    status: image.status
    targetImage: image
    inputHandler: imageInput

    AnimatedImage {
        id: image

        height: delegate.height
        width: delegate.width
        asynchronous: true
        cache: false
        clip: true
        fillMode: Image.PreserveAspectFit
        smooth: true
        scale: delegate.scale
        source: delegate.source
    }

    ImageInputHandler {
        id: imageInput

        anchors.fill: parent
        targetImage: image.status === Image.Ready ? image : null
    }
}