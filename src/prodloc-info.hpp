/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2013-2015 Regents of the University of California.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 *
 */

#ifndef PRODLOC_INFO_HPP
#define PRODLOC_INFO_HPP

#include "common.hpp"
#include "exclude.hpp"

namespace ndn {

/**
 * @brief Abstraction implementing Producer Location Information
 */
class ProdLocInfo
{
public:
  class Error : public tlv::Error
  {
  public:
    explicit
    Error(const std::string& what)
      : tlv::Error(what)
    {
    }
  };

  ProdLocInfo();

  /**
   * @brief Create from wire encoding
   */
  explicit
  ProdLocInfo(const Block& wire);

  bool
  empty() const;

  /**
   * @brief Fast encoding or block size estimation
   */
  template<encoding::Tag TAG>
  size_t
  wireEncode(EncodingImpl<TAG>& encoder) const;

  /**
   * @brief Encode to a wire format
   */
  const Block&
  wireEncode() const;

  /**
   * @brief Decode the input from wire format
   */
  void
  wireDecode(const Block& wire);

public: // getters & setters for producer location info

  void setLocation(int loc);

  int
  getLocation() const
  {
    return m_location;
  }

  void setDistanceHA(int dist);

  int
  getDistanceHA() const
  {
    return m_distanceHA;
  }

public: // EqualityComparable concept
  bool
  operator==(const ProdLocInfo& other) const;

  bool
  operator!=(const ProdLocInfo& other) const
  {
    return !this->operator==(other);
  }

private:
  // node where mobile producer is located
  int m_location;
  // distance in hops between the mobile producer and the home agent
  int m_distanceHA;  

  mutable Block m_wire;
};

} // namespace ndn

#endif // PRODLOC_INFO_HPP
