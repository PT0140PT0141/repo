/* Beaglebone GPS protocol factory implementation
 * Copyright (c) 2014 ygarcia, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#if !defined(__GPS_PROTOCOLS_MGR_H__)
#define __GPS_PROTOCOLS_MGR_H__

#include <iostream>
#include <memory> // Used for unique_ptr
#include <vector>

#include "gpsProtocolsAnalyzer.h"

namespace beagleboneGps {

  class gpsProtocolsMgr {
    static std::unique_ptr<gpsProtocolsMgr> _instance;

    gpsProtocolsMgr();

  public:
    enum Protocols : unsigned char {
      nmea2000 = 0x00
    };
    
    ~gpsProtocolsMgr();

    inline static gpsProtocolsMgr & getInstance() { return *gpsProtocolsMgr::_instance; };

    void createProtocolAnalyzer(const gpsProtocolsMgr::Protocols p_protocol, std::unique_ptr<gpsProtocolsAnalyzer> & p_newInstance);

  }; // End of class gpsProtocolsMgr

} // End of namespace beagleboneGps

using namespace beagleboneGps;

#endif // __GPS_PROTOCOLS_MGR_H__
