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

/*! \file ored/configuration/defaultcurveconfig.hpp
    \brief Default curve configuration classes
    \ingroup configuration
*/

#pragma once

#include <ored/configuration/curveconfig.hpp>
#include <ql/time/calendar.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/time/period.hpp>
#include <ql/types.hpp>

using std::string;
using std::vector;
using ore::data::XMLNode;
using ore::data::XMLDocument;
using QuantLib::Period;
using QuantLib::DayCounter;
using QuantLib::Calendar;
using QuantLib::BusinessDayConvention;

namespace ore {
namespace data {

//! Default curve configuration
/*!
  \ingroup configuration
*/
class DefaultCurveConfig : public CurveConfig {
public:
    //! Supported default curve types
    enum class Type { SpreadCDS, HazardRate, Yield };
    //! \name Constructors/Destructors
    //@{
    //! Detailed constructor
    DefaultCurveConfig(const string& curveID, const string& curveDescription, const string& currency, const Type& type,
                       const string& discountCurveID, const string& recoveryRateQuote, const DayCounter& dayCounter,
                       const string& conventionID, const vector<string>& quotes, bool extrapolation = true);
    //! Default constructor
    DefaultCurveConfig() {}
    //@}

    //! \name Serialisation
    //@{
    void fromXML(XMLNode* node) override;
    XMLNode* toXML(XMLDocument& doc) override;
    //@}

    //! \name Inspectors
    //@{
    const string& currency() const { return currency_; }
    const Type& type() const { return type_; }
    const string& discountCurveID() const { return discountCurveID_; }
    const string& benchmarkCurveID() const { return benchmarkCurveID_; }
    const string& recoveryRateQuote() const { return recoveryRateQuote_; }
    const DayCounter& dayCounter() const { return dayCounter_; }
    const string& conventionID() const { return conventionID_; }
    bool extrapolation() const { return extrapolation_; }
    const vector<string>& cdsQuotes() { return cdsQuotes_; }

    //@}

    //! \name Setters
    //@{
    string& currency() { return currency_; }
    Type& type() { return type_; }
    string& discountCurveID() { return discountCurveID_; }
    string& benchmarkCurveID() { return benchmarkCurveID_; }
    string& recoveryRateQuote() { return recoveryRateQuote_; }
    DayCounter& dayCounter() { return dayCounter_; }
    string& conventionID() { return conventionID_; }
    bool& extrapolation() { return extrapolation_; }
    //@}

private:
    vector<string> cdsQuotes_;
    string currency_;
    Type type_;
    string discountCurveID_;
    string benchmarkCurveID_;
    string recoveryRateQuote_;
    DayCounter dayCounter_;
    string conventionID_;
    bool extrapolation_;
};
} // namespace data
} // namespace ore
