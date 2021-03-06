/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 * Copyright (c) 2016-2017 metaverse core developers (see MVS-AUTHORS)
 *
 * This file is part of metaverse-explorer.
 *
 * metaverse-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <metaverse/explorer/commands/input-set.hpp>

#include <iostream>
#include <cstdint>
#include <metaverse/bitcoin.hpp>
#include <metaverse/explorer/config/transaction.hpp>
#include <metaverse/explorer/utility.hpp>


namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::explorer::config;

console_result input_set::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto index = get_index_option();
    const auto& tx_in = get_transaction_argument();
    const auto& script = get_endorsement_script_argument();

    // Clone so we keep arguments const.
    auto tx_copy = transaction(tx_in);
    auto& tx_out = tx_copy.data();

    if (index >= tx_out.inputs.size())
    {
        error << BX_INPUT_SET_INDEX_OUT_OF_RANGE << std::flush;
        return console_result::failure;
    }

    tx_out.inputs[index].script = script;

    output << tx_copy << std::flush;
    return console_result::okay;
}

} //namespace commands 
} //namespace explorer 
} //namespace libbitcoin 
