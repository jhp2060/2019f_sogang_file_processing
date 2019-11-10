#include "newsAgency.h"

NewsAgency::NewsAgency(const NewsAgency &n) {
    updateNewsAgencyId(n.newsAgencyId);
    updateName(n.name);
    updateAddress(n.address);
}

NewsAgency &NewsAgency::operator = (const NewsAgency &n) {
    updateNewsAgencyId(n.newsAgencyId);
    updateName(n.name);
    updateAddress(n.address);

    return *this;
}
bool NewsAgency::operator == (const NewsAgency &n) {
    return !memcpy(newsAgencyId,n.newsAgencyId,MAX_NEWS_AGENCY_ID);
}
bool NewsAgency::operator != (const NewsAgency &n) {
    return memcpy(newsAgencyId,n.newsAgencyId,MAX_NEWS_AGENCY_ID);
}
istream & operator >> (istream &is, NewsAgency &n) {
    string s;
    is.exceptions(istream::failbit | istream::badbit);

    try {
        getline(is,s);
    } catch (istream::failure e) {
        return is;
    }

    istringstream iss(s);
    string token;

    getline(iss, token, '|');
    n.updateNewsAgencyId(token.data());
    getline(iss, token, '|');
    n.updateName(token);
    getline(iss, token, '|');
    n.updateAddress(token);
    
    return is;
}
ostream & operator << (ostream &os, NewsAgency &n) {
    string mNewsAgencyId (n.newsAgencyId, MAX_NEWS_AGENCY_ID);

    os << "NEWSAGENCY ID : " << mNewsAgencyId << "\n";
    os << "NAME : " << n.name << "\n";
    os << "ADDRESS : " << n.address << "\n";

    return os; 
}
bool NewsAgency::Pack(IOBuffer &Buffer) const {
    int numBytes;

    Buffer.Clear();

    string mNewsAgencyId (newsAgencyId, MAX_NEWS_AGENCY_ID);
    
    numBytes = Buffer.Pack(mNewsAgencyId.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(name.c_str());
    if ( numBytes == -1 ) return false;
    numBytes = Buffer.Pack(address.c_str());
    if ( numBytes == -1 ) return false;
    
    return true;
}
bool NewsAgency::Unpack(IOBuffer &Buffer) {
    int numBytes;
    char buf[STDMAXBUF];

    numBytes = Buffer.Unpack(newsAgencyId, MAX_NEWS_AGENCY_ID);
    if ( numBytes == -1 ) return false;

    numBytes = Buffer.Unpack(buf);
    if ( numBytes == -1 ) return false;
    name = buf;

    numBytes = Buffer.Unpack (buf);
    if ( numBytes == -1 ) return false;
    address = buf;
    
    return true;
}
