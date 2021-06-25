/*
 * objecttypeseditor.h
 * Copyright 2016, Thorbjørn Lindeijer <bjorn@lindeijer.nl>>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "custompropertieshelper.h"
#include "properties.h"

#include <QDialog>
#include <QStyledItemDelegate>

namespace Ui {
class ObjectTypesEditor;
}

class QtBrowserItem;
class QtProperty;
class QtVariantPropertyManager;

namespace Tiled {

class ColorDelegate : public QStyledItemDelegate
{
public:
    explicit ColorDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    { }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &,
                   const QModelIndex &) const override;
};


class ObjectTypesModel;

class ObjectTypesEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ObjectTypesEditor(QWidget *parent = nullptr);
    ~ObjectTypesEditor() override;

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent *) override;
    void changeEvent(QEvent *e) override;

private:
    void addObjectType();
    void selectedObjectTypesChanged();
    void removeSelectedObjectTypes();
    void objectTypeIndexClicked(const QModelIndex &index);
    void applyObjectTypes();
    void objectTypesChanged();
    void applyPropertyToSelectedTypes(const QString &name, const QVariant &value);
    void removePropertyFromSelectedTypes(const QString &name);

    void importObjectTypes();
    void exportObjectTypes();

    void updateProperties();
    void propertyValueChanged(QtProperty *property, const QVariant &val);

    void openAddPropertyDialog();
    void addProperty(const QString &name, const QVariant &value = QVariant());
    void editProperty(const QString &name);
    void removeProperty();
    void renameProperty();
    void renamePropertyTo(const QString &name);

    void selectFirstType();
    void currentItemChanged(QtBrowserItem *item);

    void retranslateUi();

    Ui::ObjectTypesEditor *mUi;
    ObjectTypesModel *mObjectTypesModel;

    QtVariantPropertyManager *mVariantManager;
    CustomPropertiesHelper mPropertiesHelper;

    AggregatedProperties mProperties;
    bool mUpdating = false;
    bool mSettingPrefObjectTypes = false;

    QAction *mAddObjectTypeAction;
    QAction *mRemoveObjectTypeAction;

    QAction *mAddPropertyAction;
    QAction *mRemovePropertyAction;
    QAction *mRenamePropertyAction;
};

} // namespace Tiled
