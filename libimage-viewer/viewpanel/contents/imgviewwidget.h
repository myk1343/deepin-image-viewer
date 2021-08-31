/*
 * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     ZhangYong <zhangyong@uniontech.com>
 *
 * Maintainer: ZhangYong <ZhangYong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef IMGVIEWWIDGET_H
#define IMGVIEWWIDGET_H


#include <DSpinner>
#include <DListView>
#include <DAnchors>
#include <DThumbnailProvider>
#include <dimagebutton.h>
#include <DIconButton>
#include <DBlurEffectWidget>
#include <DGuiApplicationHelper>
#include <DLabel>

#include <QListWidget>
#include <QAbstractItemModel>
#include <QStandardItem>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include <QTime>
#include <QWidget>
#include <QLabel>

#include "image-viewer_global.h"
DWIDGET_USE_NAMESPACE

class ElidedLabel;
class QAbstractItemModel;
//class DImageButton;
class ImageButton;
class MyImageListWidget;
class ImageItem;
class ImgViewListView;

class MyImageListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyImageListWidget(QWidget *parent = nullptr);
    ~MyImageListWidget() override;

    void setAllFile(QList<imageViewerSpace::ItemInfo> itemInfos, QString path); //设置需要展示的所有缩略图
    //通过路径获取图片信息
    imageViewerSpace::ItemInfo getImgInfo(QString path);
    //获取当前图片信息
    imageViewerSpace::ItemInfo getCurrentImgInfo();
    //将选中的项居中
    void setSelectCenter();
    //获取当前所有展示图片数量
    int getImgCount();
    //清空缩略图
    void clearListView();

    //复位动画初始化
    void initAnimation();

    //获得当前图片的路径
    QString getCurrentPath();

    //获得当前
    int getCurrentCount();
signals:
    void openImg(int index, QString path);
private:
    void resetSelectImg();
protected:
    bool eventFilter(QObject *obj, QEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
public slots:
    //列表点击事件
    void onClicked(const QModelIndex &index);
    void ONselectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void onScrollBarValueChanged(int value);

    //查看下一张
    void openNext();
    //查看前一张
    void openPre();
    //移除当前选中
    void removeCurrent();
    //旋转图片
    void rotate(int matrix);
    //设置当前图片
    void setCurrentPath(const QString &path);

    //获取所有路径
    QStringList getAllPath();

    //滑动回弹动画
    void animationFinished();
    void animationValueChanged(const QVariant value);
    void animationStart(bool isReset, int endPos, int duration);
    void stopAnimation();

    //惯性滑动
    void thumbnailIsMoving();
    //无动画移动到选中位置
    void moveCenterWidget();

private:
    ImgViewListView *m_listview = nullptr;
    QPoint m_pressPoint;//鼠标按下位置
    QPoint m_movePoint;//鼠标实时移动位置
    QPoint m_moveViewPoint;//实时
    QPoint m_pressListviewPoint;//鼠标按下时列表位置
    QPoint m_releasePoint;//鼠标释放位置
    bool m_mousePress = false;//鼠标是否按下
    QTime m_mousePressTime;//记录鼠标按下的时间点
    int m_time;//鼠标按下移动持续时间，毫秒
    int m_moveSpeed = 0;
    QPropertyAnimation *m_resetAnimation = nullptr;//复位动画
    bool m_resetFinish = false;//动画标志
//    QPropertyAnimation *m_correctAnimation = nullptr;//纠偏动画

    QTimer *m_timer = nullptr;//点击定时，超过200ms过滤

    QVector<QPoint> m_movePoints;//移动的点数

    int m_preListGeometryLeft = 0;
};

#endif // IMGVIEWWIDGET_H