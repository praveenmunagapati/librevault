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
#include "MLDHTGroup.h"
#include "MLDHTProvider.h"
#ifdef Q_OS_WIN
#   include <winsock2.h>
#else
#   include <sys/socket.h>
#endif

namespace librevault {

MLDHTGroup::MLDHTGroup(MLDHTProvider* provider, QByteArray id) :
	provider_(provider),
	id_(id) {
	timer_ = new QTimer(this);

	timer_->setInterval(5*1000);

	connect(provider_, &MLDHTProvider::discovered, this, &MLDHTGroup::handleDiscovered);
	connect(timer_, &QTimer::timeout, this, &MLDHTGroup::startSearches);
}

void MLDHTGroup::setEnabled(bool enable) {
	if(enable)
		timer_->start();
	else
		timer_->stop();
}

void MLDHTGroup::startSearches() {
	QByteArray ih = getInfoHash();

	qCDebug(log_dht) << "Starting DHT searches for:" << ih.toHex() << "on port:" << provider_->getAnnouncePort();
	provider_->startSearch(ih, QAbstractSocket::IPv4Protocol, provider_->getAnnouncePort());
	provider_->startSearch(ih, QAbstractSocket::IPv6Protocol, provider_->getAnnouncePort());
}

void MLDHTGroup::handleDiscovered(QByteArray ih, QHostAddress addr, quint16 port) {
	if(!enabled() || ih != getInfoHash()) return;
	emit discovered(addr, port);
}

} /* namespace librevault */