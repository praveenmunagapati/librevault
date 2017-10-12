/* Copyright (C) 2016 Alexander Shishenko <alex@shishenko.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
#pragma once
#include <QObject>
#include <QPointer>
#include "HierarchicalService.h"

namespace librevault {

class GenericProvider : public QObject {
 Q_OBJECT

public:
  explicit GenericProvider(QObject* parent) : QObject(parent) {}
  GenericProvider(const GenericProvider&) = delete;
  GenericProvider(GenericProvider&&) = delete;
  virtual ~GenericProvider() = default;

  quint16 getAnnouncePort() const {return announce_port_;}
  Q_SLOT void setAnnouncePort(quint16 port) {announce_port_ = port;}

  bool isEnabled() const {return enabled_;}
  void setEnabled(bool enabled) {enabled_ = enabled;}

 private:
  quint16 announce_port_ = 0;
  bool enabled_ = false;
};

class GenericGroup : public QObject {
 Q_OBJECT

 public:
  explicit GenericGroup(QObject* parent) : QObject(parent) {}
  GenericGroup(const GenericGroup&) = delete;
  GenericGroup(GenericGroup&&) = delete;
  virtual ~GenericGroup() = default;

  bool isEnabled() const {return enabled_;}
  void setEnabled(bool enabled) {enabled_ = enabled;}

 private:
  QPointer<GenericProvider> provider_;
  bool enabled_ = false;

  bool readyToDiscover() {return isEnabled() && provider_ && provider_->isEnabled();}
};

} /* namespace librevault */