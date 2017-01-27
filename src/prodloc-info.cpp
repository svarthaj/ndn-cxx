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

#include "prodloc-info.hpp"
#include "encoding/encoding-buffer.hpp"
#include "encoding/block-helpers.hpp"

namespace ndn {

BOOST_CONCEPT_ASSERT((boost::EqualityComparable<ProdLocInfo>));
BOOST_CONCEPT_ASSERT((WireEncodable<ProdLocInfo>));
BOOST_CONCEPT_ASSERT((WireEncodableWithEncodingBuffer<ProdLocInfo>));
BOOST_CONCEPT_ASSERT((WireDecodable<ProdLocInfo>));
static_assert(std::is_base_of<tlv::Error, ProdLocInfo::Error>::value,
              "ProdLocInfo::Error must inherit from tlv::Error");

ProdLocInfo::ProdLocInfo()
  : m_location(-1)
  , m_distanceHA(-1)  
{
}

ProdLocInfo::ProdLocInfo(const Block& wire)
{
  wireDecode(wire);
}

bool
ProdLocInfo::empty() const
{
  return m_location == -1 && m_distanceHA == -1;
}

template<encoding::Tag TAG>
size_t
ProdLocInfo::wireEncode(EncodingImpl<TAG>& encoder) const
{
  size_t totalLength = 0;

  if (getLocation() >= 0) {
    totalLength += prependNonNegativeIntegerBlock(encoder, tlv::Location, getLocation());
  }
  
  if (getDistanceHA() >= 0) {
    totalLength += prependNonNegativeIntegerBlock(encoder, tlv::DistanceHA, getDistanceHA());
  }
  
  totalLength += encoder.prependVarNumber(totalLength);
  totalLength += encoder.prependVarNumber(tlv::ProdLocInfo);
  return totalLength;
}

template size_t
ProdLocInfo::wireEncode<encoding::EncoderTag>(EncodingImpl<encoding::EncoderTag>& encoder) const;

template size_t
ProdLocInfo::wireEncode<encoding::EstimatorTag>(EncodingImpl<encoding::EstimatorTag>& encoder) const;

const Block&
ProdLocInfo::wireEncode() const
{
  if (m_wire.hasWire())
    return m_wire;

  EncodingEstimator estimator;
  size_t estimatedSize = wireEncode(estimator);

  EncodingBuffer buffer(estimatedSize, 0);
  wireEncode(buffer);

  m_wire = buffer.block();
  return m_wire;
}

void
ProdLocInfo::wireDecode(const Block& wire)
{
  if (wire.type() != tlv::ProdLocInfo)
    BOOST_THROW_EXCEPTION(tlv::Error("Unexpected TLV type when decoding ProdLocInfo"));

  *this = ProdLocInfo();

  m_wire = wire;
  m_wire.parse();

  Block::element_const_iterator val = m_wire.find(tlv::Location);
  if (val != m_wire.elements_end()) {
    m_location = readNonNegativeInteger(*val);
  }

  val = m_wire.find(tlv::DistanceHA);
  if (val != m_wire.elements_end()) {
    m_distanceHA = readNonNegativeInteger(*val);
  }

}

void
ProdLocInfo::setLocation(int loc)
{
  m_location = loc;
  m_wire.reset();
}

void
ProdLocInfo::setDistanceHA(int dist)
{
  m_distanceHA = dist;
  m_wire.reset();
}

bool
ProdLocInfo::operator==(const ProdLocInfo& other) const
{
  return wireEncode() == other.wireEncode();
}

} // namespace ndn
