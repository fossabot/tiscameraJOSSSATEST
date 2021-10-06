/*
 * Copyright 2021 The Imaging Source Europe GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PROPERTYDIALOG_H
#define PROPERTYDIALOG_H

#include "propertywidget.h"
#include "propertyworker.h"
#include "tcamcollection.h"

#include <QDialog>
#include <QThread>
#include <gst/gst.h>
#include <string>

namespace Ui
{
class PropertyDialog;
}

class PropertyTree : public QWidget
{
    Q_OBJECT

public:
    PropertyTree(QString name,
                 const std::map<std::string, Property*>& properties,
                 QWidget* parent = nullptr);

private:
    void setup_ui();

    std::map<std::string, Property*> m_properties;

    QString m_name;
    QVBoxLayout* p_layout;
};

class PropertyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropertyDialog(TcamCollection& collection, QWidget* parent = nullptr);
    ~PropertyDialog();

public slots:

    void notify_device_lost(const QString& info);

signals:

    void device_lost(const QString& info);

private:
    void initialize_dialog();

    Ui::PropertyDialog* ui;

    TcamCollection m_collection;
    QThread* p_work_thread;
    PropertyWorker* p_worker;

    std::map<std::string, Property*> m_properties;
};

#endif // PROPERTYDIALOG_H