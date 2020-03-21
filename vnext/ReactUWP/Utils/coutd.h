#pragma once
struct coutdbuf : public std::streambuf {
 protected:
  virtual int overflow(int c) {
    static char sz[2] = {0};
    sz[0] = (char)c;
    ::OutputDebugStringA(sz);
    return c;
  }
  virtual std::streamsize sputn(const char *s, std::streamsize n) {
    ::OutputDebugStringA(s);
    return n;
  }
};
struct coutd_t : public std::ostream
{
  using base_t = std::ostream;
  coutdbuf m_buf;
  coutd_t() : base_t(&m_buf)
    {}
};

extern coutd_t coutd;
