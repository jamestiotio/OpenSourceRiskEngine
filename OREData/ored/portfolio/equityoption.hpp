/*
 Copyright (C) 2016 Quaternion Risk Management Ltd
 All rights reserved.

 This file is part of ORE, a free-software/open-source library
 for transparent pricing and risk analysis - http://opensourcerisk.org

 ORE is free software: you can redistribute it and/or modify it
 under the terms of the Modified BSD License.  You should have received a
 copy of the license along with this program.
 The license is also available online at <http://opensourcerisk.org>

 This program is distributed on the basis that it will form a useful
 contribution to risk analytics and model standardisation, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
*/

/*! \file portfolio/equityoption.hpp
    \brief Equity Option data model and serialization
    \ingroup tradedata
*/

#pragma once

#include <ored/portfolio/underlying.hpp>
#include <ored/portfolio/vanillaoption.hpp>
#include <ored/portfolio/tradestrike.hpp>

namespace ore {
namespace data {
using std::string;

//! Serializable Equity Option
/*!
  \ingroup tradedata
*/
class EquityOption : public VanillaOptionTrade {
public:
    //! Default constructor
    EquityOption() : VanillaOptionTrade(AssetClass::EQ), localStrike_(0.0) { tradeType_ = "EquityOption"; }
    //! Constructor
    EquityOption(Envelope& env, OptionData option, EquityUnderlying equityUnderlying, string currency, QuantLib::Real strike,
        QuantLib::Real quantity, string strikeCurrency = "")
        : VanillaOptionTrade(env, AssetClass::EQ, option, equityUnderlying.name(), currency, strike, quantity),
          equityUnderlying_(equityUnderlying), localCurrency_(currency), localStrike_(strike), strikeCurrency_(strikeCurrency) {
        tradeType_ = "EquityOption";
    }

    //! Build QuantLib/QuantExt instrument, link pricing engine
    void build(const boost::shared_ptr<EngineFactory>&) override;

    //! Add underlying Equity names
    std::map<AssetClass, std::set<std::string>>
    underlyingIndices(const boost::shared_ptr<ReferenceDataManager>& referenceDataManager = nullptr) const override;

    //! \name Inspectors
    //@{
    const string& equityName() const { return equityUnderlying_.name(); }
    const string& strikeCurrency() const { return strikeCurrency_; }
    //@}

    //! \name Serialisation
    //@{
    virtual void fromXML(XMLNode* node) override;
    virtual XMLNode* toXML(XMLDocument& doc) override;
    //@}

protected:
    TradeStrike tradeStrike_;
    EquityUnderlying equityUnderlying_;
    string localCurrency_;
    QuantLib::Real localStrike_;
    string strikeCurrency_;
    std::string strikeStr_;
};
} // namespace data
} // namespace ore
