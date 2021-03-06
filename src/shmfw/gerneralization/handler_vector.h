/***************************************************************************
 *   Software License Agreement (BSD License)                              *
 *   Copyright (C) 2012 by Markus Bader <markus.bader@tuwien.ac.at>        *
 *                                                                         *
 *   Redistribution and use in source and binary forms, with or without    *
 *   modification, are permitted provided that the following conditions    *
 *   are met:                                                              *
 *                                                                         *
 *   1. Redistributions of source code must retain the above copyright     *
 *      notice, this list of conditions and the following disclaimer.      *
 *   2. Redistributions in binary form must reproduce the above copyright  *
 *      notice, this list of conditions and the following disclaimer in    *
 *      the documentation and/or other materials provided with the         *
 *      distribution.                                                      *
 *   3. Neither the name of the copyright holder nor the names of its      *
 *      contributors may be used to endorse or promote products derived    *
 *      from this software without specific prior written permission.      *
 *                                                                         *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS     *
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  *
 *   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
 *   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      *
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      *
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT    *
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY *
 *   WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           *
 *   POSSIBILITY OF SUCH DAMAGE.                                           *
 ***************************************************************************/

#ifndef SHARED_MEM_HANDLER_VECTOR
#define SHARED_MEM_HANDLER_VECTOR

#include <shmfw/gerneralization/handler_object.h>
#include <shmfw/vector.h>

namespace ShmFw {

template <class T>
class HandlerVector : public HandlerObject {
public:
private:
    ShmFw::Vector<T> v;
public:
    HandlerVector(const std::string &name, HandlerPtr &shmHdl) {
        v.construct (name, shmHdl);
    }
    std::string type_name () {
        return v.type_name();
    }
    virtual void it_has_changed() {
      v.itHasChanged();
    }
    virtual void lock() {
      v.try_lock();
    }
    virtual void unlock() {
      v.unlock();
    }
    virtual bool locked() {
      return v.locked();
    }
    virtual std::string timestamp() {
        return to_simple_string(v.timestampShm()) ;
    }
    std::string name () {
        return v.name();
    }
    std::string value() const {
      std::stringstream ss;
      ss << "[ ";
      for(size_t i = 0; i < v.size(); i++){
	if( i != 0) ss << "; ";
	ss << boost::lexical_cast<std::string>(v[i]);
      }
      ss << " ]";
      return ss.str();
    }
    virtual std::string value(uint32_t i) const {
	if( i > size()) return "Out of bound";
	return boost::lexical_cast<std::string>(v[i]);
    }
    virtual uint32_t size() const {
        return v.size();
    }
    /**
     * @todo not jet finished
     **/
    void value(const std::string &str) {
      int start = str.find("[");
      int end = str.find_last_of("]");
      std::string data = str.substr(start+1, end-1); 
      end = data.find(",", start);
      int openTags = 0;
      for( int i = start; i < end; i++){
	if(data[i] == '[') openTags++;
	if(data[i] == ']') openTags--;
      }
      if(openTags == 0){
	std::string s = str.substr(start+1, end-1); 
	v->push_back(boost::lexical_cast<T>(s) );
      }
    }
    int construct ( const std::string &name, Handler &shmHdl ){
      return v.construct(name, shmHdl);
    }
};


};



#endif //SHARED_MEM_HANDLER_VAR




