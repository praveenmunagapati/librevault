/* Copyright (C) 2014-2015 Alexander Shishenko <GamePad64@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SRC_SYNC_ENCFSBLOCKSTORAGE_H_
#define SRC_SYNC_ENCFSBLOCKSTORAGE_H_

#include "FileMeta.pb.h"

#include <cryptodiff.h>
#include <sqlite3.h>
#include <boost/optional.hpp>
#include <boost/filesystem.hpp>

namespace librevault {

class EncFSBlockStorage {
protected:
	boost::filesystem::path encblocks_path;
	boost::filesystem::path directory_path;
	sqlite3* directory_db = 0;

	boost::filesystem::path encrypted_block_path(const cryptodiff::shash_t& block_hash);
public:
	EncFSBlockStorage(const boost::filesystem::path& dirpath, const boost::filesystem::path& dbpath);
	virtual ~EncFSBlockStorage();

	virtual int64_t put_FileMeta(const FileMeta& meta, const std::vector<uint8_t>& signature);
	//int64_t put_FileMeta(const FileMeta& meta, const std::vector<uint8_t>& signature);
	virtual FileMeta get_FileMeta(int64_t rowid, std::vector<uint8_t>& signature);
	virtual FileMeta get_FileMeta(std::vector<uint8_t> encpath, std::vector<uint8_t>& signature);

	virtual std::vector<uint8_t> get_block_data(const cryptodiff::shash_t& block_hash);
	virtual void put_block_data(const cryptodiff::shash_t& block_hash, const std::vector<uint8_t>& data);
};

} /* namespace librevault */

#endif /* SRC_SYNC_ENCFSBLOCKSTORAGE_H_ */